#include <mutex>
#include <queue>
#include <future>
#include <thread>
#include <iomanip>
#include <fstream>
#include <iostream>

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
	//std::cout << "sdkImuCallBack==" << std::setprecision(10) << time << std::endl;
}

void sdkSLAMResult(int ret, void* pData, void* pParam)
{
	//std::cout << "sdkSLAMResult==" << std::setprecision(10) << ret << std::endl;
}

int main()
{
    using namespace indem;
    CIMRSDK* pSDK = new CIMRSDK();
    MRCONFIG config = { 0 };

    config.bSlam = true;   //true: open slam
    pSDK->Init(config);

    //pSDK->RegistModuleCameraCallback(SdkCameraCallBack,NULL);
    //pSDK->RegistModuleIMUCallback(sdkImuCallBack,NULL);
    //pSDK->RegistModulePoseCallback(sdkSLAMResult,NULL);
    pSDK->AddPluginCallback("depthimage", "depth", DepthImageCallback, NULL);


    std::this_thread::sleep_for(std::chrono::seconds(60 * 60 * 24));
    pSDK->Release();
    delete pSDK;
    std::cout << "-----------------------END--------------------" << std::endl;
     
    return 0;
}
