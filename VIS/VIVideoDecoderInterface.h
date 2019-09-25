#pragma once
#include <string>
#include <opencv2\opencv.hpp>
#include "ReadRtsp.h"


class VIVideoDecoderInterface
{
public:
	VIVideoDecoderInterface();
	~VIVideoDecoderInterface();
	long VIVideoDecoder(int decoderType, long lRealHandle, std::string &error, VodieCallBack vodieCallBack);
	long VIInit(std::string &error, std::string ip, std::string url);
private:
	ReadRtsp rtsp;
};

