#pragma once
#include <iostream>
#include <string>
#include  <map>
#include "HCNetSDK.h"
#include "TankGroupStatus.h"
#include "CameraMap.h"

class VideoFrameRate
{
public:
	VideoFrameRate();
	~VideoFrameRate();
	static void Notify(std::string cameraip);//识别通知修改状态
	static std::map<std::string, TankGroupStatus *> groupStatusMap;   //key 曹组id value 曹组状态信息
	static std::map<int, int> frameNumMap; //key 开启槽体数量，value 帧率
	static std::map<std::string, std::string> ipGroupIdMap;  //key 相机id value 曹组id
	static int CleanInfectionNum;
	static int MinFrameNum;
	static int totalFrameNum;
	static int CleanInfectionFrameNum;
	static void StartWork();
	static bool IsEnable;
	//当前开始曹组
	static int WorkSpaceTime;
	//像槽组id  槽组状态信息
	static void UpdateFrameRate();//修改摄像机帧率
	static void intFrameRate(); //初始化帧率;
	static std::map<int, int> deviceFrameNumMap;  //key计算出来的帧数，value 设备修改帧数的key
	static std::map<int, int>  tankGroupCameras; //key 曹组id  曹组相机数量
	static void FrameCovert();
	static int getCurrentFrameNum();  //获取当前帧数
	static std::map<int, int> deviceToFrameNum;
	
};

