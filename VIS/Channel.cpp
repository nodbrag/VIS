#include "Channel.h"


Channel::Channel(ReadRtsp *VIVideoDecoder, int videoDecoderType, LONG lUserID,LONG lChannel,Log *log,bool IsPreview)
{

	this->lUserID=lUserID;
	this->lChannel=lChannel;
	this->log=log;
	this->imgChange=0;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	long irph = sys.wMilliseconds;
	std::string errormsg;
	if (IsPreview) {
		if (videoDecoderType == 0)
		{
			this->lRealPlayHandle = this->RealPlay();
		}
		else
		{
			this->lRealPlayHandle = VIVideoDecoder->VIVideoDecoder(videoDecoderType, irph, errormsg, Channel::VodieCallBack);
			if (this->lRealPlayHandle == -1) {
				log->WriteErrorLog("video decoder error:" + errormsg);
				printf_s("%s\r\n", "video decoder error:" + errormsg);
			}
			else 
			{
				log->WriteErrorLog("预览成功！");
				printf_s("%s\r\n", "预览成功！");
			}
		}
	}
	else 
	{
		this->lRealPlayHandle = -1;
	}
	

}
StorgeImgMap * Channel::storgeImgMap=new StorgeImgMap();
Channel::~Channel(void)
{

}
void Channel::VodieCallBack(long lRealHandle, cv::Mat pImg)
{
	/*char tmp[10];
	char *cp = tmp;
	sprintf(cp, "%s_%d", "wind",lRealHandle);
	cvNamedWindow(cp, WINDOW_AUTOSIZE);
    cv:imshow(cp, pImg);
	waitKey(10);
	*/
	Channel::storgeImgMap->add(lRealHandle, pImg);

}
LONG Channel::RealPlay(){

	NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
	//struPlayInfo.hPlayWnd = h;         //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
	struPlayInfo.lChannel = this->lChannel;  //预览通道号
	struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
	struPlayInfo.dwLinkMode = 0; //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
	LONG lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo,Channel::fRealDataCallBack , NULL);
	if (lRealPlayHandle < 0)
	{
		log->WriteErrorLog("NET_DVR_RealPlay_V40 error:"+ NET_DVR_GetLastError());
		printf_s("%s\r\n", "NET_DVR_RealPlay_V40 error:" + NET_DVR_GetLastError());
		//NET_DVR_Logout(this->lUserID);
		//NET_DVR_Cleanup();
	}
	else {
		log->WriteErrorLog("预览成功！");
		printf_s("%s\r\n", "预览成功！");
	}
	return lRealPlayHandle;
}
void Channel::StopRealPlay(std::map<long, CameraMap*> *cmlist){

	map<long, CameraMap *>::iterator it;
	it = cmlist->begin();
	while (it != cmlist->end())
	{
		long realHandle = it->first;
		CameraMap * cameraMap = it->second;
		long lUserID = cameraMap->getUserID();
		//关闭预览
		NET_DVR_StopRealPlay(realHandle);
		//注销用户
		NET_DVR_Logout(lUserID);
		it++;
	}
	//释放SDK资源
	NET_DVR_Cleanup();
}
void CALLBACK Channel::fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser){

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD: //系统头

		/*if (!PlayM4_GetPort(&nPort))  //获取播放库未使用的通道号
		{
		break;
		}*/
		//m_iPort = lPort; //第一次回调的是系统头，将获取的播放库port号赋值给全局port，下次回调数据时即使用此port号播放
		if (dwBufSize > 0)
		{
			if (!PlayM4_SetStreamOpenMode(lRealHandle, STREAME_REALTIME))  //设置实时流播放模式
			{
				break;
			}

			if (!PlayM4_OpenStream(lRealHandle, pBuffer, dwBufSize, 10 * 1024 * 1024)) //打开流接口
			{
				break;
			}

			if (!PlayM4_Play(lRealHandle, NULL)) //播放开始
			{
				break;
			}
			if (!PlayM4_SetDecCallBack(lRealHandle, DecCBFun))
			{
				break;
			}
		}
		break;
	case NET_DVR_STREAMDATA:   //码流数据
		if (dwBufSize > 0 && lRealHandle != -1)
		{
			if (!PlayM4_InputData(lRealHandle, pBuffer, dwBufSize))
			{
			
				break;
			}
		}
		break;
	default: //其他数据
		if (dwBufSize > 0 && lRealHandle != -1)
		{
			if (!PlayM4_InputData(lRealHandle, pBuffer, dwBufSize))
			{
				break;
			}
		}
		break;
	}
}
void  CALLBACK Channel::DecCBFun(long lRealHandle, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2){
	// 跳帧
	//if (gbHandling)
	//{
	//    gbHandling--;
	//    return;
	//}

	long lFrameType = pFrameInfo->nType;
	if (lFrameType == T_YV12)
	{

		Mat pImg(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);
		Mat src(pFrameInfo->nHeight + pFrameInfo->nHeight / 2, pFrameInfo->nWidth, CV_8UC1, pBuf);
		cvtColor(src, pImg, CV_YUV2BGR_YV12);
		//cvtColor(src, pImg, CV_YUV2RGBA_YV12);

		//imshow("IPCamera", pImg);
		//waitKey(1);
		//存储通道最新图像信息
		Channel::storgeImgMap->add(lRealHandle,pImg);
	}

	//gbHandling = 3;
}
