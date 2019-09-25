#include <vector>
#include <iostream>
#include "EchoService.h"
#include "Command.h"
#include "JSON.h"
#include "Common.h";
#include "TakePhotoParms.h";
#include "CameraMap.h";
#include "VINotify.h";
#include "SimulatedData.h";
#include "VISetting.h";
#include "XmlConfig.h"
#include "ColorArgument.h"


EchoService::EchoService(void)
{
	echoBufferSize=EchoBufferSize;
}

EchoService::~EchoService(void)
{
}
void UTF8ToGBK(char *&szOut)
{
	unsigned short *wszGBK;
	char *szGBK;
	//长度
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, NULL, 0);
	wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, (LPWSTR)wszGBK, len);

	//长度
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);

	//szOut = szGBK; //这样得到的szOut不正确，因为此句意义是将szGBK的首地址赋给szOut，当delete []szGBK执行后szGBK的内

	//存空间将被释放，此时将得不到szOut的内容

	memset(szOut, '/0', strlen(szGBK) + 1); //改将szGBK的内容赋给szOut ，这样即使szGBK被释放也能得到正确的值
	memcpy(szOut, szGBK, strlen(szGBK));


	delete[]szGBK;
	delete[]wszGBK;
}
void GBKToUTF8(char* &szOut)
{
	char* strGBK = szOut;

	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, NULL, 0);
	unsigned short * wszUtf8 = new unsigned short[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, (LPWSTR)wszUtf8, len);

	len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL, NULL);

	//szOut = szUtf8;
	memset(szOut, '/0', strlen(szUtf8) + 1);
	memcpy(szOut, szUtf8, strlen(szUtf8));

	delete[] szUtf8;
	delete[] wszUtf8;
}
void EchoService::HandleRequest(THREAD_ARGUMENTS *arguments){

	char buffer[EchoBufferSize];
	int size;
	std::string receiveData;
	
	while(true){

		if (arguments->ta_client_socket) {
			int a = 0;
		}
		if ((size = arguments->ta_sockets->ReceiveRequest(arguments->ta_client_socket, buffer, EchoBufferSize)) < 0) {
			arguments->ta_server_log->WriteErrorLog("socket close!");
			arguments->ta_sockets->CloseSocket(arguments->ta_client_socket);
			return;
		}
		if (arguments->ta_server_log_trace_mode) {
			std::string trace_message = "echo service-> received '" + std::string(buffer, size) + "' from client with size " + std::to_string(size);
			printf_s("%s\n\r", trace_message.c_str());
			arguments->ta_server_log->WriteTraceLog(trace_message);
		}
		
		std::string singledata=std::string(buffer,size);
	     /**测试
		Sleep(1000);
		std::string data = "1\r\n";
		arguments->ta_sockets->SendRequest(arguments->ta_client_socket, data.c_str(), data.size());
		*/

		if (singledata.empty()) {
			arguments->ta_sockets->CloseSocket(arguments->ta_client_socket);
			return;
		}
		if (singledata.find_last_of("]}") != singledata.size() - 1){
			receiveData += singledata;
			continue;
		}
		else {
			receiveData += singledata;
		}

		JSONValue *jsonResult = JSON::Parse(receiveData.c_str());
		if (jsonResult == NULL)
		{
			std::string error_message = "Error to JsonParse :'" + receiveData;
			arguments->ta_server_log->WriteErrorLog(error_message);
			printf_s("%s\n\r", error_message.c_str());
		}
		else
		{
			receiveData = "";
			JSONObject root;
			if (jsonResult->IsObject() == false)
			{
				std::string error_message = "The json root element is not an object ->json:" + receiveData;
				arguments->ta_server_log->WriteErrorLog(error_message);
				printf_s("%s\n\r", error_message.c_str());
			}
			else
			{
				root = jsonResult->AsObject();

				if (root.find(L"commandType") != root.end() && root[L"commandType"]->IsString())
				{
					std::string commandType= Common::UnicodeToAnsi(root[L"commandType"]->AsString().c_str());
					struct ThreadArguments *thread_arguments = (struct ThreadArguments *)malloc(sizeof(struct ThreadArguments));
					if (!thread_arguments) {
						throw (std::runtime_error(std::string("insufficient memory for allocating thread argument structure")));
					}
					thread_arguments->ta_client_socket=arguments->ta_client_socket;
					thread_arguments->ta_server_log=arguments->ta_server_log;
					thread_arguments->ta_server_log_trace_mode=arguments->ta_server_log_trace_mode;
					thread_arguments->ta_sockets=arguments->ta_sockets;

					if(commandType.compare(Command::init)==0){

						if (root.find(L"data") != root.end() && root[L"data"]->IsArray())
						{
							JSONArray dataarray=root[L"data"]->AsArray();
							map<string, std::vector<CameraMap*>> * camerasM = new map<string, std::vector<CameraMap*>>();
							for (unsigned int i = 0; i < dataarray.size(); i++) {
								JSONObject data = dataarray[i]->AsObject();
								
								if (data.find(L"tank_group_id") != data.end() && data[L"tank_group_id"]->IsString())
								{
								   string tank_group_id=Common::UnicodeToAnsi(data[L"tank_group_id"]->AsString().c_str());
								   if (!tank_group_id.empty() && camerasM->count(tank_group_id) == 0) {
									   std::vector<CameraMap*> cmvector;
									   camerasM->insert(make_pair(tank_group_id,cmvector));
								   }
								}
							}
							for (unsigned int i = 0; i < dataarray.size(); i++){

								JSONObject data=dataarray[i]->AsObject();
								CameraMap * cameraMap=new CameraMap();
								if (data.find(L"cameraIp") != data.end() && data[L"cameraIp"]->IsString())
								{
									cameraMap->setCameraIp(Common::UnicodeToAnsi(data[L"cameraIp"]->AsString().c_str()));
								}
								if (data.find(L"cameraType") != data.end() && data[L"cameraType"]->IsString())
								{
									cameraMap->setCameraType(Common::UnicodeToAnsi(data[L"cameraType"]->AsString().c_str()));
								}
								if (data.find(L"cameraPass") != data.end() && data[L"cameraPass"]->IsNumber())
								{
									cameraMap->setCameraPass(data[L"cameraPass"]->AsNumber());
								}
								if (data.find(L"tank_group_id") != data.end() && data[L"tank_group_id"]->IsString())
								{
									cameraMap->setTank_group_id(Common::UnicodeToAnsi(data[L"tank_group_id"]->AsString().c_str()));
								}
								if (!cameraMap->getTank_group_id().empty()) {
									camerasM->find(cameraMap->getTank_group_id())->second.push_back(cameraMap);
								}
							}
							if(camerasM->size()>0){
								thread_arguments->camerasMap= camerasM;
							}

						}else{
							std::string error_message = "The json root element is can't find 'data' JSONArray ->json:" + receiveData;
							arguments->ta_server_log->WriteErrorLog(error_message);
							printf_s("%s\n\r", error_message.c_str());
						}
						if(root.find(L"viconfig") != root.end() && root[L"viconfig"]->IsArray()){
							VISetting *vs=new VISetting();
							JSONArray dataarray=root[L"viconfig"]->AsArray();
							JSONObject data=dataarray[0]->AsObject();
							if (data.find(L"isPersonIdentified") != data.end() && data[L"isPersonIdentified"]->IsBool())
							{
								vs->setIsPersonIdentified(data[L"isPersonIdentified"]->AsBool());
							}
							if (data.find(L"isEndoscopeIdentified") != data.end() && data[L"isEndoscopeIdentified"]->IsBool())
							{
								vs->setIsEndoscopeIdentified(data[L"isEndoscopeIdentified"]->AsBool());
							}
							if (data.find(L"isGunIdentified") != data.end() && data[L"isGunIdentified"]->IsBool())
							{
								vs->setIsGunIdentified(data[L"isGunIdentified"]->AsBool());
							}
							if (data.find(L"isTransferEnzymeLiquidIdentified") != data.end() && data[L"isTransferEnzymeLiquidIdentified"]->IsBool())
							{
								vs->setIsTransferEnzymeLiquidIdentified(data[L"isTransferEnzymeLiquidIdentified"]->AsBool());
							}
							if (data.find(L"isTransferInfectionLiquidIdentified") != data.end() && data[L"isTransferInfectionLiquidIdentified"]->IsBool())
							{
								vs->setIsTransferInfectionLiquidIdentified(data[L"isTransferInfectionLiquidIdentified"]->AsBool());
							}
							if (data.find(L"isTransferClothIdentified") != data.end() && data[L"isTransferClothIdentified"]->IsBool())
							{
								vs->setIsTransferClothIdentified(data[L"isTransferClothIdentified"]->AsBool());
							}
							thread_arguments->visetting=vs;

						}else{
							std::string error_message = "The json root element is can't find 'viconfig' JSONArray ->json:" + receiveData;
							arguments->ta_server_log->WriteErrorLog(error_message);
							printf_s("%s\n\r", error_message.c_str());
						}
						
						if (root.find(L"tankgroupids") != root.end() && root[L"tankgroupids"]->IsArray()) {
								JSONArray dataarray = root[L"tankgroupids"]->AsArray();
								vector<string> *gids = new vector<string>();
								for (int i = 0; i < dataarray.size(); i++) {
									JSONObject data = dataarray[i]->AsObject();
									if (data.find(L"id") != data.end() && data[L"id"]->IsString())
									{
										gids->push_back(Common::UnicodeToAnsi(data[L"id"]->AsString().c_str()));
									}
								}
								thread_arguments->groupids = gids;
						}
						else 
						{
							std::string error_message = "The json root element is can't find 'tankgroupids' JSONArray ->json:" + receiveData;
							arguments->ta_server_log->WriteErrorLog(error_message);
							printf_s("%s\n\r", error_message.c_str());
						}
						
						
						VSParms *vsp = new  VSParms();
						if (root.find(L"preTime") != root.end() && root[L"preTime"]->IsNumber())
						{
							vsp->setPreTime(root[L"preTime"]->AsNumber());
						}
						XmlConfig xc;
						TiXmlDocument doc = xc.initXml();
						vsp->setMinlengthPx(atoi(xc.GetVSParmsNodeValue("MinlengthPx").c_str()));
						vsp->setMinCommonNum(atoi(xc.GetVSParmsNodeValue("MinCommonNum").c_str()));
						vsp->setDeviceCapturePicture(atoi(xc.GetVSParmsNodeValue("DeviceCapturePicture").c_str()));
						vsp->setIsRgbCheck(atoi(xc.GetVSParmsNodeValue("IsRgbCheck").c_str()));
						vsp->setVideoDecoder(atoi(xc.GetVSParmsNodeValue("VideoDecoder").c_str()));
						vsp->setDecodeInteval(atof(xc.GetVSParmsNodeValue("DecodeInteval").c_str()));
						vsp->setDetectMinArea(atoi(xc.GetVSParmsNodeValue("DetectMinArea").c_str()));
						vsp->setDetectMaxArea(atoi(xc.GetVSParmsNodeValue("DetectMaxArea").c_str()));
						vsp->setIsDrawCode(atoi(xc.GetVSParmsNodeValue("IsDrawCode").c_str())==1);
						vsp->setIsDrawTail(atoi(xc.GetVSParmsNodeValue("IsDrawTail").c_str()) == 1);
						vsp->setDecodeThresh(atof(xc.GetVSParmsNodeValue("DecodeThresh").c_str())); 
						vsp->setLableCols(atoi(xc.GetVSParmsNodeValue("lableCols").c_str()));
						vsp->setLableRows(atoi(xc.GetVSParmsNodeValue("lableRows").c_str()));
						vsp->setIsOpenillation(atoi(xc.GetVSParmsNodeValue("IsOpenillation").c_str()));
						vsp->setValidateNum(atoi(xc.GetVSParmsNodeValue("ValidateNum").c_str()));
						vsp->setTipCount(atoi(xc.GetVSParmsNodeValue("TipCount").c_str()));
						vsp->setIsTest(atoi(xc.GetVSParmsNodeValue("Test").c_str()));
						vsp->seteShiftX(atoi(xc.GetVSParmsNodeValue("EShiftX").c_str()));
						vsp->setpShiftX(atoi(xc.GetVSParmsNodeValue("PShiftX").c_str()));
						vsp->setBloodMax(atoi(xc.GetVSParmsNodeValue("bloodMax").c_str()));
						vsp->setCellsize(atoi(xc.GetVSParmsNodeValue("cellSize").c_str()));
						vsp->setLablemargin(atoi(xc.GetVSParmsNodeValue("lableMargin").c_str()));
						vsp->setInnerThresh(atoi(xc.GetVSParmsNodeValue("innerThresh").c_str()));
						vsp->setScale(atof(xc.GetVSParmsNodeValue("scale").c_str()));
						vsp->setTankwscale(atof(xc.GetVSParmsNodeValue("TankWidthScale").c_str()));
						vsp->setTotalFrameNum(atoi(xc.GetVSParmsNodeValue("TotalFrameNum").c_str()));
						vsp->setCleanInfectionMachineFrameNum(atoi(xc.GetVSParmsNodeValue("CleanInfectionMachineFrameNum").c_str()));
						vsp->setMinFrameNum(atoi(xc.GetVSParmsNodeValue("MinFrameNum").c_str()));
						vsp->setWorkSpaceTime(atoi(xc.GetVSParmsNodeValue("WorkSpaceTime").c_str()));
						vsp->setIsDynamicSetFrameRate(atoi(xc.GetVSParmsNodeValue("IsDynamicSetFrameRate").c_str()) == 0 ? false : true);
						vsp->setRgbFrameRate(atoi(xc.GetVSParmsNodeValue("RgbFrameRate").c_str()));
						vsp->setIRMaxFrameRate(atoi(xc.GetVSParmsNodeValue("IRMaxFrameRate").c_str()));
						vsp->setIRMinFrameRate(atoi(xc.GetVSParmsNodeValue("IRMinFrameRate").c_str()));
						vsp->setOpenillationTimeBySecond(atoi(xc.GetVSParmsNodeValue("OpenillationTimeBySecond").c_str()));
						vsp->setRgbcheckFrameNum(atoi(xc.GetVSParmsNodeValue("RgbcheckFrameNum").c_str()));
						vsp->setIsDemo(atoi(xc.GetVSParmsNodeValue("IsDemo").c_str()));
						vsp->setUserTestCodeForDemo(atoi(xc.GetVSParmsNodeValue("UserTestCodeForDemo").c_str()));
						vsp->setEndoscopeTestNameForDemo(Common::UTF8_To_GBK(xc.GetVSParmsNodeValue("EndoscopeTestNameForDemo")));
						vsp->setUserTestNameForDemo(Common::UTF8_To_GBK(xc.GetVSParmsNodeValue("UserTestNameForDemo")));
						vsp->setDefaultEndoscopeTestNameForDemo(Common::UTF8_To_GBK(xc.GetVSParmsNodeValue("DefaultEndoscopeTestNameForDemo")));
						vsp->setIsCupUseOptimized(atoi(xc.GetVSParmsNodeValue("IsCupUseOptimized").c_str()) == 0 ? false : true);
						vsp->setIsPureIRLableIdentification(atoi(xc.GetVSParmsNodeValue("IsPureIRLableIdentification").c_str()) == 0 ? false : true);
						vsp->setIsRgbDryCheck(atoi(xc.GetVSParmsNodeValue("IsRgbDryCheck").c_str()) == 0 ? false : true);
						vsp->setWeights(xc.GetVSParmsNodeValue("Weights"));
						vsp->setCFG(xc.GetVSParmsNodeValue("CFG"));
						vsp->setLNames(xc.GetVSParmsNodeValue("LNames"));
						vsp->setIsDryIRLableIdentification(atoi(xc.GetVSParmsNodeValue("IsDryIRLableIdentification").c_str()));
						vsp->setIsTrackUser(atoi(xc.GetVSParmsNodeValue("IsTrackUser").c_str())); 

						doc.Clear();
						
						if (root.find(L"VSParms") != root.end() && root[L"VSParms"]->IsArray()) {
							JSONArray dataarray = root[L"VSParms"]->AsArray();
							
							JSONObject data = dataarray[0]->AsObject();

							
							if (data.find(L"UserCode") != data.end() && data[L"UserCode"]->IsString())
							{
								vsp->setUserCode(Common::UnicodeToAnsi(data[L"UserCode"]->AsString().c_str()));
							}
							if (data.find(L"Endoscope") != data.end() && data[L"Endoscope"]->IsString())
							{
								vsp->setEndoscope(Common::UnicodeToAnsi(data[L"Endoscope"]->AsString().c_str()));
							}
							

							thread_arguments->vsparms = vsp;

						}
						else {
							std::string error_message = "The json root element is can't find 'VSParms' JSONArray ->json:" + receiveData;
							arguments->ta_server_log->WriteErrorLog(error_message);
							printf_s("%s\n\r", error_message.c_str());
						}
						std::map<string, vector<std::string>> *flowmap=new std::map<string, vector<std::string>>();
						if (root.find(L"flowsets") != root.end() && root[L"flowsets"]->IsArray()) {
							JSONArray dataarray = root[L"flowsets"]->AsArray();
							for (int i = 0; i < dataarray.size(); i++)
							{
								JSONObject data = dataarray[i]->AsObject();

								vector<std::string> flowtypevector;
								std::string id = "";
								if (data.find(L"id") != data.end() && data[L"id"]->IsString())
								{
									id = Common::UnicodeToAnsi(data[L"id"]->AsString().c_str());
									if (flowmap->count(id) == 0) {
									
										flowmap->insert(make_pair(id, flowtypevector));
									}
								}
								
								if (data.find(L"flow") != data.end() && data[L"flow"]->IsArray())
								{
									JSONArray flowtypearray = data[L"flow"]->AsArray();
									
									for (int n = 0; n < flowtypearray.size(); n++) {
										JSONObject ftype = flowtypearray[n]->AsObject();
										if (ftype.find(L"flowtype") != ftype.end() && ftype[L"flowtype"]->IsString())
										{
											flowmap->find(id)->second.push_back(Common::UnicodeToAnsi(ftype[L"flowtype"]->AsString().c_str()));
										}
									}
								}
							}
							thread_arguments->flowtypemap = flowmap;
						}
						else {
							std::string error_message = "The json root element is can't find 'flowsets' JSONArray ->json:" + receiveData;
							arguments->ta_server_log->WriteErrorLog(error_message);
							printf_s("%s\n\r", error_message.c_str());
						}

						std::map<int, std::vector<int>> colorval; //颜色参数
						if (root.find(L"colorarguments") != root.end() && root[L"colorarguments"]->IsArray()) {
							JSONArray dataarray = root[L"colorarguments"]->AsArray();
							
							try
							{
								for (int i = 0; i < dataarray.size(); i++) 
								{
									ColorArgument colorArgument;
									JSONObject data = dataarray[i]->AsObject();
									if (data.find(L"type_id") != data.end() && data[L"type_id"]->IsNumber())
									{
										colorArgument.setTypeid(data[L"type_id"]->AsNumber());
									}
									if (data.find(L"hue_normal") != data.end() && data[L"hue_normal"]->IsNumber())
									{
										colorArgument.setHueNormal(data[L"hue_normal"]->AsNumber());
									}
									else 
									{
										colorArgument.setHueNormal(0);
									}
									if (data.find(L"hue_up_val") != data.end() && data[L"hue_up_val"]->IsNumber())
									{
										colorArgument.setHueUpVal(data[L"hue_up_val"]->AsNumber());
									}
									else
									{
										colorArgument.setHueUpVal(0);
									}
									if (data.find(L"hue_down_val") != data.end() && data[L"hue_down_val"]->IsNumber())
									{
										colorArgument.setHueDownVal(data[L"hue_down_val"]->AsNumber());
									}
									else
									{
										colorArgument.setHueDownVal(0);
									}
									if (data.find(L"saturation_normal") != data.end() && data[L"saturation_normal"]->IsNumber())
									{
										colorArgument.setSaturationNormal(data[L"saturation_normal"]->AsNumber());
									}
									else
									{
										colorArgument.setSaturationNormal(0);
									}
									if (data.find(L"saturation_up_val") != data.end() && data[L"saturation_up_val"]->IsNumber())
									{
										colorArgument.setSaturationUpVal(data[L"saturation_up_val"]->AsNumber());
									}
									else
									{
										colorArgument.setSaturationUpVal(0);
									}
									if (data.find(L"saturation_down_val") != data.end() && data[L"saturation_down_val"]->IsNumber())
									{
										colorArgument.setSaturationDownVal(data[L"saturation_down_val"]->AsNumber());
									}
									else
									{
										colorArgument.setSaturationDownVal(0);
									}
									if (data.find(L"value_normal") != data.end() && data[L"value_normal"]->IsNumber())
									{
										colorArgument.setValueNormal(data[L"value_normal"]->AsNumber());
									}
									else
									{
										colorArgument.setValueNormal(0);
									}
									if (data.find(L"value_up_val") != data.end() && data[L"value_up_val"]->IsNumber())
									{
										colorArgument.setValueUpVal(data[L"value_up_val"]->AsNumber());
									}
									else
									{
										colorArgument.setValueUpVal(0);
									}
									if (data.find(L"value_down_val") != data.end() && data[L"value_down_val"]->IsNumber())
									{
										colorArgument.setValueDownVal(data[L"value_down_val"]->AsNumber());
									}
									else
									{
										colorArgument.setValueDownVal(0);
									}
									std::vector<int> vect;
									vect.push_back(colorArgument.getHueNormal());
									vect.push_back(colorArgument.getHueDownVal());
									vect.push_back(colorArgument.getHueUpVal());
									vect.push_back(colorArgument.getSaturationNormal());
									vect.push_back(colorArgument.getSaturationDownVal());
									vect.push_back(colorArgument.getSaturationUpVal());
									vect.push_back(colorArgument.getValueNormal());
									vect.push_back(colorArgument.getValueDownVal());
									vect.push_back(colorArgument.getValueUpVal());
									colorval.insert(make_pair(colorArgument.getTypeid(), vect));
									
								}
							}
							catch (const std::exception& ex)
							{
								printf_s("%s", std::string(ex.what()).c_str());
							}
						}
						if(root.find(L"cameragroups") != root.end() && root[L"cameragroups"]->IsArray()){
						     JSONArray dataarray=root[L"cameragroups"]->AsArray();
							
							 try
							 {
								 vector<CameraGroup*> *cgv = new  vector<CameraGroup*>();
								
								 for (int i = 0; i<dataarray.size(); i++) {
									 CameraGroup * cg = new CameraGroup();
									 cg->initVIParms(thread_arguments->vsparms->getMinCommonNum(), thread_arguments->vsparms->getIsDrawCode(), thread_arguments->vsparms->getIsDrawTail(), thread_arguments->vsparms->getDecodeInteval(), thread_arguments->vsparms->getDetectMinArea(), thread_arguments->vsparms->getDetectMaxArea(), thread_arguments->vsparms->geteShiftX(), thread_arguments->vsparms->getpShiftX(), thread_arguments->vsparms->getBloodMax(), thread_arguments->vsparms->getScale(), thread_arguments->vsparms->getInnerThresh(),colorval);
									 cg->VICode.minlengthpx = thread_arguments->vsparms->getMinlengthPx();
									 cg->VICode.mincommonnum = thread_arguments->vsparms->getMinCommonNum();
									 cg->VICode.decodeInteval = thread_arguments->vsparms->getDecodeInteval();
									 cg->VICode.detectMinArea = thread_arguments->vsparms->getDetectMinArea();
									 cg->VICode.detectMaxArea = thread_arguments->vsparms->getDetectMaxArea();
									 cg->VICode.isDrawCode = thread_arguments->vsparms->getIsDrawCode();
									 cg->VICode.isDrawTail = thread_arguments->vsparms->getIsDrawTail();
									 cg->VICode.decodeThresh = thread_arguments->vsparms->getDecodeThresh();
									 cg->VICode.lableCols = thread_arguments->vsparms->getLableCols();
									 cg->VICode.lableRows = thread_arguments->vsparms->getLableRows();
									 cg->VICode.lablemargin= thread_arguments->vsparms->getLablemargin();
									 cg->VICode.cellsize= thread_arguments->vsparms->getCellsize();
									 cg->VICode.isCupUseOptimized = thread_arguments->vsparms->getIsCupUseOptimized();
									 cg->VICode.validatenum = thread_arguments->vsparms->getValidateNum();
									 //throw (std::runtime_error(std::string("CreateThread() failed")));
									 JSONObject data = dataarray[i]->AsObject();
									 if (data.find(L"ir_camera_ip") != data.end() && data[L"ir_camera_ip"]->IsString())
									 {
										 cg->setIr_camera_ip(Common::UnicodeToAnsi(data[L"ir_camera_ip"]->AsString().c_str()));
									 }
									 if (data.find(L"ir_camera_channal") != data.end() && data[L"ir_camera_channal"]->IsNumber())
									 {
										 cg->setIr_camera_channal(data[L"ir_camera_channal"]->AsNumber());
									 }
									 if (data.find(L"rgb_camera_ip") != data.end() && data[L"rgb_camera_ip"]->IsString())
									 {
										 cg->setRgb_camera_ip(Common::UnicodeToAnsi(data[L"rgb_camera_ip"]->AsString().c_str()));
									 }
									 if (data.find(L"rgb_camera_channal") != data.end() && data[L"rgb_camera_channal"]->IsNumber())
									 {
										 cg->setRgb_camera_channal(data[L"rgb_camera_channal"]->AsNumber());
									 }
									 if (data.find(L"tank_group_id") != data.end() && data[L"tank_group_id"]->IsString())
									 {
										 cg->setTank_group_id(Common::UnicodeToAnsi(data[L"tank_group_id"]->AsString().c_str()));
									 }
									 cgv->push_back(cg);
								 }
								 thread_arguments->cgvector = cgv;
								 
							 }
							 catch (const std::exception& ex)
							 {
								 printf_s("%s", std::string(ex.what()).c_str());
							 }
							

						}else{
							std::string error_message = "The json root element is can't find 'cameragroups' JSONArray ->json:" + receiveData;
							arguments->ta_server_log->WriteErrorLog(error_message);
							printf_s("%s\n\r", error_message.c_str());
						}
						
						if(root.find(L"tanklists") != root.end() && root[L"tanklists"]->IsArray()){

							try
							{
							JSONArray dataarray=root[L"tanklists"]->AsArray();
							map<string,vector<Tank *>> *tankmap=new map<string,vector<Tank *>>();
							
							for(int i=0;i<dataarray.size();i++){
							    JSONObject data=dataarray[i]->AsObject();
							    if (data.find(L"camera_ip") != data.end() && data[L"camera_ip"]->IsString())
								{
									string camera_ip=Common::UnicodeToAnsi(data[L"camera_ip"]->AsString().c_str());
									if(tankmap->count(camera_ip)==0){
									   vector<Tank*> tankvector;
									   tankmap->insert(make_pair(camera_ip,tankvector));
									}
								}
							}
							for(int i=0;i<dataarray.size();i++){
								Tank * tank=new Tank();
							    JSONObject data=dataarray[i]->AsObject();
							    if (data.find(L"tank_id") != data.end() && data[L"tank_id"]->IsNumber())
							    {
								   tank->setTank_id(data[L"tank_id"]->AsNumber());
							    }
								if (data.find(L"tank_group_id") != data.end() && data[L"tank_group_id"]->IsString())
								{
									tank->setTank_group_id(Common::UnicodeToAnsi(data[L"tank_group_id"]->AsString().c_str()));
								}
								if (data.find(L"tank_name") != data.end() && data[L"tank_name"]->IsString())
								{
									tank->setTank_name(Common::UnicodeToAnsi(data[L"tank_name"]->AsString().c_str()));
								}
								if (data.find(L"tank_type") != data.end() && data[L"tank_type"]->IsString())
								{
									tank->setTank_type(Common::UnicodeToAnsi(data[L"tank_type"]->AsString().c_str()));
								}
								if (data.find(L"camera_ip") != data.end() && data[L"camera_ip"]->IsString())
								{
									tank->setCamera_ip(Common::UnicodeToAnsi(data[L"camera_ip"]->AsString().c_str()));
								}
								if (data.find(L"camera_type") != data.end() && data[L"camera_type"]->IsString())
								{
									tank->setCamera_type(Common::UnicodeToAnsi(data[L"camera_type"]->AsString().c_str()));
								}
								if (data.find(L"camera_channal") != data.end() && data[L"camera_channal"]->IsNumber())
							    {
									tank->setCamera_channal(data[L"camera_channal"]->AsNumber());
							    }
								if (data.find(L"area_1_ltx") != data.end() && data[L"area_1_ltx"]->IsNumber())
							    {
									tank->setArea_1_ltx(data[L"area_1_ltx"]->AsNumber());
							    }
								if (data.find(L"area_1_lty") != data.end() && data[L"area_1_lty"]->IsNumber())
							    {
									tank->setArea_1_lty(data[L"area_1_lty"]->AsNumber());
							    }
								if (data.find(L"area_1_rbx") != data.end() && data[L"area_1_rbx"]->IsNumber())
							    {
									tank->setArea_1_rbx(data[L"area_1_rbx"]->AsNumber());
							    }
								if (data.find(L"area_1_rby") != data.end() && data[L"area_1_rby"]->IsNumber())
							    {
									tank->setArea_1_rby(data[L"area_1_rby"]->AsNumber());
							    }
								
								if (data.find(L"area_2_ltx") != data.end() && data[L"area_2_ltx"]->IsNumber())
							    {
									
									tank->setArea_2_ltx(data[L"area_2_ltx"]->AsNumber());
							    }
								if (data.find(L"area_2_lty") != data.end() && data[L"area_2_lty"]->IsNumber())
							    {
									tank->setArea_2_lty(data[L"area_2_lty"]->AsNumber());
							    }
								if (data.find(L"area_2_rbx") != data.end() && data[L"area_2_rbx"]->IsNumber())
							    {
									tank->setArea_2_rbx(data[L"area_2_rbx"]->AsNumber());
							    }
								if (data.find(L"area_2_rby") != data.end() && data[L"area_2_rby"]->IsNumber())
							    {
									tank->setArea_2_rby(data[L"area_2_rby"]->AsNumber());
							    }
								if (data.find(L"exposure_val") != data.end() && data[L"exposure_val"]->IsNumber())
								{
									tank->setExposure_val(data[L"exposure_val"]->AsNumber());
								}
								if(!tank->getCamera_id().empty()){
									tankmap->find(tank->getCamera_id())->second.push_back(tank);
								}
							  }
							   thread_arguments->tankmap = tankmap;
							   
							}
							catch (const std::exception& ex)
							{
								printf_s("%s", std::string(ex.what()).c_str());
							}
							
						}else{
							std::string error_message = "The json root element is can't find 'tanklists' JSONArray ->json:" + receiveData;
							arguments->ta_server_log->WriteErrorLog(error_message);
							printf_s("%s\n\r", error_message.c_str());
						}
						
						thread_arguments->opType=0;
						this->StartNotifyThread(thread_arguments,Command::init);

					}else if(commandType.compare(Command::start)==0){

						thread_arguments->opType=1;
						StartNotifyThread(thread_arguments,Command::start);
					}else if(commandType.compare(Command::stop)==0){

						thread_arguments->opType=2;
						StartNotifyThread(thread_arguments,Command::stop);
					}else if(commandType.compare(Command::takePicture)==0){

						if (root.find(L"data") != root.end() && root[L"data"]->IsArray())
						{
							JSONArray dataarray=root[L"data"]->AsArray();
							if(dataarray.size()>0){
								JSONObject data=dataarray[0]->AsObject();
								bool isStop=true;
								TakePhotoParms *takePParms=new TakePhotoParms();
								if (data.find(L"cameraIp") != data.end() && data[L"cameraIp"]->IsString())
								{
									takePParms->setCameraIp(Common::UnicodeToAnsi(data[L"cameraIp"]->AsString().c_str()));
								}
								if (data.find(L"cameraPass") != data.end() && data[L"cameraPass"]->IsNumber())
								{
									takePParms->setCameraPass(data[L"cameraPass"]->AsNumber());
								}
								if (data.find(L"frequency") != data.end() && data[L"frequency"]->IsNumber())
								{
									takePParms->setFrequency(data[L"frequency"]->AsNumber());
								}
								if (data.find(L"imageformart") != data.end() && data[L"imageformart"]->IsNumber())
								{
									takePParms->setImageFormat(data[L"imageformart"]->AsNumber());
								}
								if (data.find(L"isImageDrowBorder") != data.end() && data[L"isImageDrowBorder"]->IsBool())
								{
									takePParms->setIsImageDrowBorder(data[L"isImageDrowBorder"]->AsBool());
								}
								if (data.find(L"Compression") != data.end() && data[L"Compression"]->IsNumber())
								{
									takePParms->setCompession(data[L"Compression"]->AsNumber());
								}
								if (data.find(L"isStop") != data.end() && data[L"isStop"]->IsBool())
								{
									isStop=data[L"isStop"]->AsBool();
								}
								if(isStop){
									thread_arguments->opType=4;
								}else{
									thread_arguments->opType=3;
								}
								thread_arguments->takePhotoParms=takePParms;
								this->StartNotifyThread(thread_arguments,Command::takePicture);
								
							}
						}else{
							std::string error_message = "The json root element is can't find 'data' JSONArray ->json:" + receiveData;
							arguments->ta_server_log->WriteErrorLog(error_message);
							printf_s("%s\n\r", error_message.c_str());
						}
					}else if(commandType.compare(Command::test)==0){

						if (root.find(L"data") != root.end() && root[L"data"]->IsArray())
						{
							JSONArray dataarray=root[L"data"]->AsArray();
							if(dataarray.size()>0){
								JSONObject data=dataarray[0]->AsObject();
								SimulatedData *simulated=new SimulatedData("10001",10,10);
								if (data.find(L"ecode") != data.end() && data[L"ecode"]->IsString())
								{
									simulated->setEcode(Common::UnicodeToAnsi(data[L"ecode"]->AsString().c_str()));
								}
								if (data.find(L"x") != data.end() && data[L"x"]->IsNumber())
								{
									simulated->setX(data[L"x"]->AsNumber());
								}
								if (data.find(L"y") != data.end() && data[L"y"]->IsNumber())
								{
									simulated->setY(data[L"y"]->AsNumber());
								}
								thread_arguments->simulatedData=simulated;
								thread_arguments->opType=5;
								this->StartNotifyThread(thread_arguments,Command::test);
							}
						}
					}

				}else{
					std::string error_message = "The json root element is can't find 'commandType' attribute ->json:" + receiveData;
					arguments->ta_server_log->WriteErrorLog(error_message);
					printf_s("%s\n\r", error_message.c_str());
				}
				delete jsonResult;
			}
		}
	}
}

void EchoService::StartNotifyThread(THREAD_ARGUMENTS * thread_arguments,std::string cammadType)
{
	
	VINotify *vinotify=new VINotify();
	DWORD thread_id;
	if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)vinotify->ThreadRunnableHandleRequest, thread_arguments, 0, (LPDWORD)&thread_id) == NULL) {
		throw (std::runtime_error(std::string("CreateThread() failed")));
		printf_s("%s\n\r", std::string("CreateThread() failed").c_str());
	}
	if (thread_arguments->ta_server_log_trace_mode) {
		std::string trace_message = std::string("Command "+cammadType+" thread created (TID) " + std::to_string(thread_id));
		thread_arguments->ta_server_log->WriteTraceLog(trace_message);
		printf_s("%s\n\r", trace_message.c_str());
	}
}

