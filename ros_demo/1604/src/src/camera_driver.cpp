#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <linux/videodev2.h>
//SDK
#include <imrsdk.h>
//Ros
#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Pose.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/CameraInfo.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/image_encodings.h>

#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/StdVector>

using namespace indem;	

//Header param
int imu_id = 0;
int slam_id = 0;
int depth_id = 0;
int camera_id = 0;
ros::Time imu_start_time;
ros::Time slam_start_time;
ros::Time depth_start_time;
ros::Time camera_start_time;
int image_width = 0;
int image_height = 0;

//----imu camera------
int imu_count = 0;
int image_l_count = 0;
int image_r_count = 0;

struct ImrDepthImageTarget
{
    double _time;
	float _cubesize;
	int _image_w;
	int _image_h;
	float* _deepptr;
};

//CameraInfo param
sensor_msgs::CameraInfo camerainfo_msg;
//Publisher
ros::Publisher imu_pub;            
ros::Publisher slam_pub;
ros::Publisher depth_pub;
ros::Publisher image_l_pub;
ros::Publisher image_r_pub;
ros::Publisher camera_info_pub;

struct CommandParams{               
	int16_t width;
	int16_t height;
	char distortion_model[16];
    	double P[12];
};

struct DepthData{
	double _time;
	unsigned char* _depthImage;
};

void ImuCallBackFunction(double time, float accX, float accY, float accZ, float gyrX, float gyrY, float gyrZ, void* pParam)
{
	//printf ("enter imu callback\n");
	//ros::Time current_time = ros::Time::now();
	//ros::Time::now();
	//--------Imu gyr and acc info----------------------------------
	if (imu_id == 0)
		imu_start_time = ros::Time::now() - ros::Duration(time); 
	sensor_msgs::Imu imu_msg;
	imu_msg.header.stamp = imu_start_time + ros::Duration(time);
	imu_msg.header.seq = imu_count++;
    	imu_msg.angular_velocity.x = gyrX;
    	imu_msg.angular_velocity.y = gyrY;
   	imu_msg.angular_velocity.z = gyrZ;
    	imu_msg.linear_acceleration.x = accX;
  	imu_msg.linear_acceleration.y = accY;
  	imu_msg.linear_acceleration.z = accZ;
	imu_pub.publish(imu_msg);
	//--------------------------------------------------------------
}


void CameraCallbackFunction(double time, unsigned char* pLeft, unsigned char* pRight, int width, int height, int channel, void* pParam)
{
	//printf("enter camera callback\n");

	cv::Mat img_l(800,1280, CV_8UC1, pLeft);
	cv::Mat img_r(800,1280, CV_8UC1, pRight);
	//ros::Time::now();
	//img(cv::Rect(0,0,1280,800));
	//img(cv::Rect(1280,0,1280,800));
	//ros::Time current_time = ros::Time::now();

	if (camera_id == 0)
		camera_start_time = ros::Time::now() - ros::Duration(time); 
	//--------Camera_left Info----------------------------------
	cv_bridge::CvImage cvi_l;
	sensor_msgs::Image imgl;	
	cvi_l.header.stamp = camera_start_time + ros::Duration(time);
	cvi_l.header.seq = image_l_count++;
	cvi_l.encoding = "mono8";
	cvi_l.image = img_l;
	cvi_l.toImageMsg(imgl);	
	image_l_pub.publish(imgl);
	//--------Camera_right Info---------------------------------
	cv_bridge::CvImage cvi_r;
	sensor_msgs::Image imgr;	
	cvi_r.header.stamp = camera_start_time + ros::Duration(time);
	cvi_r.header.seq = image_r_count++;
	cvi_r.encoding = "mono8";
	cvi_r.image = img_r;
	cvi_r.toImageMsg(imgr);	
	image_r_pub.publish(imgr);
}	

void DepthDataCallback(int, void* pData, void* pParam)
{
	//DepthData *Depth = (DepthData*)pData;
	ImrDepthImageTarget* Depth = reinterpret_cast<ImrDepthImageTarget*>(pData);	
	if (depth_id == 0)
		depth_start_time = ros::Time::now() - ros::Duration(Depth->_time); 
	//--------Header Info----------------------------------
	std_msgs::Header header_msg;
	header_msg.seq = depth_id++;
	header_msg.stamp = depth_start_time + ros::Duration(Depth->_time);
    	header_msg.frame_id = "base_link";
	camerainfo_msg.header = header_msg;
	camerainfo_msg.height = Depth->_image_h;
	camerainfo_msg.width  = Depth->_image_w;
	//---------publish camerainfo--------------------------		
	camera_info_pub.publish(camerainfo_msg);
	//---------Image Info----------------------------------
	cv_bridge::CvImage cvi;	
	sensor_msgs::Image image_msg;
	cvi.header = header_msg;
	cvi.encoding = "32FC1";
	cvi.image = cv::Mat(Depth->_image_h, Depth->_image_w, CV_32FC1, Depth->_deepptr);
	
	cvi.toImageMsg(image_msg);	
	//---------publish Image,CameraInfo--------------------
	depth_pub.publish(image_msg);
}

void sdkSLAMResult(int ret, void* pData, void* pParam)
{	
	if (ret == 0)
	{
	ImrModulePose *p = (ImrModulePose*)pData;
	if (slam_id++ == 0)
		slam_start_time = ros::Time::now() - ros::Duration(p->_pose._time);	
	geometry_msgs::Pose pose;		
	pose.position.x = p->_pose._position[1];
	pose.position.y = -p->_pose._position[0];
	pose.position.z = 0;//p->_pose._position[2];
	
	Eigen::Quaterniond t(p->_pose._rotation[0],p->_pose._rotation[1],p->_pose._rotation[2],p->_pose._rotation[3]);
	
	Eigen::Matrix3d r = t.toRotationMatrix();
	Eigen::Matrix3d lm;
	lm << 0,1,0,
	      -1,0,0,
	      0,0,1;
	Eigen::Matrix3d rm;
	rm << 0,-1,0,
	      1,0,0,
	      0,0,1;

        Eigen::Matrix3d res = lm * r * rm;
        Eigen::Quaterniond re(res);
	
	pose.orientation.x = re.x();
	pose.orientation.y = re.y();
	pose.orientation.z = re.z();
	pose.orientation.w = re.w();

	slam_pub.publish(pose);
	
	static tf::TransformBroadcaster br;
	tf::Transform transform;
	transform.setOrigin( tf::Vector3(pose.position.x, pose.position.y, pose.position.z) );
	tf::Quaternion q;
	tf::quaternionMsgToTF(pose.orientation, q);
	transform.setRotation(q);
	br.sendTransform(tf::StampedTransform(transform, slam_start_time + ros::Duration(p->_pose._time), "map", "base_link"));	
	}

}

int main(int argc, char **argv)
{
	//----------------Ros Init----------------------------------------------
	ros::init(argc, argv, "indemind_camera");
	ros::NodeHandle n;
	//-----------------------------set Publisher----------------------------
	//-------------IMU|POSE|CAERA-LEFT/RIGHT|DEPTH-IMAGE/CAMERA-------------
	imu_pub = n.advertise<sensor_msgs::Imu>("/module/imu", 100);
	slam_pub = n.advertise<geometry_msgs::Pose>("/module/pose", 10);
	image_l_pub = n.advertise<sensor_msgs::Image>("/module/image_left", 10);
	image_r_pub = n.advertise<sensor_msgs::Image>("/module/image_right", 10);
	depth_pub = n.advertise<sensor_msgs::Image>("/module/depth/image_raw", 10);
	camera_info_pub = n.advertise<sensor_msgs::CameraInfo>("/module/depth/camera_info", 10);

	//-----------------SDK Init---------------------------------------------
    	CIMRSDK* pSDK = new CIMRSDK();
    	MRCONFIG config = { 0 };
	//slam true:open false:close
	config.bSlam = true;
	pSDK->Init(config);

	//------------------get CommandParams Info------------------------------
	CommandParams params;
	//pSDK->InvokePluginMethod("pointCloud","getParams",NULL,&params);
	pSDK->InvokePluginMethod("depthimage","getParams",NULL,&params);
	//-----------another-------------------
	//image_width = params.width;
	//image_height = params.height;
	//camerainfo_msg.height = image_height;
	//camerainfo_msg.width = image_width;
	//-------------------------------------
	for(int i =0;i < 12;++i){
	    camerainfo_msg.P[i] = params.P[i];
	}
	camerainfo_msg.distortion_model = params.distortion_model;
	//-----------------------set callback-----------------------------------
	//------------------SLAM|IMU|CAMERA|DEPTH-------------------------------
	pSDK->RegistModulePoseCallback(sdkSLAMResult,NULL);
	pSDK->RegistModuleIMUCallback(ImuCallBackFunction,NULL);
	pSDK->RegistModuleCameraCallback(CameraCallbackFunction,NULL);
	pSDK->AddPluginCallback("depthimage", "depth", DepthDataCallback, NULL);         
	while(ros::ok())
	{
		ros::spinOnce(); 
	}
	return 0;
}
