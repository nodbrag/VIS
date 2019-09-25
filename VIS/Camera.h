#pragma once
#include <opencv2\opencv.hpp>
#include "HCNetSDK.h"
#include <time.h>
#include <vector>
#include <string.h>
#include "Log.h"
#include "Channel.h"
#include "ReadRtsp.h"

using namespace std;
using namespace cv;  

class Camera
{
public:
	Camera(ReadRtsp *VIVideoDecoder,int decoderType,string ip,string loginname,string pwd  ,Log *log);
	~Camera(void);
	void initInfo();
	LONG login(string ip,string admin,string pwd);
	void closeCamera();
	static void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);
	LONG lUserID;
   map<long,Channel *> *channellist;
private:
    volatile int gbHandling;
	string ip;
	string loginname;
	string pwd;
	Log *log;
};

