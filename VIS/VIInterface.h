#pragma once
#include <vector>
#include <string.h>
#include "CameraMap.h"
#include "DataParms.h"
#include "TakePhotoParms.h"

class VIInterface{
public:
	//初始化相机信息和识别任务信息
	virtual void InitializeData(map<string, std::vector<CameraMap*>> * camerasMap)=0;
	 //开始识别工作
	virtual void StartWork()=0;
	 //结束识别工作
	virtual void StopWork()=0;
	 //开始拍照  cameraIp:获取图片相机ip cameraPass：相机通道 frequency: 1 仅发生一次图片 0:执行发生图片数据 直到停止  imageFormat:发生图标格式 IsImageDrowBorder:图片是否包含识别物体矩形框
	virtual void StartTakePhoto(TakePhotoParms * takePhotoParms)=0;
	 //停止拍照
	virtual void StopTakePhoto()=0;
	// 发送数据
	 virtual  int SendData(bool IsExcuteSuccess,DataParms * dataParms,std::string errorMsg)=0;
	// 回复命令
	virtual void SendCommond(bool IsExcuteSuccess,int commandType, std::string tankgroupid, std::string errorMsg)=0;
};