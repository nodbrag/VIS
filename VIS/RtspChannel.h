#pragma once
#include "StorgeImgMap.h"
#include "Log.h"

class RtspChannel
{
public:
	RtspChannel();
	~RtspChannel();
	long RealPlay();
	static void VodieCallBack(long lRealHandle,cv::Mat img);
	long init(string url);
	static StorgeImgMap * storgeImgMap;
	long lRealPlayHandle;
	//void VIVideoDecoder(void(RtspChannel::* VodieCallBack)(long lRealHandle, cv::Mat mat));
	//long VIVideoDecoder(int decoderType,long lRealHandle,string &error, void(* VodieCallBack)(long lRealHandle, cv::Mat mat));
	//long VIInit(string &error, string url);
private:
	Log *log;
};

