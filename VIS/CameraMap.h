#pragma once
#include <string>
#include <map>
#include <vector>
using std::string;
#include "Tank.h"


class CameraMap
{
public:
	CameraMap(void);
	CameraMap(string cameraIp,long cameraPass,string cameraType);
	~CameraMap(void);
	string getCameraIp();
	void setCameraIp(string cameraIp);
	string getCameraType();
	void setCameraType(string cameraType);
	long getCameraPass();
	void setCameraPass(long cameraPass);
	void setTank_group_id(string tank_group_id);
	string getTank_group_id();
	long getUserID();
	void setUserID(long userid);
	int getVideoFrameRate();
	void setVideoFrameRate(int frameRate);
private:
	//摄像机ip
	string _cameraIp;
	//摄像机通道
	long _cameraPass;
	//相机启动类型 rgb 或 ir
	string _cameraType;
	//所属曹组
	string tank_group_id;
	//帧率
	int videoFrameRate;
	//登录用户id
	long userid;
};

