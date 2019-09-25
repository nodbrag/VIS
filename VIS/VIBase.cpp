#include "VIBase.h"



VIBase::VIBase(void)
{

}

VIBase::~VIBase(void)
{

}
std::string VIBase::serverip;
//IsExcuteSuccess 正常执行完 返回true 异常返回false dataParms：识别数据参数对象 errorMsg：异常错误
int VIBase::SendData(bool IsExcuteSuccess,DataParms * dataParms,std::string errorMsg){

	std::string commandType; 
	//1->5：人员信息 2->6：内镜信息 3->7：枪信息 4->8：换液信息 5->9：换布信息 10->10：图片信息
	switch (dataParms->getType())
	{
	case 1:
		commandType="5";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("人员标识码："+dataParms->getIdCode()+"人员信息识别异常："+errorMsg);
		}
		break;
	case 2:
		commandType="6";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("内镜标识码："+dataParms->getIdCode()+"内镜信息识别异常："+errorMsg);
		}
		break;
	case 3:
		commandType="7";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("枪信息识别异常："+errorMsg);
		}
		break;
	case 4:
		commandType="8";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("换液信息识别异常："+errorMsg);
		}
		break;
	case 5:
		commandType="9";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("换布信息识别异常："+errorMsg);
		}
		break;
	case 10:
		commandType="10";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("图片信息识别异常："+errorMsg);
		}
		break;
	case 11:
		commandType="11";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("图片信息识别异常："+errorMsg);
		}
		break;
	default:
		break;
	}
 
  std::string ip = VIBase::serverip;
  std:string data="{\"IsExcuteSuccess\":\""+std::string(IsExcuteSuccess?"1":"0")+"\",\"serverIP\":\"" + ip + "\",\"commandType\":\""+ commandType +"\",\"errorMsg\":\""+errorMsg+"\",\"data\":{\"cameraIp\":\""+dataParms->getCameraIp()+"\",\"cameraPass\":\""+dataParms->getCameraPass()+"\",\"type\":"+std::to_string(dataParms->getType())+",\"idCode\":\""+dataParms->getIdCode()+"\",\"gunStopID\":"+std::to_string(dataParms->getGunStopID())+",\"X\":"+std::to_string(dataParms->getX())+",\"Y\":"+std::to_string(dataParms->getY())+",\"height\":"+std::to_string(dataParms->getHeight())+",\"width\":"+std::to_string(dataParms->getWidth())+",\"imagedatas\":\""+dataParms->getImageDatas()+"\",\"imageFormart\":"+std::to_string(dataParms->getImageFormart())+"}}\r\n";
  
  int size = this->currentThread->ta_sockets->SendRequest(currentThread->ta_client_socket, data.c_str(), data.size());
  if (SOCKET_ERROR == size) {

	  closesocket(currentThread->ta_client_socket);
  }
  //ec::Time now;
  //std::cout << now.toDate().toString() << endl;
  /*int totalLength = data.length();
  int len = 50000;
  for (int i = 0; i < totalLength; i=i+ len) {	  
	  if (i + len >= totalLength)
	  {
		  Sleep(1000);
		  std::string data1 = data.substr(i, totalLength - i) + "\r\n";
		  cout << totalLength << endl;
		  this->currentThread->ta_sockets->SendRequest(currentThread->ta_client_socket, data1.c_str(), data1.size());
		  break;
	  }
	  else 
	  {
		  std::string data1 = data.substr(i, len) + "|\r\n";
		  this->currentThread->ta_sockets->SendRequest(currentThread->ta_client_socket, data1.c_str(), data1.size());
	  }
  }*/
 
  return size;
}

int VIBase::SendData(SocketsInterface *ta_sockets,SOCKET ta_client_socket, Log *log,bool IsExcuteSuccess, DataParms * dataParms, std::string errorMsg) {

	std::string commandType;
	//1->5：人员信息 2->6：内镜信息 3->7：枪信息 4->8：换液信息 5->9：换布信息 10->10：图片信息
	switch (dataParms->getType())
	{
	case 1:
		commandType = "5";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("人员标识码：" + dataParms->getIdCode() + "人员信息识别异常：" + errorMsg);
		}
		break;
	case 2:
		commandType = "6";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("内镜标识码：" + dataParms->getIdCode() + "内镜信息识别异常：" + errorMsg);
		}
		break;
	case 3:
		commandType = "7";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("枪信息识别异常：" + errorMsg);
		}
		break;
	case 4:
		commandType = "8";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("换液信息识别异常：" + errorMsg);
		}
		break;
	case 5:
		commandType = "9";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("换布信息识别异常：" + errorMsg);
		}
		break;
	case 10:
		commandType = "10";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("图片信息识别异常：" + errorMsg);
		}
		break;
	case 11:
		commandType = "11";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("图片信息识别异常：" + errorMsg);
		}
		break;
	default:
		break;
	}
	if (dataParms->getDryischeck()) {
		int a;
	}
	std::string ip = VIBase::serverip;
    std:string data = "{\"IsExcuteSuccess\":\"" + std::string(IsExcuteSuccess ? "1" : "0") + "\",\"serverIP\":\"" + ip + "\",\"commandType\":\"" + commandType + "\",\"errorMsg\":\"" + errorMsg + "\",\"data\":{\"cameraIp\":\"" + dataParms->getCameraIp() + "\",\"cameraPass\":\"" + dataParms->getCameraPass() + "\",\"dryischeck\":" + std::to_string(dataParms->getDryischeck()) + ",\"type\":" + std::to_string(dataParms->getType()) + ",\"idCode\":\"" + dataParms->getIdCode() + "\",\"personCode\":\"" + dataParms->getPersonCode() + "\",\"cleanStatus\":"+to_string(dataParms->getCleanStatus())+",\"cleanStartTime\":\""+dataParms->getCleanStartTime()+"\",\"cleanEndTime\":\""+dataParms->getCleanEndTime()+"\",\"tankType\":\"" + dataParms->getTankType() + "\",\"gunStopID\":" + std::to_string(dataParms->getGunStopID()) + ",\"X\":" + std::to_string(dataParms->getX()) + ",\"Y\":" + std::to_string(dataParms->getY()) + ",\"height\":" + std::to_string(dataParms->getHeight()) + ",\"width\":" + std::to_string(dataParms->getWidth()) + ",\"imagedatas\":\"" + dataParms->getImageDatas() + "\",\"imageFormart\":" + std::to_string(dataParms->getImageFormart()) + "}}\r\n";
	
	int size = ta_sockets->SendRequest(ta_client_socket, data.c_str(), data.size());
	if (SOCKET_ERROR == size) {
		
			closesocket(ta_client_socket);
	}
	//ec::Time now;
	//std::cout << now.toDate().toString() << endl;
	return size;
}
void VIBase::SendCommond(SocketsInterface *ta_sockets, SOCKET ta_client_socket, Log *log, bool IsExcuteSuccess, int commandType, std::string tankgroupid, std::string tanktype, std::string errorMsg) {
   std:string data;
	switch (commandType)
	{
	case 0:
		if (IsExcuteSuccess) {
			log->WriteTraceLog("初始化已成功.");
		}
		else {
			log->WriteTraceLog("初始化异常：" + errorMsg);
		}
		break;
	case 1:
		if (IsExcuteSuccess) {
			log->WriteTraceLog("开始识别任务已成功.");
		}
		else {
			log->WriteErrorLog("开始识别任务异常：" + errorMsg);
		}
		break;
	case 2:
		if (IsExcuteSuccess) {
			log->WriteTraceLog("结束识别任务已成功.");
		}
		else {
			log->WriteErrorLog("结束识别任务异常：" + errorMsg);
		}
		break;
	case 3:
		if (IsExcuteSuccess) {
			log->WriteTraceLog("开始获取图片任务已成功.");
		}
		else {
			log->WriteErrorLog("开始获取图片任务异常：" + errorMsg);
		}
		break;
	case 4:
		if (IsExcuteSuccess) {
			log->WriteTraceLog("结束获取图片任务已成功.");
		}
		else {
			log->WriteErrorLog("结束获取图片任务异常：" + errorMsg);
		}
		break;
	default:
		break;
	}
	std::string ip = VIBase::serverip;
	data = "{\"IsExcuteSuccess\":\"" + std::string(IsExcuteSuccess ? "1" : "0") + "\",\"serverIP\":\"" + ip + "\",\"tanktype\":\"" + tanktype + "\",\"tankgroupid\":\"" + tankgroupid + "\",\"commandType\":\"" + std::to_string(commandType) + "\",\"errorMsg\":\"" + errorMsg + "\",\"data\":{}}\r\n";
	ta_sockets->SendRequest(ta_client_socket, data.c_str(), data.size());
	
}

//回复命令 IsExcuteSuccess 正常执行完 返回true 异常返回false  commandType: 0:初始化 1:开始识别任务 2：结束识别任务  3：开始获取图片 4：停止获取图片  300: ir未识别预警  errorMsg：异常错误 
void VIBase::SendCommond(bool IsExcuteSuccess, int commandType, std::string tankgroupid, std::string errorMsg) {
std:string data;
	switch (commandType)
	{
	case 0:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("初始化已成功.");
		}
		else {
			this->log->WriteTraceLog("初始化异常：" + errorMsg);
		}
		break;
	case 1:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("开始识别任务已成功.");
		}
		else {
			this->log->WriteErrorLog("开始识别任务异常：" + errorMsg);
		}
		break;
	case 2:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("结束识别任务已成功.");
		}
		else {
			this->log->WriteErrorLog("结束识别任务异常：" + errorMsg);
		}
		break;
	case 3:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("开始获取图片任务已成功.");
		}
		else {
			this->log->WriteErrorLog("开始获取图片任务异常：" + errorMsg);
		}
		break;
	case 4:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("结束获取图片任务已成功.");
		}
		else {
			this->log->WriteErrorLog("结束获取图片任务异常：" + errorMsg);
		}
		break;
	default:
		break;
	}
	std::string ip = VIBase::serverip;
	data="{\"IsExcuteSuccess\":\""+std::string(IsExcuteSuccess?"1":"0")+"\",\"serverIP\":\""+ ip +"\",\"tankgroupid\":\"" + tankgroupid + "\",\"commandType\":\""+ std::to_string(commandType) +"\",\"errorMsg\":\""+errorMsg+"\",\"data\":{}}\r\n";
	this->currentThread->ta_sockets->SendRequest(currentThread->ta_client_socket, data.c_str(),data.size());
}


