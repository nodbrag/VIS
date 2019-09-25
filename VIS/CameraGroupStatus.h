#pragma once
#include <string>
class CameraGroupStatus
{
public:
	CameraGroupStatus();
	~CameraGroupStatus();
	int getVideoFrameRate();
	void setVideoFrameRate(int frameRate);
	void setCameraGroupid(int cameraGroupid);
	void setGroupid(int groupid);
	int getCameraGroupid();
	int getGroupid();
private:
	int IrFrameRate;
	int RGBRrameRate;
	std::string IRCameraIp;
	std::string RGBCameraIp; 
	int cameraGroupid;
	int groupid;
};

