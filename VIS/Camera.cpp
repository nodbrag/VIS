#include "Camera.h"



Camera::Camera(ReadRtsp *VIVideoDecoder,int videoDecoderType,string ip,string loginname,string pwd, Log *log)
{
	this->gbHandling=3;
	this->loginname=loginname;
	this->pwd=pwd;
	this->log=log;
	this->ip=ip;
	this->channellist=new map<long, Channel *>();
	//初始化信息
	this->initInfo();

	std::string error;
	//登录摄像头 0 海康登录并cup解码  1 为ffmpeg cup解码  2 为ffmpeg gpu解码
	if (videoDecoderType == 0) {
		this->lUserID = this->login(ip, loginname, pwd);
		if (this->lUserID == -1) {
			if (error.empty()) {
				error = NET_DVR_GetLastError();
			}
		}
	}
	else 
	{
	   std::string url = "rtsp://" + loginname + ":" + pwd + "@" + ip + ":554/h264/ch1/main/av_stream";
	   this->lUserID = VIVideoDecoder->VIInit(error,ip, url);
		
	}
	if(this->lUserID != -1){
		log->WriteTraceLog("camera：["+ip+"] login success.");
		printf_s("%s\r\n", std::string("camera：[" + ip + "] login success.").c_str());
	}
	else
	{
		log->WriteTraceLog("camera：[" + ip + "] login filed."+ error);
		printf_s("%s\r\n", std::string("camera：[" + ip + "] login filed."+error).c_str());
	}
}

Camera::~Camera(void)
{

}
//初始化信息
void Camera::initInfo(){
	// 初始化
	NET_DVR_Init();
	//设置连接时间与重连时间
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
	//---------------------------------------
	
	//设置异常消息回调函数
	NET_DVR_SetExceptionCallBack_V30(0, NULL, Camera::g_ExceptionCallBack, NULL);
}
//登录
LONG Camera::login(string ip,string loginname,string pwd){

	//登录参数，包括设备地址、登录用户、密码等
	NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
	struLoginInfo.bUseAsynLogin = 0; //同步登录方式
	strcpy(struLoginInfo.sDeviceAddress, ip.c_str()); //设备IP地址
	struLoginInfo.wPort = 8000; //设备服务端口
	strcpy(struLoginInfo.sUserName, loginname.c_str()); //设备登录用户名
	strcpy(struLoginInfo.sPassword, pwd.c_str()); //设备登录密码
	//设备信息, 输出参数
	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
	LONG lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	if (lUserID == -1)
	{
		log->WriteErrorLog("camera:["+ip+"] Login failed, error code:"+to_string( NET_DVR_GetLastError()));
		NET_DVR_Cleanup();
	}
	return lUserID;
}
void CALLBACK Camera::g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser){

	char tempbuf[256] = {0};
	switch(dwType)
	{
	case EXCEPTION_RECONNECT: //预览时重连
		//printf("----------reconnect--------%d\n", time(NULL));
		break;
	default:
		break;
	}
}
void Camera::closeCamera(){

	 //关闭预览
	for(int i=0;i<channellist->size();i++){
		NET_DVR_StopRealPlay(channellist->at(i)->lRealPlayHandle);
	}
    //注销用户
    NET_DVR_Logout(lUserID);

    //释放SDK资源
    NET_DVR_Cleanup();

	//释放通道列表对象
	delete channellist;
}