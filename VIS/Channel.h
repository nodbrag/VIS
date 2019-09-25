#pragma once
#include <opencv2\opencv.hpp>
#include "HCNetSDK.h"
#include "plaympeg4.h"
#include "Log.h"
#include <vector>
#include <map>
//#include "ChannelImg.h"
#include "StorgeImgMap.h"
#include "CameraMap.h"
#include "ReadRtsp.h"

using namespace cv; 
using namespace std; 
class Channel
{
public:
	 Channel(ReadRtsp *VIVideoDecoder, int videoDecoderType, LONG lUserID,LONG lChannel,Log *log,bool deviceCapturePicture);
	~Channel(void);
	static void   CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);
	static void CALLBACK DecCBFun(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);
	static void  VodieCallBack (long lRealHandle, cv::Mat mat);
	LONG RealPlay();
	LONG lRealPlayHandle;
	static StorgeImgMap * storgeImgMap;
	static void StopRealPlay(std::map<long, CameraMap*> *cmlist);
private:
	LONG lUserID;
	LONG lChannel;
	Log *log;
	long imgChange;
};



