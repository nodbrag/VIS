#pragma once
#include <string>
#include "VICoreInterface.h"
using namespace std;

class CameraGroup
{
public:
	CameraGroup(void);
	~CameraGroup(void);
	string getIr_camera_ip();
	void setIr_camera_ip(string ir_camera_ip);
	int   getIr_camera_channal();
	void setIr_camera_channal(int ir_camera_channal);
	string getRgb_camera_ip();
	void setRgb_camera_ip(string rgb_camera_ip);
	int   getRgb_camera_channal();
	void setRgb_camera_channal(int rgb_camera_channal);
	void setGroupid(int groupid);
	int getGroupid();
	void setTank_group_id(string tank_group_id);
	string getTank_group_id();
	//Ëã·¨½Ó¿Ú
	VICoreInterface VICode;
	void initVIParms(int mincommonnum, bool isDrawCode, bool isDrawTail, float decodeInteval, float detectMinArea, float detectMaxArea, int eshiftx, int pshiftx, int bloodMax, float scale, int innerThresh, std::map<int, std::vector<int>> colorval);

private:
	string ir_camera_ip;
	int   ir_camera_channal;
	string rgb_camera_ip;
	int   rgb_camera_channal;
	int groupid;
	string tank_group_id;
	
};

