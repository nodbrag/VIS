#include "Camera.h"



Camera::Camera(ReadRtsp *VIVideoDecoder,int videoDecoderType,string ip,string loginname,string pwd, Log *log)
{
	this->gbHandling=3;
	this->loginname=loginname;
	this->pwd=pwd;
	this->log=log;
	this->ip=ip;
	this->channellist=new map<long, Channel *>();
	//��ʼ����Ϣ
	this->initInfo();

	std::string error;
	//��¼����ͷ 0 ������¼��cup����  1 Ϊffmpeg cup����  2 Ϊffmpeg gpu����
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
		log->WriteTraceLog("camera��["+ip+"] login success.");
		printf_s("%s\r\n", std::string("camera��[" + ip + "] login success.").c_str());
	}
	else
	{
		log->WriteTraceLog("camera��[" + ip + "] login filed."+ error);
		printf_s("%s\r\n", std::string("camera��[" + ip + "] login filed."+error).c_str());
	}
}

Camera::~Camera(void)
{

}
//��ʼ����Ϣ
void Camera::initInfo(){
	// ��ʼ��
	NET_DVR_Init();
	//��������ʱ��������ʱ��
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
	//---------------------------------------
	
	//�����쳣��Ϣ�ص�����
	NET_DVR_SetExceptionCallBack_V30(0, NULL, Camera::g_ExceptionCallBack, NULL);
}
//��¼
LONG Camera::login(string ip,string loginname,string pwd){

	//��¼�����������豸��ַ����¼�û��������
	NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
	struLoginInfo.bUseAsynLogin = 0; //ͬ����¼��ʽ
	strcpy(struLoginInfo.sDeviceAddress, ip.c_str()); //�豸IP��ַ
	struLoginInfo.wPort = 8000; //�豸����˿�
	strcpy(struLoginInfo.sUserName, loginname.c_str()); //�豸��¼�û���
	strcpy(struLoginInfo.sPassword, pwd.c_str()); //�豸��¼����
	//�豸��Ϣ, �������
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
	case EXCEPTION_RECONNECT: //Ԥ��ʱ����
		//printf("----------reconnect--------%d\n", time(NULL));
		break;
	default:
		break;
	}
}
void Camera::closeCamera(){

	 //�ر�Ԥ��
	for(int i=0;i<channellist->size();i++){
		NET_DVR_StopRealPlay(channellist->at(i)->lRealPlayHandle);
	}
    //ע���û�
    NET_DVR_Logout(lUserID);

    //�ͷ�SDK��Դ
    NET_DVR_Cleanup();

	//�ͷ�ͨ���б����
	delete channellist;
}