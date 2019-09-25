#include "VideoFrameRate.h"

 std::map<std::string, TankGroupStatus*> VideoFrameRate::groupStatusMap;
 std::map<std::string, std::string> VideoFrameRate::ipGroupIdMap;
 int VideoFrameRate::WorkSpaceTime=10;
 bool VideoFrameRate::IsEnable=true;
 int VideoFrameRate::CleanInfectionNum = 0;
 int  VideoFrameRate::MinFrameNum = 5;
 int VideoFrameRate::totalFrameNum=0;
 int VideoFrameRate::CleanInfectionFrameNum=0;
 std::map<int, int> VideoFrameRate::deviceFrameNumMap;
 std::map<int, int> VideoFrameRate::frameNumMap;
 std::map<int, int> VideoFrameRate::deviceToFrameNum;

VideoFrameRate::VideoFrameRate()
{
}

VideoFrameRate::~VideoFrameRate()
{

}

void VideoFrameRate::StartWork() {

  while(VideoFrameRate::IsEnable)
  {
	  std::map<std::string, TankGroupStatus*>::iterator it = VideoFrameRate::groupStatusMap.begin();
	  while (it != VideoFrameRate::groupStatusMap.end())
	  {
		 TankGroupStatus *tgs=it->second;
		 ec::Time time;
		 long timespan = time.diff(tgs->getRecentVITime(), ec::Duration::Minute);
		 //最近识别时间大于一定时间 开始减针
		 if (tgs->getIsWorking()) {
			 if (timespan >VideoFrameRate::WorkSpaceTime){
				 tgs->setIsWorking(false);
				 UpdateFrameRate();
			 }
		 }
		 else
		 {
			 if (timespan <=VideoFrameRate::WorkSpaceTime) {
				 tgs->setIsWorking(true);
				 UpdateFrameRate();
			 }
		  }
		  it++;
	  }
	  Sleep(1000);
  }
}
int VideoFrameRate::getCurrentFrameNum() {

	std::map<std::string, TankGroupStatus*>::iterator it = VideoFrameRate::groupStatusMap.begin();
	int i = 0;
	int workNum = 0;
	int stopNum = 0;
	while (it != VideoFrameRate::groupStatusMap.end())
	{
		i++;
		TankGroupStatus *tgs = it->second;
		int cameraNum = tgs->cameraVector->size();
		if (tgs->getIsWorking()) {
			workNum += cameraNum;
		}
		else {
			stopNum += cameraNum;
		}
		it++;
	}
	int frameNum = workNum!=0?(totalFrameNum - stopNum*VideoFrameRate::MinFrameNum - VideoFrameRate::CleanInfectionNum *CleanInfectionFrameNum) / workNum : VideoFrameRate::MinFrameNum;
	if (frameNum < 5) {
		frameNum = 5;
	}
	if (frameNum >= 25) {
		frameNum = 25;
	}
  return VideoFrameRate::deviceFrameNumMap.find(frameNum)->second;
}
//帧率转换
void VideoFrameRate::FrameCovert() {
	for (int i = 1; i <= 25; i++) {
		int num = 7;
		if (i <2) {
			num = 5;
		}
		else if (i <=3) {
			num = 6;
		}
		else if (i <= 5) {
			num = 7;
		} 
		else if (i <= 7) {
			num = 8;
		}
		else if (i <= 9) {
			num = 9;
		}
		else if (i <= 11) {
			num = 10;
		}
		else if (i <= 15) {
			num = 11;
		}
		else if (i <= 19) {
			num = 12;
		}
		else if (i <= 24) {
			num = 13;
		}
		else if (i == 25) {
			num = 0;
		}
		VideoFrameRate::deviceFrameNumMap.insert(make_pair(i, num));
	}

	VideoFrameRate::deviceToFrameNum.insert(make_pair(5, 1));
	VideoFrameRate::deviceToFrameNum.insert(make_pair(6, 2));
	VideoFrameRate::deviceToFrameNum.insert(make_pair(7, 4));
	VideoFrameRate::deviceToFrameNum.insert(make_pair(8, 6));
	VideoFrameRate::deviceToFrameNum.insert(make_pair(9, 8));
	VideoFrameRate::deviceToFrameNum.insert(make_pair(10, 10));
	VideoFrameRate::deviceToFrameNum.insert(make_pair(11, 12));
	VideoFrameRate::deviceToFrameNum.insert(make_pair(12, 16));
	VideoFrameRate::deviceToFrameNum.insert(make_pair(13, 20));
	VideoFrameRate::deviceToFrameNum.insert(make_pair(0, 25));

}
//根据槽组初始化 工作帧率
void VideoFrameRate::intFrameRate() {
	VideoFrameRate::FrameCovert();
}
//标签识别通知
void VideoFrameRate::Notify(std::string cameraip) {
	if (VideoFrameRate::IsEnable) 
	{
		std::string tankGroupId = VideoFrameRate::ipGroupIdMap.find(cameraip)->second;
		TankGroupStatus *cgs = VideoFrameRate::groupStatusMap.find(tankGroupId)->second;
		ec::Time now;
		cgs->setRecentVITime(now);
	}
}
//修改帧率
void VideoFrameRate::UpdateFrameRate() {
	int frameWorkRate = getCurrentFrameNum();
	int frameStopRate = VideoFrameRate::deviceFrameNumMap.find(VideoFrameRate::MinFrameNum)->second;
	int frameRate = frameStopRate;
	std::map<std::string, TankGroupStatus*>::iterator it = VideoFrameRate::groupStatusMap.begin();
	while (it != VideoFrameRate::groupStatusMap.end())
	{
		TankGroupStatus *tgs = it->second;
		if (tgs->getIsWorking())
		{
			frameRate = frameWorkRate;
		}
		else
		{
			frameRate = frameStopRate;
		}
		std::vector<CameraMap*> *cmvector = tgs->cameraVector;
		for (int i = 0; i < cmvector->size(); i++)
		{
			int Ret;
			NET_DVR_COMPRESSIONCFG_V30  struParams = { 0 };
			DWORD dwReturnLen;
			Ret = NET_DVR_GetDVRConfig(cmvector->at(i)->getUserID(), NET_DVR_GET_COMPRESSCFG_V30, cmvector->at(i)->getCameraPass(), &struParams, sizeof(NET_DVR_COMPRESSIONCFG_V30), &dwReturnLen);
			if (!Ret)
			{
				printf_s("%s", std::string("获取视频参数失败！").c_str());
			}
			else
			{
				//再修改帧率  
				struParams.struNormHighRecordPara.dwVideoFrameRate = frameRate;
				int SetCamera;
				SetCamera = NET_DVR_SetDVRConfig(cmvector->at(i)->getUserID(), NET_DVR_SET_COMPRESSCFG_V30, cmvector->at(i)->getCameraPass(),
					&struParams, sizeof(NET_DVR_COMPRESSIONCFG_V30));
				if (SetCamera)
				{
					printf_s("%s", std::string("修改视频帧率成功!").c_str());
					//修改内存帧数
					cmvector->at(i)->setVideoFrameRate(frameRate);
				}
			}

		}
		it++;
	}
}

