#pragma once
#include <string>
using std::string;

class DataParms
{
public:
	DataParms();
	DataParms(string cameraIp, string cameraPass,int type,string idCode, string personCode, int gunStopID,int x,int y,int width,int height,string imagedatas,int imageFormart);
	DataParms(string cameraIp, string cameraPass, int type, string idCode, string personCode, int dryischeck, int cleanStatus, string cleanStartTime, string cleanEndTime, string tankType,int gunStopID, int x, int y, int width, int height, string imagedatas, int imageFormart);
	~DataParms(void);
	//���������ip
	void setCameraIp(string cameraIp);
	string getCameraIp();
	string getCameraPass();
	//���������ͨ��
	void setCameraPass(string cameraPass);
	int getType();
	//������Ϣ��� 1����Ա��Ϣ 2���ھ���Ϣ 3��ǹ��Ϣ 4����Һ��Ϣ 5��������Ϣ 10��ͼƬ��Ϣ
	void setType(int type);
	string getIdCode();
	//���ñ�ʶ��(��Ա��ʶ��� �ھ���ʶ��, ����ʶ�� ���� Ϊ��)
	void setIdCode(string idCode);
	int getGunStopID();
	//����ǹʹ��ֹͣ��ʶ (0:��ʼʹ�� 1:����ʹ��) 
	void setGunStopID(int gunStopID);
	int getX();
	//�������Ͻ�X  ����
	void setX(int x);
	int getY();
	//�������Ͻ�Y ����
	void setY(int y);
	int getWidth();
	//����ʶ����ο��
	void setWidth(int width);
	int getHeight();
	//ʶ����θ߶�
	void setHeight(int height);
	string getImageDatas();
	//ͼƬ����
	void setImageDatas(string imagedatas);
	int getImageFormart();
	//ͼƬ��ʽ(0:jpeg,1:png,2:bmp)
	void setImageFormart(int imageFormart);

	string getPersonCode();
	void setPersonCode(string personCode);

	//�ھ���ϴ״̬ 0 ������ϴ 1 ��ʼ��ϴ
	int getCleanStatus();
	void setCleanStatus(int cleanStatus);
	//�ھ���ʼʱ��
	string getCleanStartTime();
	void setCleanStartTime(string cleanstarttime);
	//�ھ�����ʱ��
	string getCleanEndTime();
	void setCleanEndTime(string cleanendtime);
	//��������
	string  getTankType();
	void setTankType(string tankType);
	//�����Ƿ������
	int getDryischeck();
	void setDryischeck(int dryischeck);

private:
	//�����ip
	string _cameraIp;
	//�����ͨ��
	string _cameraPass;
	//��Ϣ��� 1����Ա��Ϣ 2���ھ���Ϣ 3��ǹ��Ϣ 4����Һ��Ϣ 5��������Ϣ 10��ͼƬ��Ϣ
	int _type;
	//��ʶ��(��Ա��ʶ��� �ھ���ʶ��, ����ʶ�� ���� Ϊ��)
	string _idCode;
	//ǹʹ��ֹͣ��ʶ (0:��ʼʹ�� 1:����ʹ��) 
	int  _gunStopID;
	//���Ͻ�X  ����
	int _x;
	//���Ͻ�Y ����
	int _y;
	//ʶ����ο��
	int _width;
	//ʶ����θ߶�
	int _height;
	//ͼƬ����
	string _imagedatas;
	//ͼƬ��ʽ(0:jpeg,1:png,2:bmp)
	int _imageFormart;
	//�ھ�����Աcode��
	string personCode;
	//�ھ���ϴ״̬ 0 ������ϴ 1 ��ʼ��ϴ
	int cleanStatus;
	//�ھ���ʼʱ��
	string cleanStartTime;
	//�ھ�����ʱ��
	string cleanEndTime;
	//��������
	string  tankType;
	//�����Ƿ������
	int dryischeck;
	
	

};

