#include <mutex>
#include <queue>
#include <thread>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include "imrsdk.h"

struct ImrDepthImageTarget
{
	float _cubesize;
	int _image_w;
	int _image_h;
	float* _deepptr;
};

void DepthImageCallback(int ret, void* pData, void* pParam) {
	ImrDepthImageTarget* Depth = reinterpret_cast<ImrDepthImageTarget*>(pData);
        //std::cout << "DepthImageCallback==" << std::setprecision(10) << Depth->_image_w << ", _image_h" << Depth->_image_h << std::endl;
}

void  SdkCameraCallBack(double time, unsigned char* pLeft, unsigned char* pRight, int width, int height, int channel, void* pParam)
{
	//std::cout << "SdkCameraCallBack==" << std::setprecision(10) << time << std::endl;
}

void sdkImuCallBack(double time, float accX, float accY, float accZ, float gyrX, float gyrY, float gyrZ, void* pParam)
{
	//std::cout << "sdkImuCallBack==" << time << std::endl;
}

void sdkSLAMResult(int ret, void* pData, void* pParam)
{
    ImrModulePose* pose = (ImrModulePose*)pData;
    std::cout << "SLAM: "<<pose->_pose._position[0] << "," << pose->_pose._position[1]  << "," << pose->_pose._position[2] << ","<< pose->_pose._oula[0] << "," << pose->_pose._oula[1]  << "," << pose->_pose._oula[2]  << std::endl;
}

int main()
{
    using namespace indem;
    CIMRSDK* pSDK = new CIMRSDK();
    MRCONFIG config = { 0 };

    config.bSlam = true;   //true: open slam
    pSDK->Init(config);

    pSDK->RegistModuleCameraCallback(SdkCameraCallBack,NULL);
    pSDK->RegistModuleIMUCallback(sdkImuCallBack,NULL);
    pSDK->RegistModulePoseCallback(sdkSLAMResult,NULL);
//   pSDK->AddPluginCallback("depthimage", "depth", DepthImageCallback, NULL);


    std::this_thread::sleep_for(std::chrono::seconds(60 * 60 * 24));
    pSDK->Release();
    delete pSDK;
    std::cout << "-----------------------END--------------------" << std::endl;
     
    return 0;
}
