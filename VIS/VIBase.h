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
	//IsExcuteSuccess 正常执行完 返回true 异常返回false dataParms：识别数据参数对象 errorMsg：异常错误
	virtual int SendData(bool IsExcuteSuccess,DataParms * dataParms,std::string errorMsg);
	int SendData(SocketsInterface *ta_sockets,SOCKET ta_client_socket,Log *log,bool IsExcuteSuccess, DataParms * dataParms, std::string errorMsg);
	//初始化相机信息和识别任务信息
	virtual void InitializeData(map<string, std::vector<CameraMap*>> * camerasMap)=0;
	 //开始识别工作
	virtual void StartWork()=0;
	 //结束识别工作
	virtual void StopWork()=0;
	 //开始拍照  cameraIp:获取图片相机ip cameraPass：相机通道 frequency: 1 仅发生一次图片 0:执行发生图片数据 直到停止  imageFormat:图标格式 IsImageDrowBorder:图片是否包含识别物体矩形框
	virtual void StartTakePhoto(TakePhotoParms * takePhotoParms)=0;
	 //停止拍照
	virtual void StopTakePhoto()=0;
	//回复命令 IsExcuteSuccess 正常执行完 返回true 异常返回false  commandType: 0:初始化 1:开始识别任务 2：结束识别任务  3：开始获取图片 4：停止获取图片 errorMsg：异常错误
	virtual void SendCommond(bool IsExcuteSuccess,int commandType, std::string tankgroupid, std::string errorMsg);
	void VIBase::SendCommond(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, bool IsExcuteSuccess, int commandType, std::string tankgroupid,std::string tanktype, std::string errorMsg);

	//模拟数据
	virtual void SetSimulated(SimulatedData * simulated)=0;
	//识别内镜方法
	virtual void DealPersonEndoscope(int type, int dryischeck, string startTime, string endTime, int sx, int sy, std::string tankgroupid,std::string tanktype, UploadImage *ui, cv::Mat rgbImg,cv::Mat irImg, SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log,vector<vector<string>> objs, string ip, string channal, string rgbip, int rgbchannal, int imgwidth, int imgheight)=0;
	//处理换液
	virtual void DealChangeWater(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip,std::string channal, vector<vector<string>> objs) = 0;
	//处理枪的使用
	virtual void DealGunUse(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs) = 0;
	//处理换布
	virtual void DealChangeFabric(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs) = 0;

	//修改曝光度
	virtual void UpdateExposureValue(long userid, int value)=0;
	//修改帧率
	virtual void UpdateFrameRate(std::string irip, std::string tankgroupid, std::string tankType)=0;
	//查找上一步骤
	virtual map<string, std::string> findPreSetp(std::string tanktype)=0;
	//内镜绑定人员code
	virtual string  BindEndocodePerson(string irip, string tankgroupid, string tanktype, int sx, int sy)=0;
public:
	Log *log;
	THREAD_ARGUMENTS * currentThread;
	static std::string serverip;
};

