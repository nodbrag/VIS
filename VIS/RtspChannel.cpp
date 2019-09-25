#include "RtspChannel.h"

StorgeImgMap * RtspChannel::storgeImgMap = new StorgeImgMap();

RtspChannel::RtspChannel()
{

}

RtspChannel::~RtspChannel()
{

}
long RtspChannel::init(string url) {
	string error;
	long userid = 0;//this->VIInit(error, url);
	if (userid < 0) {
		log->WriteErrorLog("VIInit error:" + error);
		cout << "VIInit error:" + error << endl;
	}
	else {
		log->WriteErrorLog("视频解码接口连接相机已成功！");
		cout << "视频解码接口连接相机已成功！" << endl;
	}
	return userid;
}
long RtspChannel::RealPlay() {
	string error;
	
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	long lRealPlayHandle = sys.wMilliseconds;

	
	long isDecoder = 0;// this->VIVideoDecoder( DeciderType,lRealPlayHandle, error, RtspChannel::VodieCallBack);
	if (isDecoder < 0)
	{
		this->lRealPlayHandle = -1;
		return -1;
		log->WriteErrorLog("VIVideoDecoder error:" + error);
		cout << "VIVideoDecoder error:" + error << endl;
	}
	else {
		this->lRealPlayHandle = lRealPlayHandle;
		return lRealPlayHandle;
		cout << "视频解码成功！" << endl;
	}
	

}
void RtspChannel::VodieCallBack(long lRealHandle, cv::Mat img) {

	//RtspChannel::storgeImgMap->add(lRealHandle, img);

}


