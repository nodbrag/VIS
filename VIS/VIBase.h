#pragma once
#include <opencv2\opencv.hpp>
#include "VIInterface.h"
#include "ThreadArguments.h"
#include "SimulatedData.h"
#include "UploadImage.h"

class VIBase:public VIInterface
{
public:
	VIBase(void);
	~VIBase(void);
	//IsExcuteSuccess ����ִ���� ����true �쳣����false dataParms��ʶ�����ݲ������� errorMsg���쳣����
	virtual int SendData(bool IsExcuteSuccess,DataParms * dataParms,std::string errorMsg);
	int SendData(SocketsInterface *ta_sockets,SOCKET ta_client_socket,Log *log,bool IsExcuteSuccess, DataParms * dataParms, std::string errorMsg);
	//��ʼ�������Ϣ��ʶ��������Ϣ
	virtual void InitializeData(map<string, std::vector<CameraMap*>> * camerasMap)=0;
	 //��ʼʶ����
	virtual void StartWork()=0;
	 //����ʶ����
	virtual void StopWork()=0;
	 //��ʼ����  cameraIp:��ȡͼƬ���ip cameraPass�����ͨ�� frequency: 1 ������һ��ͼƬ 0:ִ�з���ͼƬ���� ֱ��ֹͣ  imageFormat:ͼ���ʽ IsImageDrowBorder:ͼƬ�Ƿ����ʶ��������ο�
	virtual void StartTakePhoto(TakePhotoParms * takePhotoParms)=0;
	 //ֹͣ����
	virtual void StopTakePhoto()=0;
	//�ظ����� IsExcuteSuccess ����ִ���� ����true �쳣����false  commandType: 0:��ʼ�� 1:��ʼʶ������ 2������ʶ������  3����ʼ��ȡͼƬ 4��ֹͣ��ȡͼƬ errorMsg���쳣����
	virtual void SendCommond(bool IsExcuteSuccess,int commandType, std::string tankgroupid, std::string errorMsg);
	void VIBase::SendCommond(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, bool IsExcuteSuccess, int commandType, std::string tankgroupid,std::string tanktype, std::string errorMsg);

	//ģ������
	virtual void SetSimulated(SimulatedData * simulated)=0;
	//ʶ���ھ�����
	virtual void DealPersonEndoscope(int type, int dryischeck, string startTime, string endTime, int sx, int sy, std::string tankgroupid,std::string tanktype, UploadImage *ui, cv::Mat rgbImg,cv::Mat irImg, SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log,vector<vector<string>> objs, string ip, string channal, string rgbip, int rgbchannal, int imgwidth, int imgheight)=0;
	//����Һ
	virtual void DealChangeWater(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip,std::string channal, vector<vector<string>> objs) = 0;
	//����ǹ��ʹ��
	virtual void DealGunUse(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs) = 0;
	//������
	virtual void DealChangeFabric(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs) = 0;

	//�޸��ع��
	virtual void UpdateExposureValue(long userid, int value)=0;
	//�޸�֡��
	virtual void UpdateFrameRate(std::string irip, std::string tankgroupid, std::string tankType)=0;
	//������һ����
	virtual map<string, std::string> findPreSetp(std::string tanktype)=0;
	//�ھ�����Աcode
	virtual string  BindEndocodePerson(string irip, string tankgroupid, string tanktype, int sx, int sy)=0;
public:
	Log *log;
	THREAD_ARGUMENTS * currentThread;
	static std::string serverip;
};

