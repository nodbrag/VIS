#pragma once
#include <vector>
#include "VIBase.h";
#include "VISetting.h";
#include "Camera.h";
#include "CameraGroup.h"
#include "VSParms.h"
#include "date.h"
#include "Common.h"
#include "XmlConfig.h"
#include "UploadImage.h"
#include "MyMessageBox.h"
#include "VideoFrameRate.h"
#include "TagStatus.h"
#include "Person.h"
#include "Log.h"


typedef struct TArguments {
	CameraGroup * cg;
	SOCKET ta_client_socket;
	Log *log;
	SocketsInterface *ta_sockets;	
	VIBase *vib;
	UploadImage *ui;
	
} T_ARGUMENTS;
class VIBussiness:public VIBase
{
public:
	VIBussiness(void);
	~VIBussiness(void);
	 //��ʼ�������Ϣ��ʶ��������Ϣ
	 void InitializeData(map<string, std::vector<CameraMap*>> * camerasMap);
	 //��ʼʶ����
	 void StartWork();
	 //����ʶ����
	 void StopWork();
	 //��ʼ����  cameraIp:��ȡͼƬ���ip cameraPass�����ͨ�� frequency: 1 ������һ��ͼƬ 0:ִ�з���ͼƬ���� ֱ��ֹͣ  imageFormat:����ͼ���ʽ IsImageDrowBorder:ͼƬ�Ƿ����ʶ��������ο�
	 void StartTakePhoto(TakePhotoParms * takePhotoParms);
	 //ֹͣ����
	 void StopTakePhoto();
	 //ģ������
	 void SetSimulated(SimulatedData * simulated);
	 //ʶ�𷽷�
	 static void VICallbackFun(T_ARGUMENTS * ta);
	 static void RgbCheckRectangleCallBack (std::string rgbip, cv::Mat img);
	 //RGB���ص�
	 static void RGBCallBackFun(std::string tankGroupId, std::string rgbIp, std::string irIp, std::string eventType,std::string  TankType,cv::Rect roi, bool isHasPerson);
	 //ģ��ӿ�
	 int viCall(string rgbId, Mat rgbImg, string irId, Mat irImg, vector<int> flags, map<int, vector<Rect> > roiRects, Mat *overlayImg, map<int, vector<vector<string> > > objs, string errorMsg);
	 static VISetting *visetting;
	 static map<std::string,vector<Tank *>> * tankmap;
	 static std::vector<CameraGroup *> *cgvector;
	 static vector<string> *tankgroupids;
	 static std::map<string, vector<std::string>> *flowtypemap;
	 static long getRealHandleId(string ip,int channelid);
	 static Mat getOverlayImg();
	 static void setOverlayImg(Mat img);
	 static  VSParms *vsparms;
	 void DealPersonEndoscope(int type, int dryischeck, string startTime, string endTime, int sx, int sy, std::string tankgroupid, std::string tanktype, UploadImage *ui, Mat rgbImg, Mat irImg,SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log,vector<vector<string>> objs,string ip,string channal,string rgbip,int rgbchannal,int imgwidth,int imgheight);
	 //����Һ
	 void DealChangeWater(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs);
	 //����ǹ��ʹ��
	 void DealGunUse(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs);
	 //����
	 void DealChangeFabric(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs);

	 //�޸��ع��
	 void UpdateExposureValue(long userid, int value);

	 //�޸�֡��
	 void UpdateFrameRate(std::string irip, std::string tankgroupid, std::string tankType);

	 void UpdateFrameRateToCamera(long userid, int framevalue);

	 //����Ա
	 string  BindEndocodePerson(string irip, string tankgroupid, string tanktype, int sx, int sy);

	 //������һ��������Ϣ
	 map<string, std::string> findPreSetp(std::string tanktype);
	 static map<string, std::string> findSaticPreSetp(std::string tanktype);
	 //���ҵ�ǰ�뾵��code�������ʶ�������Զ�������ʶ
	 static void SetAutostopTankIDAndIP(std::string tankgroupid, string workstep, map<string, string> curcode);
	 static string findFirstStep();
	 static long errornum;
	 static long totalnum;

private:
	static map<string,Camera *> *cameralist;
	static std::map<long,CameraMap*> *handleCameralist;
	static bool isTakePictrueStop;
	static bool isVideTracking;
	static std::string TrackingIp;
	static SimulatedData *simulated;
	static bool isStartWork;
	static map<string,vector<int>> taskflags;
	static map<string,map<int, vector<Rect>>> roiRects;
	static map<int, map<string, map<string, cv::Rect>>> CheckRects;
	static map<long,vector<long>> groupidRealhandles;
	static Mat overlayImg;
	static int overlayChangeCount;
	static map<string,map<long,vector<Rect>>> rgbTrackingRect;
	static XmlConfig config;
	static int MaxIrTankWidth;
	static map<string, map<string,TagStatus>> tagStatusMap;
	static map<string, map<string, int>> exposureMap;
	static map<string, Person> personMap;
	static map<string, int> curFrameRate;
	static map<string, int> curExposure;
	static map<string,map<string, string>> curworkstep;
	static map<string, string> worksetpnamemap;
	static map<string, map<string, string>> GroupidTankIPMap;
	static Log slog;
	static std::map<string, map<string, string>>  TankTypeToIP;
	static std::map<string, int> DryTankClearCount;
	static string curIdentifyCodeIP;
	static vector<string> AutoInfectionTypeAndID;
	static map<string, string> DryTankTypeAndIDMap; 
	static map<string, string> dryIRIPMap;
	
};

