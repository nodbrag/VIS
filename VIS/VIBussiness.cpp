#include <opencv2/opencv.hpp>
#include <vector>
#include "VIBussiness.h"
#include "Command.h"
#include "ZBase64.h"
#include "Channel.h"
#include <mutex>
#include "ReadRtsp.h"



using namespace cv;
using namespace std;



enum TankType_v1 {
	/// <summary>
	/// 测漏
	/// </summary>
	TankType_v1_001,

	/// <summary>
	/// 初洗
	/// </summary>
	TankType_v1_002,

	/// <summary>
	/// 酶洗
	/// </summary>
	TankType_v1_003,    

	/// <summary>
	/// 次洗
	/// </summary>
	TankType_v1_004,

	/// <summary>
	/// 消毒
	/// </summary>
	TankType_v1_005,

	/// <summary>
	/// 末洗
	/// </summary>
	TankType_v1_006,

	/// <summary>
	/// 干燥
	/// </summary>
	TankType_v1_007,
	/// <summary>
	/// 消毒机
	/// </summary>
	TankType_v1_008
};
char * TankType_v1_Array[8]={"TankType_v1_001","TankType_v1_002","TankType_v1_003","TankType_v1_004","TankType_v1_005","TankType_v1_006","TankType_v1_007","TankType_v1_008"};
enum TankType_v2 {
	/// <summary>
	/// 测漏
	/// </summary>
	TankType_v2_001,

	/// <summary>
	/// 清洗
	/// </summary>
	TankType_v2_002,

	/// <summary>
	/// 漂洗
	/// </summary>
	TankType_v2_003,

	/// <summary>
	/// 消毒
	/// </summary>
	TankType_v2_005,

	/// <summary>
	/// 末洗
	/// </summary>
	TankType_v2_006,

	/// <summary>
	/// 干燥
	/// </summary>
	TankType_v2_007,

	/// <summary>
	/// 消毒机
	/// </summary>
	TankType_v2_008
};

char * TankType_v2_Array[7]={"TankType_v2_001","TankType_v2_002","TankType_v2_003","TankType_v2_005","TankType_v2_006","TankType_v2_007","TankType_v2_008"};

std::mutex mutexlock2;

//初始化集合对象开始

//模拟数据
SimulatedData *VIBussiness::simulated = new SimulatedData("10001", 10, 10);
//曹组信息
vector<string> *VIBussiness::tankgroupids = new vector<string>();
//识别设置信息
VISetting *VIBussiness::visetting = new VISetting();
//识别参数信息
VSParms *VIBussiness::vsparms = new VSParms();
//槽体信息 key 相机IP value 槽体信息
map<std::string, vector<Tank *>> *VIBussiness::tankmap = new map<std::string, vector<Tank *>>();

//槽体流程
std::map<string, vector<std::string>> * VIBussiness::flowtypemap = new std::map<string, vector<std::string>>();

//容器变量 开始
map<string, Camera *> *VIBussiness::cameralist=new map<string,Camera *>();
std::map<long,CameraMap*> *VIBussiness::handleCameralist=new std::map<long,CameraMap*>();
//key 相机组id 和 value  打开摄像头预览句柄realhandle
map<long,vector<long>> VIBussiness::groupidRealhandles;
//相机组
std::vector<CameraGroup *> *VIBussiness::cgvector=new std::vector<CameraGroup *>();
bool VIBussiness::isTakePictrueStop=false;
//RGB跟踪 标识
bool VIBussiness::isVideTracking=false;
//是否开始识别工作
bool VIBussiness::isStartWork = false;
//追溯ip
std::string VIBussiness::TrackingIp = "";
//key,曹组编号,任务标识
map<string,vector<int>> VIBussiness::taskflags;
//key string 曹组id,感兴趣坐标
map<string,map<int, vector<Rect>>> VIBussiness::roiRects;

//检查ir及RGB 区域  第一key为 ir或rgb  第二key 为 ip  第三key 为槽体类型  value 区域
map<int, map<string,map<string,cv::Rect>>> VIBussiness::CheckRects;
//第一个曹组id 第二个key 槽体类型 value ip；
map<string, map<string, string>> VIBussiness::GroupidTankIPMap;

// 第一key 为曹组id 第二key 槽类型 值 标签状态
map<string, map<string, TagStatus>> VIBussiness::tagStatusMap;

//第一key 为曹组id 第二key 槽类型 值 为曝光值
 map<string, map<string, int>> VIBussiness::exposureMap;

//RGB 追踪 存储 对应 感兴趣位置  key 预览句柄 value 感兴趣区域
map<string,map<long, vector<Rect>>> VIBussiness::rgbTrackingRect;

// 第一个key 曹组id 第二个为草类型 value 上一次清洗的内镜编码
map<string, map<string, string>> VIBussiness::curworkstep;

std::map<string, map<string, string>>  VIBussiness::TankTypeToIP;

map<string, string> VIBussiness::worksetpnamemap;
//key 人员编码  value识别的人员信息
map<string, Person> VIBussiness::personMap;
//记录当前槽体对应的帧率
map<string, int> VIBussiness::curFrameRate;
//记录当前槽体对应的曝光
map<string, int> VIBussiness::curExposure;
Log VIBussiness::slog(Common::GetLogPath());
long VIBussiness::errornum = 0;
long VIBussiness::totalnum = 0;
//当前识别编码相机ip 针对演示1条内镜
string VIBussiness::curIdentifyCodeIP="";
//画框mat对象
Mat VIBussiness::overlayImg;
int VIBussiness::overlayChangeCount;
int VIBussiness::MaxIrTankWidth=0;
std::map<string, int> VIBussiness::DryTankClearCount;
vector<string> VIBussiness::AutoInfectionTypeAndID;
//key 曹组编号  value 曹组类型及编码
map<string, string> VIBussiness::DryTankTypeAndIDMap; 
//存储干燥台irip；
map<string, string> VIBussiness::dryIRIPMap;
//配置文件
XmlConfig  VIBussiness::config;

VIBussiness::VIBussiness(void){}
VIBussiness::~VIBussiness(void){}

//初始化相机信息和识别任务信息
void VIBussiness::InitializeData(map<string, std::vector<CameraMap*>> * camerasMap){
	try
	{
		VIBussiness::isStartWork = false;
		UploadImage::isUploadThread = false;
		VideoFrameRate::WorkSpaceTime = VIBussiness::vsparms->getWorkSpaceTime();
		VideoFrameRate::MinFrameNum = VIBussiness::vsparms->getMinFrameNum();
		VideoFrameRate::totalFrameNum= VIBussiness::vsparms->getTotalFrameNum();
		VideoFrameRate::CleanInfectionFrameNum= VIBussiness::vsparms->getCleanInfectionMachineFrameNum();
		VideoFrameRate::IsEnable = VIBussiness::vsparms->getIsDynamicSetFrameRate();
		VIBase::serverip=Common::getLocalHostIp();
		Sleep(5 * 1000);
		//相机
		Camera * camera;
		//通道
		Channel *channel;

		bool a = VIBussiness::visetting->getIsEndoscopeIdentified();

		//静态集合每次初始化都要清空
		//Channel::StopRealPlay(VIBussiness::handleCameralist);
		//VIBussiness::handleCameralist->clear();
		//VIBussiness::cameralist->clear();
		VIBussiness::roiRects.clear();
		VIBussiness::taskflags.clear();
		VIBussiness::groupidRealhandles.clear();
		VIBussiness::rgbTrackingRect.clear();
		VideoFrameRate::ipGroupIdMap.clear();
		VideoFrameRate::groupStatusMap.clear();
		VIBussiness::DryTankTypeAndIDMap.clear();
		VIBussiness::dryIRIPMap.clear();
		//Channel::storgeImgMap->Imgmaps->clear();
		bool IsPreview = true;
		VIBussiness::CheckRects.clear();
		map<string, map<string, cv::Rect>> ipmap;
		VIBussiness::CheckRects.insert(make_pair(0, ipmap));
		VIBussiness::CheckRects.insert(make_pair(1, ipmap));

		//初始化映射帧率
		VideoFrameRate::intFrameRate();

		CEndoCore::SetFlow(VIBussiness::flowtypemap);

		VIBussiness::worksetpnamemap.insert(make_pair("TankType_v1_001", "测漏"));
		VIBussiness::worksetpnamemap.insert(make_pair("TankType_v1_002", "初洗"));
		VIBussiness::worksetpnamemap.insert(make_pair("TankType_v1_003", "清洗"));
		VIBussiness::worksetpnamemap.insert(make_pair("TankType_v1_004", "漂洗"));
		VIBussiness::worksetpnamemap.insert(make_pair("TankType_v1_005", "消毒"));
		VIBussiness::worksetpnamemap.insert(make_pair("TankType_v1_006", "末洗"));
		VIBussiness::worksetpnamemap.insert(make_pair("TankType_v1_007", "干燥"));
		VIBussiness::worksetpnamemap.insert(make_pair("TankType_v1_008", "自动消毒机"));
		
		//初始化帧率情况

		//遍历曹组
		for (int n = 0; n < tankgroupids->size(); n++) {

			string tank_group_id = tankgroupids->at(n);
			map<string, string> pertankWork;
			VIBussiness::curworkstep.insert(make_pair(tank_group_id, pertankWork));

			TankGroupStatus *tgs=new TankGroupStatus();
			tgs->setTank_group_id(tank_group_id);
			vector<CameraMap*> *cameravector=new vector<CameraMap*>();
			//根据曹组id 找到对应的相机列表
			std::vector<CameraMap*> camerMaplist = camerasMap->find(tank_group_id)->second;
			//任务vector
			vector<int> taskvector;
			//任务感兴趣
			map<int, vector<Rect>> taskRectMap;

			//RGB 追踪 预览句柄对应的感兴趣坐标
			map<long, vector<Rect>> realHandleRectVector;
			
			//ReadRtsp readrstp;
			Sleep(500);
			//遍历相机列表
			for (int j = 0; j<camerMaplist.size(); j++) {

				CameraMap* cameramap = camerMaplist.at(j);

				ReadRtsp *readrstp = new  ReadRtsp();
				//创建相机
				if (VIBussiness::cameralist->count(cameramap->getCameraIp()) == 0)
				{
					camera = new Camera(readrstp,VIBussiness::vsparms->getVideoDecoder(),cameramap->getCameraIp(), "admin", "infecon123", this->currentThread->ta_server_log);
				}
				else
				{
					camera = VIBussiness::cameralist->find(cameramap->getCameraIp())->second;
				}
				if (camera->lUserID != -1) 
				{
					


					if (camera->channellist->count(cameramap->getCameraPass()) == 0) {

						if (VIBussiness::vsparms->getDeviceCapturePicture() == 1 && cameramap->getCameraType() == "RGB")
						{
							IsPreview = false;
						}
						else
						{ 
							IsPreview = true;
						}
						
						channel = new Channel(readrstp,VIBussiness::vsparms->getVideoDecoder(), camera->lUserID, cameramap->getCameraPass(), this->currentThread->ta_server_log, IsPreview);
						camera->channellist->insert(make_pair(cameramap->getCameraPass(), channel));
						cameramap->setUserID(camera->lUserID);
						VIBussiness::handleCameralist->insert(make_pair(channel->lRealPlayHandle, cameramap));
						VIBussiness::cameralist->insert(make_pair(cameramap->getCameraIp(), camera));
						//初始化容器
						ChannelImg * channelimg = new ChannelImg();
						channelimg->setlRealPlayHandle(channel->lRealPlayHandle);
						channelimg->setImg(Mat(0, 0, CV_8UC3));
						Channel::storgeImgMap->Imgmaps->insert(make_pair(channel->lRealPlayHandle, channelimg));
						//初始化rgb监测对象
						if (cameramap->getCameraType() == "RGB") {
							ec::Time now;
							Channel::storgeImgMap->RgbMonitor.insert(make_pair(channel->lRealPlayHandle, now));
						}

					}
					else
					{
						channel = camera->channellist->find(cameramap->getCameraPass())->second;
					}
					cameravector->push_back(cameramap);
					VideoFrameRate::ipGroupIdMap.insert(make_pair(cameramap->getCameraIp(), tank_group_id));
					
					/* 任务标识：0：内镜标识识别	1：人员标识识别2：气水枪使用检测	3：酶洗槽换液检测	4：消毒槽换液检测5：干燥台换布检测100：RGB跟踪	*/
					/*感兴趣坐标
					0：内镜标识识别   ir->2坐标-取包括的所有槽体 min-2-ltx min-2-lty max-2-rbx max-2-rby
					1：人员标识识别   ir->2坐标-取包括的所有槽体 min-2-ltx min-2-lty max-2-rbx max-2-rby
					2：气水枪使用检测 rgb->2坐标-取包括的所有槽体 min-2-ltx min-2-lty max-2-rbx max-2-rby
					3：酶洗槽换液检测 rgb->1坐标-取酶洗槽体 1-ltx 1-lty 1-rbx 1-rby
					4：消毒槽换液检测 rgb->1坐标-取消毒槽体 1-ltx 1-lty 1-rbx 1-rby
					5：干燥台换布检测 rgb->1坐标-取干燥槽体 1-ltx 1-lty 1-rbx 1-rby
					100：RGB跟踪      rgb->2坐标-取包括的所有槽体 min-2-ltx min-2-lty max-2-rbx max-2-rby
					*/
					vector<Tank *> tankvector = VIBussiness::tankmap->find(cameramap->getCameraIp())->second;

					int minltx = 0, minlty = 0, maxrbx = 0, maxrby = 0;
					vector<Rect> rectenzymevect;
					vector<Rect> rectInfectionVect;
					vector<Rect> rectDryVect;
					for (int i = 0; i<tankvector.size(); i++) {
						Tank *tank = tankvector.at(i);

						if (tank->getTank_type().compare("TankType_v1_007") == 0) {
						
							//初始化干燥台ip；
							if (cameramap->getCameraType() == "IR"&&VIBussiness::dryIRIPMap.count(cameramap->getCameraIp())==0) {

								VIBussiness::dryIRIPMap.insert(make_pair(cameramap->getCameraIp(),cameramap->getCameraIp()));
							}
							//记录每一组对应干燥台唯一号
							if(VIBussiness::DryTankTypeAndIDMap.count(tank->getTank_group_id())==0)
							VIBussiness::DryTankTypeAndIDMap.insert(make_pair(tank->getTank_group_id(),tank->getTank_type() + "_" + to_string(tank->getTank_id())));
						}
						//记录所有的消毒机编号队列
						if (tank->getTank_type().compare("TankType_v1_008") == 0) {
							AutoInfectionTypeAndID.push_back(tank->getTank_type() + "_" + to_string(tank->getTank_id()));
						}

						//默认当前曝光值
						if (VIBussiness::exposureMap.count(tank_group_id) == 0) {
							map<string, int> tankexposure;
							tankexposure.insert(make_pair(tank->getTank_type() + "_" + to_string(tank->getTank_id()), tank->getExposure_val()));
							VIBussiness::exposureMap.insert(make_pair(tank_group_id, tankexposure));
						}
						else
						{
							VIBussiness::exposureMap.find(tank_group_id)->second.insert(make_pair(tank->getTank_type() + "_" + to_string(tank->getTank_id()), tank->getExposure_val()));
						}

						if (tank->getTank_type() == TankType_v1_Array[TankType_v1::TankType_v1_008])
						{
							VideoFrameRate::CleanInfectionNum ++;
						}
						if (cameramap->getCameraPass() == tank->getCamera_channal()) {

							if (minltx == 0 || minltx>tank->getArea_2_ltx())
								minltx = tank->getArea_2_ltx();
							if (minlty == 0 || minlty>tank->getArea_2_lty())
								minlty = tank->getArea_2_lty();
							if (maxrbx == 0 || maxrbx<tank->getArea_2_rbx())
								maxrbx = tank->getArea_2_rbx();
							if (maxrby == 0 || maxrby<tank->getArea_2_rby())
								maxrby = tank->getArea_2_rby();


							map<string, cv::Rect> tanktypemap;
							Rect rect(tank->getArea_l_ltx(), tank->getArea_1_lty(), tank->getArea_1_rbx() - tank->getArea_l_ltx(), tank->getArea_1_rby() - tank->getArea_1_lty());

							if (cameramap->getCameraType() == "RGB") {
								if (tank->getTank_type() == TankType_v1_Array[TankType_v1::TankType_v1_003] && VIBussiness::visetting->getIsTransferEnzymeLiquidIdentified()) {
									taskvector.push_back(3);
									Rect rect(tank->getArea_l_ltx(), tank->getArea_1_lty(), tank->getArea_1_rbx() - tank->getArea_l_ltx(), tank->getArea_1_rby() - tank->getArea_1_lty());
									rectenzymevect.push_back(rect);
									taskRectMap.insert(make_pair(3, rectenzymevect));
								}
								if ((tank->getTank_type() == TankType_v1_Array[TankType_v1::TankType_v1_005] || tank->getTank_type() == TankType_v2_Array[TankType_v2::TankType_v2_005]) && VIBussiness::visetting->getIsTransferInfectionLiquidIdentified()) {
									taskvector.push_back(4);
									Rect rect(tank->getArea_l_ltx(), tank->getArea_1_lty(), tank->getArea_1_rbx() - tank->getArea_l_ltx(), tank->getArea_1_rby() - tank->getArea_1_lty());
									rectInfectionVect.push_back(rect);
									taskRectMap.insert(make_pair(4, rectInfectionVect));
								}
								if ((tank->getTank_type() == TankType_v1_Array[TankType_v1::TankType_v1_007] || tank->getTank_type() == TankType_v2_Array[TankType_v2::TankType_v2_007]) && VIBussiness::visetting->getIsTransferClothIdentified()) {
									taskvector.push_back(5);

									Rect rect(tank->getArea_l_ltx(), tank->getArea_1_lty(), tank->getArea_1_rbx() - tank->getArea_l_ltx(), tank->getArea_1_rby() - tank->getArea_1_lty());
									rectDryVect.push_back(rect);
									taskRectMap.insert(make_pair(5, rectDryVect));
								}

								if (VIBussiness::CheckRects.find(0)->second.count(tank->getCamera_id()) == 0)
								{
									tanktypemap.insert(make_pair(tank->getTank_type() + "_" + to_string(tank->getTank_id()), rect));
									VIBussiness::CheckRects.find(0)->second.insert(make_pair(tank->getCamera_id(), tanktypemap));
								}
								else
								{
									//如果rgb不检测rgb则不需要给干燥槽体区域
									if (VIBussiness::vsparms->getIsRgbDryCheck()) {

										if (tank->getTank_type().compare("TankType_v1_008") != 0)
										{
											VIBussiness::CheckRects.find(0)->second.find(tank->getCamera_id())->second.insert(make_pair(tank->getTank_type() + "_" + to_string(tank->getTank_id()), rect));
										}
									}
									else {
										//干燥，和消毒机区域排除
										if (tank->getTank_type().compare("TankType_v1_007") != 0&& tank->getTank_type().compare("TankType_v1_008") != 0)
										{
											VIBussiness::CheckRects.find(0)->second.find(tank->getCamera_id())->second.insert(make_pair(tank->getTank_type() + "_" + to_string(tank->getTank_id()), rect));
										}
									}
								}

								if (VIBussiness::GroupidTankIPMap.count(tank->getTank_group_id()) == 0)
								{
									std::map<string, string> tankip;
									VIBussiness::GroupidTankIPMap.insert(make_pair(tank->getTank_group_id(), tankip));
								}
								
								VIBussiness::GroupidTankIPMap.find(tank->getTank_group_id())->second.insert(make_pair(tank->getTank_type() + "_" + to_string(tank->getTank_id()), tank->getCamera_id()));
							}
							if (cameramap->getCameraType() == "IR"){
							
								if (VIBussiness::CheckRects.find(1)->second.count(tank->getCamera_id()) == 0)
								{
									tanktypemap.insert(make_pair(tank->getTank_type() + "_" + to_string(tank->getTank_id()), rect));
									VIBussiness::CheckRects.find(1)->second.insert(make_pair(tank->getCamera_id(), tanktypemap));
								}
								else
								{
									VIBussiness::CheckRects.find(1)->second.find(tank->getCamera_id())->second.insert(make_pair(tank->getTank_type() + "_" + to_string(tank->getTank_id()), rect));
								}
								

								int distance = tank->getArea_1_rbx() - tank->getArea_l_ltx();
								if (distance > VIBussiness::MaxIrTankWidth) {
									VIBussiness::MaxIrTankWidth = distance;
								}
							}
							
						}
					}
					vector<Rect> rectvect;



					//初始化调整帧率rgb 的帧率
					if (cameramap->getCameraType() == "RGB") {
						int frate = VideoFrameRate::deviceFrameNumMap.find(VIBussiness::vsparms->getRgbFrameRate())->second;
						this->UpdateFrameRateToCamera(camera->lUserID, frate);
						VIBussiness::curFrameRate.insert(make_pair(cameramap->getCameraIp(), frate));
					}
					else
					{
						int frate = VideoFrameRate::deviceFrameNumMap.find(VIBussiness::vsparms->getIRMinFrameRate())->second;
						//如果是干燥台ip 则初始化最大帧数
						if (VIBussiness::dryIRIPMap.count(cameramap->getCameraIp())> 0&& VIBussiness::vsparms->getIsDryIRLableIdentification() == 1	) 
						{
							frate = VideoFrameRate::deviceFrameNumMap.find(VIBussiness::vsparms->getIRMaxFrameRate())->second;
						}
						this->UpdateFrameRateToCamera(camera->lUserID, frate);
						//记录当前ip帧率
						VIBussiness::curFrameRate.insert(make_pair(cameramap->getCameraIp(), frate));
					}


					Rect rect(minltx, minlty, maxrbx - minltx, maxrby - minlty);
					rectvect.push_back(rect);
					taskRectMap.clear();
					if (cameramap->getCameraType() == "IR") {
						if (VIBussiness::visetting->getIsEndoscopeIdentified()) {
							taskvector.push_back(0);
							if (taskRectMap.count(0) == 0) {
								taskRectMap.insert(make_pair(0, rectvect));
							}
							
						}
						if (VIBussiness::visetting->getIsPersonIdentified()) {
							taskvector.push_back(1);
							if (taskRectMap.count(1) == 0) {
								taskRectMap.insert(make_pair(1, rectvect));
							}
						}

					}
					else {

						realHandleRectVector.insert(make_pair(channel->lRealPlayHandle, rectvect));
						if (VIBussiness::visetting->getIsGunIdentified()) {
							taskvector.push_back(2);
							if (taskRectMap.count(2) == 0) {
								taskRectMap.insert(make_pair(2, rectvect));
							}
						}
					}
            

					//delete  cameramap;
					VIBussiness::roiRects.insert(make_pair(cameramap->getCameraIp(),taskRectMap));
				}
				else 
				{
					std::string tip = cameramap->getCameraType()+" "+cameramap->getCameraIp()+ "相机登录失败，是否继续？10秒之后默认继续.";
					MyMessageBox mmb;
					int x =  mmb.showDialog(GetForegroundWindow(), tip.c_str(), "错误提示!", 4, 0, 10000);
					if (x == 7) { exit(1); }
				}
				
			}

			tgs->cameraVector = cameravector;
			VideoFrameRate::groupStatusMap.insert(make_pair(tank_group_id, tgs));
			

			VIBussiness::taskflags.insert(make_pair(tank_group_id, taskvector));

			VIBussiness::rgbTrackingRect.insert(make_pair(tank_group_id, realHandleRectVector));
		}
		if (VideoFrameRate::IsEnable) 
		{
			
			VideoFrameRate::UpdateFrameRate();
		}
		/*初始化 相机组id 和 预览句柄对应*/
		//循环相机组
		std::vector<CameraGroup *>::iterator it;
		it = VIBussiness::cgvector->begin();
		int i = 0;
		while (it != VIBussiness::cgvector->end())
		{
			CameraGroup *cg = *it;
			long irRealHandle = VIBussiness::getRealHandleId(cg->getIr_camera_ip(), cg->getIr_camera_channal());
			long rgbRealHandle = VIBussiness::getRealHandleId(cg->getRgb_camera_ip(), cg->getRgb_camera_channal());
			if (irRealHandle != -1) {
				vector<long> realhanlevctor;
				cg->setGroupid(i);
				realhanlevctor.push_back(irRealHandle);
				realhanlevctor.push_back(rgbRealHandle);
				VIBussiness::groupidRealhandles.insert(make_pair(i, realhanlevctor));
				i++;
			}
			else {
				//如果没ir没有登录则把这组踢掉
				VIBussiness::cgvector->erase(it);
				it--;
			}
			it++;
		}
	}
	catch (const std::exception& ex)
	{
		printf_s("%s", std::string(ex.what()).c_str());
	}

	// 初始化rgb检测信息
	CEndoCore::initRgbCheck(VIBussiness::CheckRects.find(0)->second,VIBussiness::RGBCallBackFun);
	
	//初始化之后.
	this->SendCommond(true,0,"","");
}
//回调显示数据
void VIBussiness::RgbCheckRectangleCallBack(std::string rgbip, cv::Mat frameShow) {

	if (VIBussiness::vsparms->getIsDemo()) {
		imshow(rgbip, frameShow);
		waitKey(1);
	}

	if (!VIBussiness::vsparms->getIsPureIRLableIdentification()) {
		if (frameShow.cols > 0 && frameShow.rows > 0) {
			if (VIBussiness::TrackingIp != "") {
				if (VIBussiness::isVideTracking&&VIBussiness::TrackingIp == rgbip) {
					VIBussiness::setOverlayImg(frameShow);
				}
			}
			else {

				if (VIBussiness::isVideTracking&&VIBussiness::curIdentifyCodeIP == rgbip) {
					VIBussiness::setOverlayImg(frameShow);
				}
			}
		}
	}
}
//开始识别工作
void VIBussiness::StartWork() {

	VIBussiness::isStartWork = true;

	this->SendCommond(true, 1, "","");

	int flag = VIBussiness::vsparms->getIsRgbCheck() == 1 ? true : false;

	if (!VIBussiness::vsparms->getIsPureIRLableIdentification()) 
	{
		CEndoCore::setisRgbCheck(flag);
		CEndoCore::setRgbCheckFrameNum(VIBussiness::vsparms->getRgbcheckFrameNum());
		CEndoCore::setEnableShowRect(VIBussiness::vsparms->getIsTest() == 1 ? true : false);
		CEndoCore::setPath(Common::GetCurrentPath());
		CEndoCore::setWeightsPath(VIBussiness::vsparms->getCFG(),VIBussiness::vsparms->getWeights(),VIBussiness::vsparms->getLNames());
		CEndoCore::setIsOutByIshasEndoscope(VIBussiness::vsparms->getIsDemo());
		if (VIBussiness::vsparms->getIsDemo()) {
			CEndoCore::SetEndoscopeDefaultNameForDemo(VIBussiness::vsparms->getDefaultEndoscopeTestNameForDemo());
			CEndoCore::SetPersonDefaultNameForDemo(VIBussiness::vsparms->getUserTestNameForDemo());
		}
		//开启rgb检测线程
		CEndoCore::startRgbCheck(VIBussiness::RgbCheckRectangleCallBack);
	}

	if (flag) {
		CEndoCore::setPath(Common::GetCurrentPath());
		CEndoCore::setWeightsPath(VIBussiness::vsparms->getCFG(), VIBussiness::vsparms->getWeights(), VIBussiness::vsparms->getLNames());
		CEndoCore::loadfile();
		CEndoCore::LoadStereoParam();
		CEndoCore::setUserCodes(VIBussiness::vsparms->getUserCode());
	}
	//上传图片
	UploadImage *ui=new UploadImage();
	if (ui->isUploadimage) {
		ui->start(ui);
	}
	//开启实时更新视频帧率线程
	/*DWORD thread_id;
	if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)VideoFrameRate::StartWork, NULL, 0, (LPDWORD)&thread_id) == NULL) {
		throw (std::runtime_error(std::string("CreateThread() failed")));
		printf_s("%s\r\n", "CreateThread() failed");
	}
	std::string trace_message = std::string("update VideoFrameRate  thread created (TID)" + std::to_string(thread_id));
	this->log->WriteTraceLog(trace_message);
	printf_s("%s\r\n", trace_message.c_str());*/
	
	//循环相机组
	for (int i = 0; i < VIBussiness::cgvector->size(); i++) {

		struct TArguments *ta = (struct TArguments *)malloc(sizeof(struct TArguments));
		if (!ta) {
			printf_s("%s\r\n", std::string("insufficient memory for allocating thread argument structure").c_str());
		}
		CameraGroup * cg = VIBussiness::cgvector->at(i);
		ta->cg =cg;
		VIBussiness *curvib = new  VIBussiness();
		ta->log = this->log;
		ta->ui = ui;
		ta->vib = curvib;
		ta->ta_sockets = this->currentThread->ta_sockets;
		ta->ta_client_socket = this->currentThread->ta_client_socket;
		DWORD thread_id;
		if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)this->VICallbackFun, ta, 0, (LPDWORD)&thread_id) == NULL) {
			throw (std::runtime_error(std::string("CreateThread() failed")));
			printf_s("%s\n\r", std::string("CreateThread() failed").c_str());
		}
		std::string trace_message = std::string(cg->getIr_camera_ip() + cg->getRgb_camera_ip() + "group  thread created (TID) " + std::to_string(thread_id));
		this->log->WriteTraceLog(trace_message);
		printf_s("%s\n\r", trace_message.c_str());
		
	}
}

void VIBussiness::VICallbackFun(T_ARGUMENTS * ta) {

	string rgbId;
	Mat rgbImg = Mat(0, 0, CV_8UC3);
	string irId;
	Mat irImg = Mat(0, 0, CV_8UC3);
	map<int, vector<vector<string>>> objs;
	string errorMsg;
	Mat frameShow;
	CameraGroup *cg = ta->cg;
	map<int, vector<vector<string>>>::iterator it;

	while (VIBussiness::isStartWork)
	{
		try {

			long irRealHandle = VIBussiness::groupidRealhandles.find(cg->getGroupid())->second.at(0);
			long rgbRealHandle = VIBussiness::groupidRealhandles.find(cg->getGroupid())->second.at(1);
			if (VIBussiness::isVideTracking) {
				if (roiRects.find(cg->getIr_camera_ip())->second.count(100) == 0) {
					//任务vector
					vector<int> taskvector;
					//任务感兴趣
					map<int, vector<Rect>> taskRectMap;
					taskRectMap.insert(make_pair(100, VIBussiness::rgbTrackingRect.find(cg->getTank_group_id())->second.find(rgbRealHandle)->second));
					taskvector.push_back(100);
					taskflags.insert(make_pair(cg->getTank_group_id(), taskvector));
					roiRects.insert(make_pair(cg->getIr_camera_ip(), taskRectMap));
				}
			}
			map<long, Mat> imgs = Channel::storgeImgMap->getImg(irRealHandle, rgbRealHandle);
			if (imgs.size() > 0) {
				irImg= Mat(0, 0, CV_8UC3);
				rgbImg = Mat(0, 0, CV_8UC3);
				if (imgs.count(rgbRealHandle) > 0)
					rgbImg = imgs.find(rgbRealHandle)->second;
				if (imgs.count(irRealHandle) > 0)
					irImg = imgs.find(irRealHandle)->second;
				 //rgbId = cg->getRgb_camera_ip() + "_" + to_string(cg->getRgb_camera_channal());
				 //irId = cg->getIr_camera_ip() + "_" + to_string(cg->getIr_camera_channal());

				if (!rgbImg.empty()) {
					//pyrDown(rgbImg, frameShow);
					 //resize(irImg.clone(), frameShow,cv::Size(1280,720));
					frameShow = rgbImg.clone();
				}

				if (irImg.cols > 0 && irImg.rows > 0) {
					//ec::Time now;
					//cout << cg->getIr_camera_ip()<<now.toDate().toString() << endl;
					/*if (VIBussiness::vsparms->getIsTest() == 1) {
						//TickMeter tm;
						//tm.start();
						cg->VICode.viCall(cg->getRgb_camera_ip(), rgbImg, "", irImg, taskflags.find(cg->getTank_group_id())->second, VIBussiness::MaxIrTankWidth*VIBussiness::vsparms->getTankwscale(), roiRects.find(cg->getTank_group_id())->second, frameShow, objs, errorMsg);
						//tm.stop();
						//printf_s("%s\n\r", to_string(tm.getTimeMilli())+"ms");
						ec::Time now;
						long second = now.getUTCFullSeconds();
						long persecond = 0;
						if (persecond != second && second % 20 == 0) {
							persecond = second;
							printf_s("%s\n\r", std::string("识别次数量:" + to_string(VIBussiness::totalnum)).c_str());
							printf_s("%s\n\r", std::string("识别错误数量:" + to_string(VIBussiness::errornum)).c_str());

							if (VIBussiness::totalnum > 0) {
								printf_s("%s\n\r", std::string("识别错误率:" + to_string((VIBussiness::errornum * 100 / VIBussiness::totalnum))).c_str());
							}
						}
						if (cg->getRgb_camera_ip() == "169.254.13.102") {
							if (frameShow.cols > 0 && frameShow.rows > 0) {
								imshow("frameShow2", frameShow);
								waitKey(1);
							}
						}
						if (cg->getRgb_camera_ip() == "169.254.13.104") {
							if (frameShow.cols > 0 && frameShow.rows > 0) {
								imshow("frameShow4", frameShow);
								waitKey(1);
							}
						}
					}
					else
					{
						//try
						//{
							cg->VICode.viCall(cg->getRgb_camera_ip(), rgbImg, "", irImg, taskflags.find(cg->getTank_group_id())->second, VIBussiness::MaxIrTankWidth*VIBussiness::vsparms->getTankwscale(), roiRects.find(cg->getTank_group_id())->second, frameShow, objs, errorMsg);
						//}
						//catch (const std::exception& e)
						//{
						//	printf_s("%s\n\r", std::string(e.what()).c_str());
						//}

					}*/

					if (VIBussiness::vsparms->getIsTrackUser() || VIBussiness::vsparms->getIsPureIRLableIdentification() || (VIBussiness::vsparms->getIsDryIRLableIdentification() && VIBussiness::dryIRIPMap.count(cg->getIr_camera_ip()) > 0))
					{
						try
						{
							cg->VICode.viCall(cg->getRgb_camera_ip(), rgbImg, "", irImg, taskflags.find(cg->getTank_group_id())->second, VIBussiness::MaxIrTankWidth*VIBussiness::vsparms->getTankwscale(), VIBussiness::roiRects.find(cg->getIr_camera_ip())->second, frameShow, objs, errorMsg);
							if (VIBussiness::vsparms->getIsTest() == 1 && VIBussiness::vsparms->getIsPureIRLableIdentification()) {
								if (frameShow.cols > 0 && frameShow.rows > 0) {
									imshow(cg->getRgb_camera_ip(), frameShow);
									waitKey(1);
								}
							}
						}
						catch (const std::exception& e)
						{
							printf_s("调用ir识别：%s\n\r", std::string(e.what()).c_str());
							ta->log->WriteErrorLog("调用ir识别：" + std::string(e.what()));
						}

						if (!objs.empty() && objs.size() > 0) {

							it = objs.begin();

							while (it != objs.end())
							{
								int type = it->first;
								vector<vector<string>> val = it->second;
								switch (type)
								{
								case 0:
									ta->vib->DealPersonEndoscope(0, 0, "", "", 0, 0, cg->getTank_group_id(), "", ta->ui, rgbImg, irImg, ta->ta_sockets, ta->ta_client_socket, ta->log, it->second, cg->getIr_camera_ip(), to_string(cg->getIr_camera_channal()),cg->getRgb_camera_ip(),cg->getRgb_camera_channal(), irImg.cols, irImg.rows);
									break;
								case 2:
									ta->vib->DealGunUse(ta->ta_sockets, ta->ta_client_socket, ta->log, cg->getRgb_camera_ip(), to_string(cg->getRgb_camera_channal()), it->second);
									break;
								case 3:
									ta->vib->DealChangeWater(ta->ta_sockets, ta->ta_client_socket, ta->log, cg->getRgb_camera_ip(), to_string(cg->getRgb_camera_channal()), it->second);
									break;
								case 4:
									ta->vib->DealChangeWater(ta->ta_sockets, ta->ta_client_socket, ta->log, cg->getRgb_camera_ip(), to_string(cg->getRgb_camera_channal()), it->second);
									break;
								case 5:
									ta->vib->DealChangeFabric(ta->ta_sockets, ta->ta_client_socket, ta->log, cg->getRgb_camera_ip(), to_string(cg->getRgb_camera_channal()), it->second);
									break;
								default:
									break;
								}
								it++;
								//大屏显示数据根据编码动态显示。
								if (type == 0)
								{
									for (int n = 0; n < val.size(); n++) {
										vector<string> vstr = val.at(n);
										if (vstr.size() == 3) {

											string code = vstr[0].c_str();
											VIBussiness::totalnum++;
											if (code == "-1" || code == "") {
												VIBussiness::errornum++;
												continue;
											}
											string usercodes = ";" + VIBussiness::vsparms->getUserCode() + ";";
											string::size_type isexist = usercodes.find(";" + code + ";");
											string personCode = "";
											if (isexist = string::npos) {
												VIBussiness::curIdentifyCodeIP = cg->getRgb_camera_ip();
											}
										}
									}
								}
							}
						}
					}
				}
				if (!VIBussiness::vsparms->getIsPureIRLableIdentification())
				{
					try
					{					
						if (rgbImg.cols > 0 && rgbImg.rows > 0) {
							//调用
							cg->VICode.SaveRgbImageMat(rgbImg, cg->getRgb_camera_ip(), cg->getIr_camera_ip(), cg->getTank_group_id());

							//该曹组有槽信息
							if (VIBussiness::tagStatusMap.count(cg->getTank_group_id()) > 0) {

								map<string, TagStatus> tsmap = VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second;
								map<string, TagStatus>::reverse_iterator its;
								its = tsmap.rbegin();
								while (its != tsmap.rend())
								{

									TagStatus ts = its->second;
									std::string tankType = ts.getWorkstep();
									//根据ip，槽类型 找到对应区域
									cv::Rect rect = VIBussiness::roiRects.find(cg->getIr_camera_ip())->second.find(0)->second.at(0);

									std::string irip = ts.getIrIp();
									std::string rgbip = ts.getRgbIp();
									//当前画面跟之前曹组ip是对应 且 镜子在槽里面，并且没有识别出code  之后进行ir检测
									if (irip.compare(cg->getIr_camera_ip()) == 0 && irImg.rows > 0 && irImg.cols > 0) {

										//是否干燥
										if (ts.getIsDray())
										{
											//调整曝光
											int exposureValue = 0;
											if (VIBussiness::exposureMap.count(cg->getTank_group_id()) > 0) {
												if (VIBussiness::exposureMap.find(cg->getTank_group_id())->second.count(tankType) > 0) {
													exposureValue = VIBussiness::exposureMap.find(cg->getTank_group_id())->second.find(tankType)->second;
												}
											}
											if (VIBussiness::cameralist->count(cg->getIr_camera_ip()) > 0 && exposureValue > 0) {
												Camera *camera = VIBussiness::cameralist->find(cg->getIr_camera_ip())->second;
												if (VIBussiness::curExposure.count(cg->getIr_camera_ip()) == 0) {
													VIBussiness::curExposure.insert(make_pair(cg->getIr_camera_ip(), exposureValue));
													ta->vib->UpdateExposureValue(camera->lUserID, exposureValue);
												}
												else
												{
													if (VIBussiness::curExposure.find(cg->getIr_camera_ip())->second != exposureValue) {
														VIBussiness::curExposure.find(cg->getIr_camera_ip())->second = exposureValue;
														ta->vib->UpdateExposureValue(camera->lUserID, exposureValue);
													}
												}
											}
											//调整帧率
											ta->vib->UpdateFrameRate(irip, cg->getTank_group_id(), tankType);

											Mat dismat;
											//调用IR检测

											cg->VICode.IrCheck(rect, cg->getIr_camera_ip(), irImg, dismat, objs, errorMsg);

											if (!objs.empty() && objs.size() > 0 && objs.count(0) > 0 && objs.find(0)->second.size() > 0) {

												it = objs.begin();
												while (it != objs.end())
												{
													int type = it->first;

													switch (type)
													{
													case 0:
														ta->vib->DealPersonEndoscope(3, 0, ts.getStime().toDate().toString(), ts.getEtime(), ts.getSX(), ts.getSY(), cg->getTank_group_id(), tankType, ta->ui, rgbImg, irImg, ta->ta_sockets, ta->ta_client_socket, ta->log, it->second, cg->getIr_camera_ip(), to_string(cg->getIr_camera_channal()), cg->getRgb_camera_ip(), cg->getRgb_camera_channal(), irImg.cols, irImg.rows);
														break;
													default:
														break;
													}
													it++;
												}
											}

											/*if (ts.getStatus() == 1) {
												ec::Time cutime;
												long timespan = cutime.diff(ts.getdryTime(), ec::Duration::Second);
												if (timespan > 5)
												{
													VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setStatus(2);
													VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setdryTime(cutime);
												}
											}*/

											if (ts.getCodes().size()>0) {

												ec::Time ctime;
												long timespans = ctime.diff(ts.getdryTime(), ec::Duration::Second);
												//两分钟自动结束
												int pertime = VIBussiness::vsparms->getPreTime();
												if (pertime == 0) {
													pertime = 120;
												}
												//时间够了或已经检测到了，则结束
												if (timespans > pertime || ts.getCodes().count(ts.getDefalutCode())>0)
												{
													Rect rt = VIBussiness::CheckRects.find(1)->second.find(irip)->second.find(tankType)->second;
													int ex = rt.x + rt.width / 2;
													int ey = rt.y + rt.height + 10;
													VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setStatus(0);
													VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setEtime(ctime.toDate().toString());
													VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setEX(ex);
													VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setEY(ey);
													//调整帧率
													ta->vib->UpdateFrameRate(irip, cg->getTank_group_id(), tankType);
													//移除槽信息
													VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.erase(tankType);

													if (ts.getCodes().count(ts.getDefalutCode()) > 0) {
														vector<vector<string>> data;
														vector<string> res;
														res.push_back(ts.getDefalutCode());
														res.push_back(to_string(ex));
														res.push_back(to_string(ey));
														data.push_back(res);
														ta->vib->DealPersonEndoscope(2, 1, ts.getStime().toDate().toString(), ts.getEtime(), ts.getSX(), ts.getSY(), cg->getTank_group_id(), tankType, ta->ui, rgbImg, irImg, ta->ta_sockets, ta->ta_client_socket, ta->log, data, cg->getIr_camera_ip(), to_string(cg->getIr_camera_channal()), cg->getRgb_camera_ip(), cg->getRgb_camera_channal(), irImg.cols, irImg.rows);
													}
												}
											}

										}
										else
										{
											if (ts.getStatus() == 1)
											{
												//调整曝光
												int exposureValue = 0;
												if (VIBussiness::exposureMap.count(cg->getTank_group_id()) > 0) {
													if (VIBussiness::exposureMap.find(cg->getTank_group_id())->second.count(tankType) > 0) {
														exposureValue = VIBussiness::exposureMap.find(cg->getTank_group_id())->second.find(tankType)->second;
													}
												}
												if (VIBussiness::cameralist->count(cg->getIr_camera_ip()) > 0 && exposureValue > 0) {
													Camera *camera = VIBussiness::cameralist->find(cg->getIr_camera_ip())->second;
													if (VIBussiness::curExposure.count(cg->getIr_camera_ip()) == 0) {
														VIBussiness::curExposure.insert(make_pair(cg->getIr_camera_ip(), exposureValue));
														ta->vib->UpdateExposureValue(camera->lUserID, exposureValue);
													}
													else
													{
														if (VIBussiness::curExposure.find(cg->getIr_camera_ip())->second != exposureValue) {
															VIBussiness::curExposure.find(cg->getIr_camera_ip())->second = exposureValue;
															ta->vib->UpdateExposureValue(camera->lUserID, exposureValue);
														}
													}
												}
												//调整帧率
												ta->vib->UpdateFrameRate(irip, cg->getTank_group_id(), tankType);

												Mat dismat;
												//调用IR检测

												cg->VICode.IrCheck(rect, cg->getIr_camera_ip(), irImg, dismat, objs, errorMsg);
												/*for (int n = 0; n < objs.find(0)->second.size(); n++) {
													cout<< rect.x <<rect.y<< tankType <<" : "<< objs.find(0)->second.at(n)[0]<<endl;
												}
												//如果测试状态
												if (VIBussiness::vsparms->getIsTest() == 1) {

													if (dismat.rows > 0 && dismat.cols > 0) {
														imshow(cg->getIr_camera_ip(), dismat);
														/waitKey(1);
													}
												}*/

												if (!objs.empty() && objs.size() > 0 && objs.count(0) > 0 && objs.find(0)->second.size() > 0) {

													it = objs.begin();
													while (it != objs.end())
													{
														int type = it->first;

														switch (type)
														{
														case 0:
															ta->vib->DealPersonEndoscope(1, 0, ts.getStime().toDate().toString(), ts.getEtime(), ts.getSX(), ts.getSY(), cg->getTank_group_id(), tankType, ta->ui, rgbImg, irImg, ta->ta_sockets, ta->ta_client_socket, ta->log, it->second, cg->getIr_camera_ip(), to_string(cg->getIr_camera_channal()), cg->getRgb_camera_ip(), cg->getRgb_camera_channal(), irImg.cols, irImg.rows);
															break;
														default:
															break;
														}
														it++;
													}
												}
												//如果是干燥不需要推理及预警
												if (ts.getCodes().size()==0)
												{
													ec::Time ctime;
													long timespan = ctime.diff(ts.getSendTime(), ec::Duration::Second);
													//大于5秒 进行推理一次
													if (timespan > VIBussiness::vsparms->getOpenillationTimeBySecond())
													{
														//没识别出来 进行逻辑推理
													   //1.查找在流程中找到上一步流程类型
														map<string, string> steps = ta->vib->findPreSetp(tankType);
														//根据流程类型在状态队列找是否有已经结束镜子 
														map<string, string>::iterator stepit;
														stepit = steps.begin();
														std::string preCode = "";
														if (VIBussiness::vsparms->getIsOpenillation()) {
															//只推理1次
															if (ts.getSkillCount() == 0)
															{
																while (stepit != steps.end())
																{
																	string workstep = stepit->second;
																	if (VIBussiness::curworkstep.find(cg->getTank_group_id())->second.count(workstep) > 0) {
																		preCode = VIBussiness::curworkstep.find(cg->getTank_group_id())->second.find(workstep)->second;
																		//VIBussiness::curworkstep.find(cg->getTank_group_id())->second.erase(workstep);
																	}
																	stepit++;
																}
																VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setSKillCount(1);
																ec::Time t;
																printf_s("已推断code时间：%s\r\n", t.toDate().toString().c_str());
															}
														}
														
														//逻辑推理找到code
														if (!preCode.empty()) {

															//VIBussiness::curIdentifyCodeIP = cg->getRgb_camera_ip();
															//VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setCodes(preCode,ts.getStime().toDate().toString());
															//VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setStatus(2);
															vector<vector<string>> data;
															vector<string> res;
															res.push_back(preCode);
															res.push_back(to_string(ts.getSX()));
															res.push_back(to_string(ts.getSY()));
															data.push_back(res);
															ta->vib->DealPersonEndoscope(1, 0, ts.getStime().toDate().toString(), ts.getEtime(), ts.getSX(), ts.getSY(), cg->getTank_group_id(), tankType, ta->ui, rgbImg, irImg, ta->ta_sockets, ta->ta_client_socket, ta->log, data, cg->getIr_camera_ip(), to_string(cg->getIr_camera_channal()), cg->getRgb_camera_ip(), cg->getRgb_camera_channal(),irImg.cols, irImg.rows);
														}
														else
														{	
															if (VIBussiness::vsparms->getIsDemo()) {
																CEndoCore::SetEndoscopeDefaultNameForDemo(VIBussiness::vsparms->getDefaultEndoscopeTestNameForDemo());
															}
															// 查看间隔时间有没有超过10秒 进行发送提醒命令
															if (timespan > 10) {
																int tipcount = VIBussiness::vsparms->getTipCount();
																if (ts.getTipCount() < tipcount) {
																	//发送预警命令
																	ta->vib->SendCommond(ta->ta_sockets, ta->ta_client_socket, ta->log, true, 300, cg->getTank_group_id(), tankType, "");
																	VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setSendTime(ctime);
																	VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setTipCount(ts.getTipCount() + 1);
																}
															}
														}
													}
												}
											}

											//绑定人
											if (ts.getPersonCode().empty())
											{
												//判断是否已经锁定用户
												if (VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.getPersonlock() != 1) {
													ta->vib->BindEndocodePerson(irip, cg->getTank_group_id(), tankType, ts.getSX(), ts.getSY());
												}
											}
											//识别到ok 则发送坐标
											if (ts.getCodes().size()>0) {
												if (VIBussiness::vsparms->getIsDemo()) {
													CEndoCore::SetEndoscopeDefaultNameForDemo(VIBussiness::vsparms->getEndoscopeTestNameForDemo());
												}
												for (auto &code : ts.getCodes()) {
													if (VIBussiness::DryTankClearCount.count(code.first) > 0) {
													
														VIBussiness::DryTankClearCount.find(code.first)->second = 0;
													}
												}
												//当前内镜已经识别编码 判断上一个槽体中该内镜是否出槽体
												/*if (ts.getAutostopcount() == 0)
												{
													map<string, string> steps = ta->vib->findPreSetp(tankType);
													map<string, string>::iterator stepit;
													stepit = steps.begin();
													while (stepit != steps.end())
													{
														string workstep = stepit->second;
														if (!workstep.empty())
														{
															 VIBussiness::SetAutostopTankIDAndIP(cg->getTank_group_id(), workstep, ts.getCodes());
														}

														stepit++;
													}
													
												}*/
												//10发送中心点坐标
												ec::Time cutime;
												long timespan = cutime.diff(ts.getSendTime(), ec::Duration::Second);
												if (timespan > 10)
												{
													for (auto &code : ts.getCodes()) {
														VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.find(tankType)->second.setSendTime(cutime);
														vector<vector<string>> data;
														vector<string> res;
														res.push_back(code.first);
														res.push_back(to_string(ts.getSX()));
														res.push_back(to_string(ts.getSY()));
														data.push_back(res);
														ec::Time t;
														printf_s("间隔发送坐标%s\r\n", t.toDate().toString().c_str());
														ta->vib->DealPersonEndoscope(2, 0, code.second, ts.getEtime(), ts.getSX(), ts.getSY(), cg->getTank_group_id(), tankType, ta->ui, rgbImg, irImg, ta->ta_sockets, ta->ta_client_socket, ta->log, data, cg->getIr_camera_ip(), to_string(cg->getIr_camera_channal()), cg->getRgb_camera_ip(), cg->getRgb_camera_channal(), irImg.cols, irImg.rows);
													}
												}
											}
											//如果镜子离开 并且已经识别到code 则发生信息 发出镜信号说明肯定是一条内镜 可能多个必须上一条内镜 进入下一个槽体 识别编码则要清除掉
											if (ts.getStatus() == 0)
											{
												//调整帧率
												ta->vib->UpdateFrameRate(irip, cg->getTank_group_id(), tankType);
												//移除槽信息
												VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.erase(tankType);

												if (ts.getCodes().size()==1) {
													std::map<string, std::string> umapcodes = ts.getCodes();
													std::map<string, std::string>::iterator itcodes;
													itcodes = umapcodes.begin();
													string Code = itcodes->first;
													vector<vector<string>> data;
													vector<string> res;
													res.push_back(Code);
													res.push_back(to_string(ts.getEX()));
													res.push_back(to_string(ts.getEY()));
													data.push_back(res);
													ta->vib->DealPersonEndoscope(2, 0, itcodes->second, ts.getEtime(), ts.getSX(), ts.getSY(), cg->getTank_group_id(), tankType, ta->ui, rgbImg, irImg, ta->ta_sockets, ta->ta_client_socket, ta->log, data, cg->getIr_camera_ip(), to_string(cg->getIr_camera_channal()), cg->getRgb_camera_ip(), cg->getRgb_camera_channal(),irImg.cols, irImg.rows);
													//如果rgb不检测干燥台 则自动生成。
													if (!VIBussiness::vsparms->getIsDryIRLableIdentification() &&!VIBussiness::vsparms->getIsRgbDryCheck()) {
														//末洗结束之后  tankType 类型包含末洗
														if (tankType.find("TankType_v1_006") != string::npos)
														{
															std::string nexttanktype = VIBussiness::DryTankTypeAndIDMap.find(cg->getTank_group_id())->second;//"TankType_v1_007";
															Rect rt = VIBussiness::CheckRects.find(1)->second.find(irip)->second.find(nexttanktype)->second;
															if (VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.count(nexttanktype) == 0) {
																ec::Time now;
																TagStatus newts;
																newts.setSTime(now);
																newts.setSX(rt.x + rt.width / 2);
																newts.setSY(rt.y + rt.height / 2);
																newts.setStatus(1);

																newts.setDefaultCode(Code);
																newts.setIrIp(irip);
																newts.setRgbIp(rgbip);
																newts.setWorkstep(nexttanktype);
																newts.setIsDray(1);
																newts.setdryTime(now);
																VIBussiness::tagStatusMap.find(cg->getTank_group_id())->second.insert(make_pair(nexttanktype, newts));
															}

														}
													}
													
												}

											}
										}
									}
									its++;
									Sleep(2);
								}
							}
						}
					}
					catch (const std::exception& e)
					{
						printf_s("rbg 识别逻辑推理：%s\n\r", std::string(e.what()).c_str());
						ta->log->WriteErrorLog("rbg 识别逻辑推理：" + std::string(e.what()));
					}
				}
				if (VIBussiness::vsparms->getIsPureIRLableIdentification()) {
					if (frameShow.cols > 0 && frameShow.rows > 0) {
						if (VIBussiness::TrackingIp != "") {
							if (VIBussiness::isVideTracking&&VIBussiness::TrackingIp == cg->getRgb_camera_ip()) {
								VIBussiness::setOverlayImg(frameShow);
							}
						}
						else {
							if (VIBussiness::isVideTracking&&VIBussiness::curIdentifyCodeIP == cg->getRgb_camera_ip()) {
								VIBussiness::setOverlayImg(frameShow);
							}
						}
					}
				}
			}
		}
		catch (const std::exception& e) {
			printf_s("%s", std::string(e.what()).c_str());
			ta->log->WriteErrorLog("工作识别：" + std::string(e.what()));
		}
		Sleep(40);
	}
}
void VIBussiness::SetAutostopTankIDAndIP(std::string tgid, string workstep,map<string,string> curcode) {

	 map<string, string> tankidandcode;
	 for (auto &tankgroupidmap : VIBussiness::tagStatusMap) {

		 std::string tankgroupid = tankgroupidmap.first;
		 map<string, TagStatus> tst = tankgroupidmap.second;// VIBussiness::tagStatusMap.find(tankgroupid)->second;
		 map<string, TagStatus>::iterator tstit = tst.begin();
		 while (tstit != tst.end()) {

			 std::string tanktypeid = tstit->first;
			 TagStatus ts = tstit->second;
			 //tanktypeid.find(workstep) != string::npos
			 if (tanktypeid.find(workstep) == string::npos) {
				 //只有上一个槽体只有识别到一个内镜时候 code匹配则自动出镜  有个问题 如果内镜识别了一个 还有一未识别则也会自动出镜
				 if (ts.getCodes().size() == 1){
					 
					 for (auto &codemap : ts.getCodes()) {
						 string preCode = codemap.first;
						 if (!preCode.empty()) {

							 if (VIBussiness::GroupidTankIPMap.find(tankgroupid)->second.count(tanktypeid) > 0) {
								 string ip = VIBussiness::GroupidTankIPMap.find(tankgroupid)->second.find(tanktypeid)->second;
								 if (curcode.count(preCode) > 0) {
									 VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktypeid)->second.setAutostopcount(1);
									 if (VIBussiness::DryTankTypeAndIDMap.find(tankgroupid)->second.find(workstep) != string::npos) {
										 VIBussiness::DryTankClearCount.insert(make_pair(preCode, 1));
									 }
									 CEndoCore::setPopEndoscope(ip, tanktypeid);
								 }
							 }
						 }
					 }
				 }
				 //采用移除上一个槽体的编码
				 else if (ts.getCodes().size() > 1) {

					 for (auto &code : ts.getCodes()) {

						 if (curcode.count(code.first) > 0) {

							 VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktypeid)->second.RemoveCode(code.first);
						 }
					 }
				 }
			 }
			 tstit++;
		 }

	 }
}
//查找上步骤 
map<string, std::string> VIBussiness::findPreSetp(std::string curstep) {
	
	map<string, std::string> preStep;
	std::map<string, vector<std::string>>::iterator it;
	it = VIBussiness::flowtypemap->begin();
	while (it!= VIBussiness::flowtypemap->end())
	{
		vector<string> flowtypes=it->second;

		for (int i = 0; i<flowtypes.size(); i++) {

			if (curstep.find(flowtypes.at(i))!=std::string::npos) {

				if (i>0) {
					if (preStep.count(flowtypes.at(i - 1)) == 0) {
						preStep.insert(make_pair(flowtypes.at(i - 1), flowtypes.at(i - 1)));
					}
				}
				break;
			}
		}
		it++;
	}
	return preStep;
}
map<string, std::string> VIBussiness::findSaticPreSetp(std::string curstep) {

	map<string, std::string> preStep;
	std::map<string, vector<std::string>>::iterator it;
	it = VIBussiness::flowtypemap->begin();
	while (it != VIBussiness::flowtypemap->end())
	{
		vector<string> flowtypes = it->second;

		for (int i = 0; i<flowtypes.size(); i++) {

			if (curstep.find(flowtypes.at(i)) != std::string::npos) {

				if (i>0) {
					if (preStep.count(flowtypes.at(i - 1)) == 0) {
						preStep.insert(make_pair(flowtypes.at(i - 1), flowtypes.at(i - 1)));
					}
				}
				break;
			}
		}
		it++;
	}
	return preStep;
}
void  VIBussiness::UpdateFrameRateToCamera(long userid, int framevalue) {

	int Ret;
	NET_DVR_COMPRESSIONCFG_V30  struParams = { 0 };
	DWORD dwReturnLen;
	Ret = NET_DVR_GetDVRConfig(userid, NET_DVR_GET_COMPRESSCFG_V30, 1, &struParams, sizeof(NET_DVR_COMPRESSIONCFG_V30), &dwReturnLen);
	if (!Ret)
	{
		printf_s("%s\r\n", std::string("获取视频参数失败！").c_str());
	}
	else
	{
		//再修改帧率  
		if (struParams.struNormHighRecordPara.dwVideoFrameRate != framevalue)
		{
			struParams.struNormHighRecordPara.dwVideoFrameRate = framevalue;
			int SetCamera=0;
			SetCamera = NET_DVR_SetDVRConfig(userid, NET_DVR_SET_COMPRESSCFG_V30, 1,&struParams, sizeof(NET_DVR_COMPRESSIONCFG_V30));
			if (SetCamera)
			{
				if (VIBussiness::vsparms->getIsTest() == 1) {
					printf_s("%d%s\r\n", framevalue, std::string("-修改视频帧率成功!").c_str());
					printf_s("%s\r\n", "--------------------相机当前帧率如下------------------------");
					for (auto &curfame : VIBussiness::curFrameRate) {

						printf_s("%s\r\n", (curfame.first + " | " + to_string(VideoFrameRate::deviceToFrameNum.find(curfame.second)->second)).c_str());
					}
					printf_s("%s\r\n", "--------------------------------------------");
				}
				
			}
		}
	}

}

void VIBussiness::UpdateFrameRate(std::string irip,std::string tankgroupid, std::string tankType) {
	if (VIBussiness::cameralist->count(irip) > 0) {
		Camera *camera = VIBussiness::cameralist->find(irip)->second;
		long userid = camera->lUserID;
		std::map<string,TagStatus> tsmap = VIBussiness::tagStatusMap.find(tankgroupid)->second;
		int status=VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tankType)->second.getStatus();
		
		if (status == 1) {
		     //如果 1 镜子在槽里 可以考虑升帧率
			
			int frate = VideoFrameRate::deviceFrameNumMap.find(VIBussiness::vsparms->getIRMaxFrameRate())->second;
			int curfrate = VIBussiness::curFrameRate.find(irip)->second;
			if (frate != curfrate)
			{
				VIBussiness::curFrameRate.find(irip)->second = frate;
				UpdateFrameRateToCamera(userid, frate);
			}
		}
		else 
		{
			//镜子离开或镜子编码已经识别出来  考虑进行降帧率

		   //镜子离开 看看ip下面有没有其他镜子在槽体里 或 其他有镜子在槽体里面并有识别编码但 人员编码也识别了
		
			//找到该ip 下对应的槽体状态信息
			//考虑到多内镜同槽，情况 除非都是空槽，才降帧，其他情况不降帧 4-10
			bool iswork = false;
			map<string, TagStatus>::iterator its;
			its = tsmap.begin();
			
			map<string, int> tankmap;
			
			while (its != tsmap.end())
			{
				TagStatus ts = its->second;

				if (ts.getIrIp().compare(irip) == 0) {
					
					if (ts.getStatus() == 1) {
						iswork = true;
					}
					/*else if (ts.getStatus() == 2) {

						if (tankmap.count(ts.getCode()) == 0) {
							int isz = !ts.getPersonCode().empty();
							tankmap.insert(make_pair(ts.getCode(), isz));
						}
						else 
						{
							if (!ts.getPersonCode().empty()) {
								tankmap.find(ts.getCode())->second = 1;
							}
						}
						//考虑多内镜同槽体 识别到一个编码也不能降帧，可能还有别的没识别到 4-10 update
						iswork = true;
					}*/
				}

			 its++;
			}
			//人员检测
			/*if (!iswork) {
				map<string, int>::iterator tkit;
				tkit = tankmap.begin();
				while (tkit != tankmap.end())
				{
					if (!tkit->second) {
						iswork = true;
					}
					tkit++;
				}
			}*/

			int curfrate = VIBussiness::curFrameRate.find(irip)->second;
			int minfrate = VideoFrameRate::deviceFrameNumMap.find(VIBussiness::vsparms->getIRMinFrameRate())->second;
			if (!iswork)
			{
				//降帧率
				if (minfrate != curfrate) {
					if (VIBussiness::vsparms->getIsDryIRLableIdentification() == 1) {
						//不是干燥台ip则降帧率
						if (VIBussiness::dryIRIPMap.count(irip) == 0) {
							VIBussiness::curFrameRate.find(irip)->second = minfrate;
							UpdateFrameRateToCamera(userid, minfrate);
						}
					}
					else
					{
						VIBussiness::curFrameRate.find(irip)->second = minfrate;
						UpdateFrameRateToCamera(userid, minfrate);
					}
				}
			}
		}
		
		
	}
}
void VIBussiness::UpdateExposureValue(long userid, int value) {

	int Ret;
	NET_DVR_CAMERAPARAMCFG  struParams = { 0 };
	DWORD dwReturnLen;
	Ret = NET_DVR_GetDVRConfig(userid, NET_DVR_GET_CCDPARAMCFG, 1, &struParams, sizeof(NET_DVR_CAMERAPARAMCFG), &dwReturnLen);
	if (!Ret)
	{
		std::cout << NET_DVR_GetLastError() << std::endl;
		printf_s("%s\r\n", std::string("获取曝光参数失败！").c_str());
	}
	else
	{
		//再修改帧率  
		struParams.struExposure.dwVideoExposureSet = value;
		int SetCamera=0;
		SetCamera = NET_DVR_SetDVRConfig(userid, NET_DVR_SET_CCDPARAMCFG, 1,&struParams, sizeof(NET_DVR_AEMODECFG));
		if (SetCamera)
		{
			if (VIBussiness::vsparms->getIsTest() == 1) {
				printf_s("%s\r\n", std::string("修改曝光参数成功!").c_str());
			}

		}
	}
}
string VIBussiness::findFirstStep() {
	std::map<string, vector<std::string>>::iterator it;
	it = VIBussiness::flowtypemap->begin();
	return it->second[0];
}
//rgb内镜检查
void VIBussiness::RGBCallBackFun(std::string tankGroupId, std::string rgbIp, std::string irIp, std::string eventType, std::string  tankType, cv::Rect rect,bool isHasPerson) {
	//干燥不要入镜信号 末洗之后默认5秒 开始

	if (!VIBussiness::vsparms->getIsRgbDryCheck()) {
		if (tankType.compare(VIBussiness::DryTankTypeAndIDMap.find(tankGroupId)->second) == 0)
			return;
	}
	ec::Time now;
	string mes = eventType == "0" ? "镜出" : "镜入";
	std::string msg = rgbIp + ":" + now.toDate().toString() + ":" + VIBussiness::worksetpnamemap.find(tankType.substr(0,15))->second + "槽：" + mes;
	printf_s("%s\r\n", msg.c_str());
	slog.WriteTraceLog(msg);
	
	if (VIBussiness::tagStatusMap.count(tankGroupId) == 0) {
		map<string, TagStatus> tsmap;
		VIBussiness::tagStatusMap.insert(make_pair(tankGroupId, tsmap));
	}

	Rect rt = VIBussiness::CheckRects.find(1)->second.find(irIp)->second.find(tankType)->second;
	if (VIBussiness::tagStatusMap.find(tankGroupId)->second.count(tankType) == 0) {
		
		TagStatus ts;
		if (eventType == "1")
		{
			ts.setSTime(now);
			ts.setSX(rt.x + rt.width / 2);
			ts.setSY(rt.y + rt.height / 2);
			ts.setStatus(1);
			ts.setSKillCount(0);
			ts.setAutostopcount(0);
			ts.setTipCount(0);
			if (VIBussiness::vsparms->getIsDemo()) {
				if (isHasPerson) {
					ts.setPersonCode(to_string(VIBussiness::vsparms->getUserTestCodeForDemo()));
					ts.setPersonLock(1);
				}
			}
			else {
				ts.setPersonLock(0);
			}
		}
		ts.setIrIp(irIp);
		ts.setRgbIp(rgbIp);;
		ts.setWorkstep(tankType);
		ts.setIsDray(0);
		VIBussiness::tagStatusMap.find(tankGroupId)->second.insert(make_pair(tankType, ts));
	}
	else
	{
		if (eventType == "0") {
			
			VIBussiness::tagStatusMap.find(tankGroupId)->second.find(tankType)->second.setEtime(now.toDate().toString());
			VIBussiness::tagStatusMap.find(tankGroupId)->second.find(tankType)->second.setEX(rt.x + rt.width / 2);
			VIBussiness::tagStatusMap.find(tankGroupId)->second.find(tankType)->second.setEY(rt.y + rt.height + 10);
			VIBussiness::tagStatusMap.find(tankGroupId)->second.find(tankType)->second.setStatus(0);
			map<std::string,std::string> mapcodes = VIBussiness::tagStatusMap.find(tankGroupId)->second.find(tankType)->second.getCodes();

			if (mapcodes.size()>0)
			{
				for (auto &code : mapcodes) {
					//如果是第一步开始 重置槽体信息
					if (tankType.substr(0, 15).compare(VIBussiness::findFirstStep()) == 0)
					{
						map<string, string>::reverse_iterator itt;
						itt = VIBussiness::curworkstep.find(tankGroupId)->second.rbegin();
						while (itt != VIBussiness::curworkstep.find(tankGroupId)->second.rend())
						{
							if (code.first.compare(itt->second) == 0)
							{
								VIBussiness::curworkstep.find(tankGroupId)->second.erase(itt->first);
							}
							itt++;
						}
					}

					map<string, string> steps = VIBussiness::findSaticPreSetp(tankType);
					map<string, string>::iterator stepit;
					stepit = steps.begin();
					std::string preCode = "";
					while (stepit != steps.end())
					{
						string workstep = stepit->second;
						if (VIBussiness::curworkstep.find(tankGroupId)->second.count(workstep) > 0) {
							preCode = VIBussiness::curworkstep.find(tankGroupId)->second.find(workstep)->second;
							if (code.first.compare(preCode) == 0)
							{
								VIBussiness::curworkstep.find(tankGroupId)->second.erase(workstep);
							}
						}
						stepit++;
					}
				}
				if (mapcodes.size() == 1) {

					//如果是只有一个内镜则获取编号及设置
					std::map<string, std::string>::iterator itcodes;
					itcodes = mapcodes.begin();
					std::string code = itcodes->first;
					
					//镜子离开的时候记录当前槽体最新内镜
					if (VIBussiness::curworkstep.find(tankGroupId)->second.count(tankType.substr(0, 15)) == 0)
					{
						VIBussiness::curworkstep.find(tankGroupId)->second.insert(make_pair(tankType.substr(0, 15), code));
					}
					else
					{
						VIBussiness::curworkstep.find(tankGroupId)->second.find(tankType.substr(0, 15))->second = code;
					}
				}
			}
		}
	}
}
//结束识别工作
void VIBussiness::StopWork(){

	//发送已结束识别命令
	this->SendCommond(true,2,"","");
}

void VIBussiness::StartTakePhoto(TakePhotoParms * takePhotoParms){

	this->SendCommond(true,3,"","");
	DataParms *dataParms;
	int flag=true;
	

	//频次为一次只获取当前相机当前图像信息
	if(takePhotoParms->getFrequency()==1){

		if (VIBussiness::vsparms->getDeviceCapturePicture() == 1) {

			LPNET_DVR_JPEGPARA jpegpara=new NET_DVR_JPEGPARA;
			if (jpegpara != NULL) {
				jpegpara->wPicQuality = 2;
				jpegpara->wPicSize = 5;
			}
			int w = 1280;
			int h = 720;
			int px = w * h;
			char * imgdata = new char[px];
			LPDWORD size = 0;
			vector<uchar>data(px);
			Camera *camera= VIBussiness::cameralist->find(takePhotoParms->getCameraIp())->second;
			
		    long userid= camera->lUserID;
			
			if (!NET_DVR_SetCapturePictureMode(BMP_MODE)) {
				log->WriteErrorLog("NET_DVR_SetCapturePictureMode error code:" + to_string(NET_DVR_GetLastError()));
			}
			bool flag = NET_DVR_CaptureJPEGPicture_NEW(userid, takePhotoParms->getCameraPass(), jpegpara, imgdata, px, size);
			if (!flag) {
				log->WriteErrorLog("NET_DVR_CaptureJPEGPicture_NEW error code:" + to_string(NET_DVR_GetLastError()));
			}

			for (int i = 0; i < px; i++) {
				data[i] = imgdata[i];
			}
			delete imgdata;
			Mat img = imdecode(Mat(data), 1);
			if (img.rows > 0 && img.cols > 0) {
				vector<uchar> vecImg;                               //Mat 图片数据转换为vector<uchar>  
				vector<int> vecCompression_params;
				vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
				if (takePhotoParms->getCompression() > 0) {
					vecCompression_params.push_back(takePhotoParms->getCompression());
				}
				else {
					vecCompression_params.push_back(25);
				}
				imencode(".jpg", img, vecImg, vecCompression_params);
				ZBase64 base64;
				string imgbase64 = base64.Encode(vecImg.data(), vecImg.size());
				dataParms = new DataParms(takePhotoParms->getCameraIp(), to_string(takePhotoParms->getCameraPass()), 10, "","", 0, 0, 0, w, h, imgbase64, 0);
				this->SendData(true, dataParms, "");
				delete dataParms;
			}
		}
		else 
		{
			while (true)
			{
				map<long, CameraMap *>::iterator it;
				it = VIBussiness::handleCameralist->begin();
				while (it != VIBussiness::handleCameralist->end())
				{
					long realHandle = it->first;
					CameraMap * cameraMap = it->second;
					if (cameraMap->getCameraIp() == takePhotoParms->getCameraIp() && cameraMap->getCameraPass() == takePhotoParms->getCameraPass()) {

						Mat img = Channel::storgeImgMap->getImg(realHandle);

						if (img.rows > 0 && img.cols > 0) {
							vector<uchar> vecImg;                               //Mat 图片数据转换为vector<uchar>  
							vector<int> vecCompression_params;
							vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
							if (takePhotoParms->getCompression() > 0) {
								vecCompression_params.push_back(takePhotoParms->getCompression());
							}
							else {
								vecCompression_params.push_back(25);
							}
							imencode(".jpg", img, vecImg, vecCompression_params);
							ZBase64 base64;
							string imgbase64 = base64.Encode(vecImg.data(), vecImg.size());
							CameraMap* cameraMap = VIBussiness::handleCameralist->find(realHandle)->second;
							if (cameraMap->getCameraIp() == takePhotoParms->getCameraIp() && cameraMap->getCameraPass() == takePhotoParms->getCameraPass()) {
								dataParms = new DataParms(cameraMap->getCameraIp(), to_string(cameraMap->getCameraPass()), 10, "","", 0, 0, 0, img.cols, img.rows, imgbase64, 0);
								flag = false;
								this->SendData(true, dataParms, "");
								delete dataParms;
							}
						}
					}
					it++;
				}
				if (!flag) {
					break;
				}

			}
		}
	}
	else
	{
		VIBussiness::TrackingIp = takePhotoParms->getCameraIp();
		VIBussiness::isTakePictrueStop = false;
		VIBussiness::isVideTracking=true;
		
		while (!VIBussiness::isTakePictrueStop)
		{
			if (VIBussiness::overlayChangeCount == 1)
			{
				Mat img = VIBussiness::getOverlayImg();
			 if (img.cols > 0 && img.rows > 0)
			 {
				/*imshow("endoscope", img);
				if (waitKey(1) == 27)
					break;*/
				
				 //resize(VIBussiness::overlayImg, VIBussiness::overlayImg, Size(), 0.75, 0.75);
				 vector<uchar> vecImg;                               //Mat 图片数据转换为vector<uchar>  
				 vector<int> vecCompression_params;
				 vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
				 if (takePhotoParms->getCompression() > 0) {
					 vecCompression_params.push_back(takePhotoParms->getCompression());
				 }
				 else {
					 vecCompression_params.push_back(25);
				 }
				 //imwrite("xx.jpg", img, vecCompression_params);
				 imencode(".jpg", img, vecImg, vecCompression_params);
				 //std::string encode =std::string(vecImg.begin(),vecImg.end());
				
				 ZBase64 base64;
				 string imgbase64 = base64.Encode(vecImg.data(), vecImg.size());

				for (int i = 0; i < VIBussiness::cgvector->size(); i++)
				{
					CameraGroup *cg = VIBussiness::cgvector->at(i);
					bool flag = false;
					if (takePhotoParms->getCameraIp() != "") {
						flag = cg->getRgb_camera_ip() == takePhotoParms->getCameraIp() && cg->getRgb_camera_channal() == takePhotoParms->getCameraPass();
					}
					else {
						flag = true;
					}

					if (flag)
					{
						dataParms = new DataParms(cg->getRgb_camera_ip(), to_string(cg->getRgb_camera_channal()), 11, "", "",0, 0, 0, img.cols, img.rows, imgbase64, 0);
						int size = this->SendData(true, dataParms, "");
						if (size == SOCKET_ERROR) {
							break;
						}
						delete dataParms;
					}
				}
			 }
		    }
			Sleep(10);

		}

	}
}

//停止获取图片
void VIBussiness::StopTakePhoto(){

	VIBussiness::isTakePictrueStop=true;
	VIBussiness::isVideTracking=false;
	VIBussiness::TrackingIp = "";
	this->SendCommond(true,4,"","");
}
void VIBussiness::SetSimulated(SimulatedData *simulateData){

	VIBussiness::simulated=simulateData;
}

long VIBussiness::getRealHandleId( string ip,int channelid )
{
	int hanlde=-1;
	map<long,CameraMap *>::iterator it;
	it=VIBussiness::handleCameralist->begin();
	while(it != VIBussiness::handleCameralist->end())
	{
		long realHandle=it->first;
		CameraMap * cameraMap=it->second;
		if(cameraMap->getCameraIp()==ip&&cameraMap->getCameraPass()==channelid){
			hanlde=realHandle;
			break;
		}
		it++;
	}
	return hanlde;
}
Mat VIBussiness::getOverlayImg() {
	std::unique_lock<std::mutex> ulk(mutexlock2);
	VIBussiness::overlayChangeCount = 0;
	return VIBussiness::overlayImg.clone();
}
void VIBussiness::setOverlayImg(Mat img) {
	std::unique_lock<std::mutex> ulk(mutexlock2);
	VIBussiness::overlayChangeCount = 1;
	VIBussiness::overlayImg = img;
}
int VIBussiness::viCall(string rgbId, Mat rgbImg, string irId, Mat irImg, vector<int> flags, map<int, vector<Rect> > roiRects, Mat *overlayImg, map<int, vector<vector<string> > > objs, string errorMsg )
{
	*overlayImg=rgbImg.clone();
	errorMsg="";
	return 0;
}
//换布 
void VIBussiness::DealChangeFabric(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs) {
	int flag;
	for (int n = 0; n < objs.size(); n++) {
		vector<string> vstr = objs.at(n);
		if (vstr.size() == 3) {
			int index = atoi(vstr[0].c_str());
			int x = atoi(vstr[1].c_str());
			int y = atoi(vstr[2].c_str());
			int type = 5;
			if (index == 1) {
				if (type != 0) {
					DataParms *dataParms = new DataParms(ip, channal, type, "","", 0, x, y, 0, 0, "", 0);
					//发送识别数据
					flag = this->SendData(ta_sockets, ta_client_socket, log, true, dataParms, "");
					if (flag == SOCKET_ERROR) {
						break;
					}
					delete dataParms;
				}
			}
		}

	}
}
//处理换液
void VIBussiness::DealChangeWater(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs) {
	int flag;
	for (int n = 0; n < objs.size(); n++) {
		vector<string> vstr = objs.at(n);
		if (vstr.size() == 3) {
			int index = atoi(vstr[0].c_str());
			int x = atoi(vstr[1].c_str());
			int y = atoi(vstr[2].c_str());
			int type = 4;
			if (index == 1) {
				if (type != 0) {
					DataParms *dataParms = new DataParms(ip, channal, type, "","", 0, x, y, 0, 0, "", 0);
					//发送识别数据
					flag = this->SendData(ta_sockets, ta_client_socket, log, true, dataParms, "");
					if (flag == SOCKET_ERROR) {
						break;
					}
					delete dataParms;
				}
			}
		}

	}
}
//处理枪的使用
void VIBussiness::DealGunUse(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, std::string ip, std::string channal, vector<vector<string>> objs) {
	int flag;
	for (int n = 0; n < objs.size(); n++) {
		vector<string> vstr = objs.at(n);
		if (vstr.size() == 6) {
			std::string code = vstr[0].c_str();
			int gunstop = atoi(vstr[1].c_str());
			int x = atoi(vstr[2].c_str());
			int y = atoi(vstr[3].c_str());
			//int w = atoi(vstr[4].c_str());
			//int h = atoi(vstr[5].c_str());
			int type = 3;

			if (type != 0) {
				DataParms *dataParms = new DataParms(ip, channal, type, code,"", gunstop, x, y, 0, 0, "", 0);
				//发送识别数据
				flag = this->SendData(ta_sockets, ta_client_socket, log, true, dataParms, "");
				if (flag == SOCKET_ERROR) {
					break;
				}
				delete dataParms;
			}
		}
	}
}
string   VIBussiness::BindEndocodePerson(string irip,string tankgroupid,string tanktype,int sx, int sy) {
	//第一步在人员识别队列中找到5秒人识别的人员信息
	vector<Person> persons;
	string personCode="";
	map<std::string, Person>::iterator personit;
	personit = VIBussiness::personMap.begin();
	ec::Time ctime;
	while (personit != VIBussiness::personMap.end())
	{
		Person person = personit->second;
		long timespan = ctime.diff(person.getRecentVITime(), ec::Duration::Second);
		if (timespan <= 5)
		{
			persons.push_back(person);
		}
		personit++;
	}
	//匹配到1个人
	if (persons.size() == 1) {

		personCode = persons.at(0).getCode();
		VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.setPersonCode(persons.at(0).getCode());
	}
	else if (persons.size() > 1)
	{
		//如果匹配多个人 就通过距离找最近的那个人
		int mindistance = 0;
		std::string code = "";
		int minx = 0;
		int miny = 0;
		for (int i = 0; i < persons.size(); i++) {
			Person person = persons.at(i);
			int distance = sqrt((person.getX() - sx)*(person.getX() - sx) + (person.getY() - sy)* (person.getY() - sy));
			if (mindistance == 0) {
				mindistance = distance;
				code = person.getCode();
				minx = person.getX();
				miny = person.getY();
			}
			else if (mindistance > distance) {
				mindistance = distance;
				code = person.getCode();
				minx = person.getX();
				miny = person.getY();
			}
		}
		Rect rect=VIBussiness::CheckRects.find(1)->second.find(irip)->second.find(tanktype)->second;
		if (minx > rect.x&&minx<(rect.x + rect.width) && miny>rect.y&&miny < (rect.y + rect.height)) {
			VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.setPersonLock(1);
		}
		personCode = code;
		VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.setPersonCode(code);
	}
	return personCode;
}
//处理内镜和用户
void VIBussiness::DealPersonEndoscope(int sign,int dryischeck,string startTime,string endTime,int sx,int sy, std::string tankgroupid, std::string tanktype, UploadImage *ui, cv::Mat rgbImg, cv::Mat irImg, SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, vector<vector<string>> objs, string ip, string channal, string rgbip, int rgbchannal, int imgwidth, int imgheight) {

	int flag;
	for (int n = 0; n < objs.size(); n++) {
		vector<string> vstr = objs.at(n);
		if (vstr.size() == 3) {

			string code = vstr[0].c_str();
			VIBussiness::totalnum++;
			if (code == "-1" || code == "") {
				VIBussiness::errornum++;
				continue;
			}

			int x = atoi(vstr[1].c_str());
			int y = atoi(vstr[2].c_str());
			if ((sign == 1|| sign==3) && !tankgroupid.empty()) {
				Rect rect = VIBussiness::CheckRects.find(1)->second.find(ip)->second.find(tanktype)->second;
				//判断是否到x，y 是否在rect 在里面；
				if (x < rect.x || x>(rect.x + rect.width) || y<rect.y || y >(rect.y + rect.height)) {
					continue;
				}
			}
			int type = 0;
			string usercodes = ";" + VIBussiness::vsparms->getUserCode() + ";";
			string::size_type isexist = usercodes.find(";"+code+";");
			string personCode = "";
			if (isexist!=string::npos) {
				type = 1;
				//记录人员识别队列信息
				if (VIBussiness::personMap.count(code) == 0) {
					Person person;
					person.setCode(code);
					ec::Time now;
					person.setRecentVITime(now);
					person.setTankgroupid(tankgroupid);
					person.setX(x);
					person.setY(y);
					VIBussiness::personMap.insert(make_pair(code, person));
				}
				else 
				{
					ec::Time now;
					VIBussiness::personMap.find(code)->second.setRecentVITime(now);
					VIBussiness::personMap.find(code)->second.setTankgroupid(tankgroupid);
					VIBussiness::personMap.find(code)->second.setX(x);
					VIBussiness::personMap.find(code)->second.setY(y);
				}
			}
			else {
				if (ui->isUploadimage) {
					if (VIBussiness::cameralist->count(rgbip) > 0) {
						Camera *camera = VIBussiness::cameralist->find(rgbip)->second;
						long userid = camera->lUserID;
						//保存图片
						ui->addImageName(ui, rgbImg, irImg, userid, rgbchannal);
					}
				}
				//通知帧率状态
				VideoFrameRate::Notify(ip);
				if (sign == 1) {

					if (VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.getCodes().size() == 0) {
						ec::Time t;
						printf_s("推断后发送坐标%s\r\n", t.toDate().toString().c_str());
						type = 2;
						ec::Time cutime;
						VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.setSendTime(cutime);
					}
					//修改code
					 VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.setCodes(code, startTime);
					 
					 if (VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.getAutostopcount() == 0)
					 {
						 VIBussiness::SetAutostopTankIDAndIP(tankgroupid, tanktype.substr(0, 15), VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.getCodes());
					 }

					//VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.setStatus(2);
					//内镜code 不为空的时候 去绑定人员关系
					if (!code.empty())
					{
						//判断是否已经锁定用户
						if (VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.getPersonlock() != 1) {
							personCode = this->BindEndocodePerson(ip, tankgroupid, tanktype, sx, sy);
						}
						else
						{
							personCode = VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.getPersonCode();
						}
					}
					//调整帧率
					UpdateFrameRate(ip, tankgroupid, tanktype);
					
					//type = 2;
				}
				else if (sign == 2)
				{
					type = 2;
				}
				//干燥识别内镜
				else if (sign == 3) 
				{
					string defaultcode=VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.getDefalutCode();
					//发现有识别默认的内镜则标记code
					if (defaultcode.compare(code) == 0) 
					{
						VIBussiness::tagStatusMap.find(tankgroupid)->second.find(tanktype)->second.setCodes(code, startTime);
					}
				}
				//如果是纯标签识别
				if (VIBussiness::vsparms->getIsPureIRLableIdentification()) {
					type = 2;
				}

				//如果干燥区域有识别的标签编码则可以直接识别
				if (VIBussiness::vsparms->getIsDryIRLableIdentification()&&!VIBussiness::vsparms->getIsRgbDryCheck()) {

					Rect rect = VIBussiness::CheckRects.find(1)->second.find(ip)->second.find(VIBussiness::DryTankTypeAndIDMap.find(tankgroupid)->second)->second;
					//判断是否到x，y 是否在rect 在里面；
					if (x > rect.x && x<(rect.x + rect.width) && y>rect.y && y <(rect.y + rect.height)) {
						
						if (VIBussiness::DryTankClearCount.count(code) == 0|| VIBussiness::DryTankClearCount.find(code)->second==0) {
						 
							/*map<string, string> steps = this->findPreSetp(VIBussiness::DryTankTypeAndID);
							map<string, string>::iterator stepit;
							stepit = steps.begin();
							while (stepit != steps.end())
							{
								string workstep = stepit->second;
								if (!workstep.empty())
								{
									std::map<string, string> codes;
									codes.insert(make_pair(code, code));

									VIBussiness::SetAutostopTankIDAndIP(tankgroupid, workstep, codes);
								}
								stepit++;
							}*/
							std::map<string, string> codes;
							ec::Time time;
							codes.insert(make_pair(code, time.toDate().toString()));
							VIBussiness::SetAutostopTankIDAndIP(tankgroupid, VIBussiness::DryTankTypeAndIDMap.find(tankgroupid)->second.substr(0,15), codes);

							
						}
						type = 2;
					}
				}
				//处理自动消毒机区域识别区域

			}
			
			if (type != 0) {

				DataParms *dataParms = new DataParms(ip, channal, type, code,personCode,dryischeck,sign, startTime,endTime,tanktype,0, x, y, imgwidth, imgheight, "", 0);
				//发送识别数据
				flag = this->SendData(ta_sockets, ta_client_socket,log, true, dataParms, "");
				if (flag == SOCKET_ERROR) {
					break;
				}
				delete dataParms;
			}
		
		}
	}
	
}
