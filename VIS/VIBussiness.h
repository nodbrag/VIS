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
	 //初始化相机信息和识别任务信息
	 void InitializeData(map<string, std::vector<CameraMap*>> * camerasMap);
	 //开始识别工作
	 void StartWork();
	 //结束识别工作
	 void StopWork();
	 //开始拍照  cameraIp:获取图片相机ip cameraPass：相机通道 frequency: 1 仅发生一次图片 0:执行发生图片数据 直到停止  imageFormat:发生图标格式 IsImageDrowBorder:图片是否包含识别物体矩形框
	 void StartTakePhoto(TakePhotoParms * takePhotoParms);
	 //停止拍照
	 void StopTakePhoto();
	 //模拟数据
	 void SetSimulated(SimulatedData * simulated);
	 //识别方法
	 static void VICallbackFun(T_ARGUMENTS * ta);
	 static void RgbCheckRectangleCallBack (std::string rgbip, cv::Mat img);
	 //RGB检测回掉
	 static void RGBCallBackFun(std::string tankGroupId, std::string rgbIp, std::string irIp, std::string eventType,std::string  TankType,cv::Rect roi, bool isHasPerson);
	 //模拟接口
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
	 //处理换液
	 void DealChangeWater(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs);
	 //处理枪的使用
	 void DealGunUse(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs);
	 //换布
	 void DealChangeFabric(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs);

	 //修改曝光度
	 void UpdateExposureValue(long userid, int value);

	 //修改帧率
	 void UpdateFrameRate(std::string irip, std::string tankgroupid, std::string tankType);

	 void UpdateFrameRateToCamera(long userid, int framevalue);

	 //绑定人员
	 string  BindEndocodePerson(string irip, string tankgroupid, string tanktype, int sx, int sy);

	 //查找上一步流程信息
	 map<string, std::string> findPreSetp(std::string tanktype);
	 static map<string, std::string> findSaticPreSetp(std::string tanktype);
	 //查找当前入镜内code及槽体标识并设置自动出镜标识
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

