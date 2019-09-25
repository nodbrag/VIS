#pragma once
#include <vector>
#include <string.h>
#include "CameraMap.h"
#include "DataParms.h"
#include "TakePhotoParms.h"

class VIInterface{
public:
	//��ʼ�������Ϣ��ʶ��������Ϣ
	virtual void InitializeData(map<string, std::vector<CameraMap*>> * camerasMap)=0;
	 //��ʼʶ����
	virtual void StartWork()=0;
	 //����ʶ����
	virtual void StopWork()=0;
	 //��ʼ����  cameraIp:��ȡͼƬ���ip cameraPass�����ͨ�� frequency: 1 ������һ��ͼƬ 0:ִ�з���ͼƬ���� ֱ��ֹͣ  imageFormat:����ͼ���ʽ IsImageDrowBorder:ͼƬ�Ƿ����ʶ��������ο�
	virtual void StartTakePhoto(TakePhotoParms * takePhotoParms)=0;
	 //ֹͣ����
	virtual void StopTakePhoto()=0;
	// ��������
	 virtual  int SendData(bool IsExcuteSuccess,DataParms * dataParms,std::string errorMsg)=0;
	// �ظ�����
	virtual void SendCommond(bool IsExcuteSuccess,int commandType, std::string tankgroupid, std::string errorMsg)=0;
};