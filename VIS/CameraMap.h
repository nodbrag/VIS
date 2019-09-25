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
	//�����ip
	string _cameraIp;
	//�����ͨ��
	long _cameraPass;
	//����������� rgb �� ir
	string _cameraType;
	//��������
	string tank_group_id;
	//֡��
	int videoFrameRate;
	//��¼�û�id
	long userid;
};

