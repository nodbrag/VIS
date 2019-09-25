#include "VIVideoDecoderInterface.h"

VIVideoDecoderInterface::VIVideoDecoderInterface()
{
	ReadRtsp rtsp;
	this->rtsp= rtsp;
}


VIVideoDecoderInterface::~VIVideoDecoderInterface()
{
}

long VIVideoDecoderInterface::VIVideoDecoder(int decoderType, long lRealHandle, std::string &error, VodieCallBack vodieCallBack)
{
	return this->rtsp.VIVideoDecoder(decoderType, lRealHandle, error, vodieCallBack);
}
long VIVideoDecoderInterface::VIInit(std::string &error, std::string ip, std::string url)
{
	return  this->rtsp.VIInit(error,ip,url);
}
