#include "VIBase.h"



VIBase::VIBase(void)
{

}

VIBase::~VIBase(void)
{

}
std::string VIBase::serverip;
//IsExcuteSuccess ����ִ���� ����true �쳣����false dataParms��ʶ�����ݲ������� errorMsg���쳣����
int VIBase::SendData(bool IsExcuteSuccess,DataParms * dataParms,std::string errorMsg){

	std::string commandType; 
	//1->5����Ա��Ϣ 2->6���ھ���Ϣ 3->7��ǹ��Ϣ 4->8����Һ��Ϣ 5->9��������Ϣ 10->10��ͼƬ��Ϣ
	switch (dataParms->getType())
	{
	case 1:
		commandType="5";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("��Ա��ʶ�룺"+dataParms->getIdCode()+"��Ա��Ϣʶ���쳣��"+errorMsg);
		}
		break;
	case 2:
		commandType="6";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("�ھ���ʶ�룺"+dataParms->getIdCode()+"�ھ���Ϣʶ���쳣��"+errorMsg);
		}
		break;
	case 3:
		commandType="7";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("ǹ��Ϣʶ���쳣��"+errorMsg);
		}
		break;
	case 4:
		commandType="8";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("��Һ��Ϣʶ���쳣��"+errorMsg);
		}
		break;
	case 5:
		commandType="9";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("������Ϣʶ���쳣��"+errorMsg);
		}
		break;
	case 10:
		commandType="10";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("ͼƬ��Ϣʶ���쳣��"+errorMsg);
		}
		break;
	case 11:
		commandType="11";
		if(!IsExcuteSuccess){
			this->log->WriteErrorLog("ͼƬ��Ϣʶ���쳣��"+errorMsg);
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
	//1->5����Ա��Ϣ 2->6���ھ���Ϣ 3->7��ǹ��Ϣ 4->8����Һ��Ϣ 5->9��������Ϣ 10->10��ͼƬ��Ϣ
	switch (dataParms->getType())
	{
	case 1:
		commandType = "5";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("��Ա��ʶ�룺" + dataParms->getIdCode() + "��Ա��Ϣʶ���쳣��" + errorMsg);
		}
		break;
	case 2:
		commandType = "6";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("�ھ���ʶ�룺" + dataParms->getIdCode() + "�ھ���Ϣʶ���쳣��" + errorMsg);
		}
		break;
	case 3:
		commandType = "7";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("ǹ��Ϣʶ���쳣��" + errorMsg);
		}
		break;
	case 4:
		commandType = "8";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("��Һ��Ϣʶ���쳣��" + errorMsg);
		}
		break;
	case 5:
		commandType = "9";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("������Ϣʶ���쳣��" + errorMsg);
		}
		break;
	case 10:
		commandType = "10";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("ͼƬ��Ϣʶ���쳣��" + errorMsg);
		}
		break;
	case 11:
		commandType = "11";
		if (!IsExcuteSuccess) {
			log->WriteErrorLog("ͼƬ��Ϣʶ���쳣��" + errorMsg);
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
			log->WriteTraceLog("��ʼ���ѳɹ�.");
		}
		else {
			log->WriteTraceLog("��ʼ���쳣��" + errorMsg);
		}
		break;
	case 1:
		if (IsExcuteSuccess) {
			log->WriteTraceLog("��ʼʶ�������ѳɹ�.");
		}
		else {
			log->WriteErrorLog("��ʼʶ�������쳣��" + errorMsg);
		}
		break;
	case 2:
		if (IsExcuteSuccess) {
			log->WriteTraceLog("����ʶ�������ѳɹ�.");
		}
		else {
			log->WriteErrorLog("����ʶ�������쳣��" + errorMsg);
		}
		break;
	case 3:
		if (IsExcuteSuccess) {
			log->WriteTraceLog("��ʼ��ȡͼƬ�����ѳɹ�.");
		}
		else {
			log->WriteErrorLog("��ʼ��ȡͼƬ�����쳣��" + errorMsg);
		}
		break;
	case 4:
		if (IsExcuteSuccess) {
			log->WriteTraceLog("������ȡͼƬ�����ѳɹ�.");
		}
		else {
			log->WriteErrorLog("������ȡͼƬ�����쳣��" + errorMsg);
		}
		break;
	default:
		break;
	}
	std::string ip = VIBase::serverip;
	data = "{\"IsExcuteSuccess\":\"" + std::string(IsExcuteSuccess ? "1" : "0") + "\",\"serverIP\":\"" + ip + "\",\"tanktype\":\"" + tanktype + "\",\"tankgroupid\":\"" + tankgroupid + "\",\"commandType\":\"" + std::to_string(commandType) + "\",\"errorMsg\":\"" + errorMsg + "\",\"data\":{}}\r\n";
	ta_sockets->SendRequest(ta_client_socket, data.c_str(), data.size());
	
}

//�ظ����� IsExcuteSuccess ����ִ���� ����true �쳣����false  commandType: 0:��ʼ�� 1:��ʼʶ������ 2������ʶ������  3����ʼ��ȡͼƬ 4��ֹͣ��ȡͼƬ  300: irδʶ��Ԥ��  errorMsg���쳣���� 
void VIBase::SendCommond(bool IsExcuteSuccess, int commandType, std::string tankgroupid, std::string errorMsg) {
std:string data;
	switch (commandType)
	{
	case 0:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("��ʼ���ѳɹ�.");
		}
		else {
			this->log->WriteTraceLog("��ʼ���쳣��" + errorMsg);
		}
		break;
	case 1:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("��ʼʶ�������ѳɹ�.");
		}
		else {
			this->log->WriteErrorLog("��ʼʶ�������쳣��" + errorMsg);
		}
		break;
	case 2:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("����ʶ�������ѳɹ�.");
		}
		else {
			this->log->WriteErrorLog("����ʶ�������쳣��" + errorMsg);
		}
		break;
	case 3:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("��ʼ��ȡͼƬ�����ѳɹ�.");
		}
		else {
			this->log->WriteErrorLog("��ʼ��ȡͼƬ�����쳣��" + errorMsg);
		}
		break;
	case 4:
		if (IsExcuteSuccess) {
			this->log->WriteTraceLog("������ȡͼƬ�����ѳɹ�.");
		}
		else {
			this->log->WriteErrorLog("������ȡͼƬ�����쳣��" + errorMsg);
		}
		break;
	default:
		break;
	}
	std::string ip = VIBase::serverip;
	data="{\"IsExcuteSuccess\":\""+std::string(IsExcuteSuccess?"1":"0")+"\",\"serverIP\":\""+ ip +"\",\"tankgroupid\":\"" + tankgroupid + "\",\"commandType\":\""+ std::to_string(commandType) +"\",\"errorMsg\":\""+errorMsg+"\",\"data\":{}}\r\n";
	this->currentThread->ta_sockets->SendRequest(currentThread->ta_client_socket, data.c_str(),data.size());
}


