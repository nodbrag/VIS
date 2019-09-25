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
	static void Notify(std::string cameraip);//ʶ��֪ͨ�޸�״̬
	static std::map<std::string, TankGroupStatus *> groupStatusMap;   //key ����id value ����״̬��Ϣ
	static std::map<int, int> frameNumMap; //key ��������������value ֡��
	static std::map<std::string, std::string> ipGroupIdMap;  //key ���id value ����id
	static int CleanInfectionNum;
	static int MinFrameNum;
	static int totalFrameNum;
	static int CleanInfectionFrameNum;
	static void StartWork();
	static bool IsEnable;
	//��ǰ��ʼ����
	static int WorkSpaceTime;
	//�����id  ����״̬��Ϣ
	static void UpdateFrameRate();//�޸������֡��
	static void intFrameRate(); //��ʼ��֡��;
	static std::map<int, int> deviceFrameNumMap;  //key���������֡����value �豸�޸�֡����key
	static std::map<int, int>  tankGroupCameras; //key ����id  �����������
	static void FrameCovert();
	static int getCurrentFrameNum();  //��ȡ��ǰ֡��
	static std::map<int, int> deviceToFrameNum;
	
};

