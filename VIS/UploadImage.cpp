#include "UploadImage.h"

#include <mutex>

std::mutex mlx;
bool UploadImage::isUploadThread = false;

#define PRINT_LOG [](const std::string& strLogMsg) { printf_s("%s\r\n",strLogMsg.c_str()); }
UploadImage::UploadImage()
{
	XmlConfig config;
	TiXmlDocument doc = config.initXml();
	this->IntervalUploadImageTime = std::atoi(config.GetVSParmsNodeValue("IntervalUploadImageTime").c_str());
	this->saveImagePath= config.GetVSParmsNodeValue("SaveImagePath");
	this->host = config.GetVSParmsNodeValue("Host");
	this->username = config.GetVSParmsNodeValue("UserName");
	this->paassword = config.GetVSParmsNodeValue("Password");
	this->port = std::atoi(config.GetVSParmsNodeValue("Port").c_str());
	this->uploadImageMode = std::atoi(config.GetVSParmsNodeValue("UploadImageModel").c_str());
	this->hospitalcatalog = config.GetVSParmsNodeValue("HospitalCatalog");
	this->isUploadimage = false;
	std::string isuploadimage = config.GetVSParmsNodeValue("IsUploadImage");
	if (!isuploadimage.empty() && std::atoi(isuploadimage.c_str()) == 1) {
		this->isUploadimage = true;
	}
	doc.Clear();
	if (!this->saveImagePath.empty()) {
		if (!file.checkFolderExist(this->saveImagePath))
			file.createDirectory(this->saveImagePath);
	}
	this->log = new Log(Common::GetLogPath());
	if (this->isUploadimage&&this->uploadImageMode==1) {
		this->FTPClient = new CFTPClient(PRINT_LOG);
		this->FTPClient->InitSession(this->host, this->port, this->username, this->paassword);
		if (!this->hospitalcatalog.empty()) {
			if (!file.checkFolderExist(this->hospitalcatalog))
				this->FTPClient->CreateDir("/" + this->hospitalcatalog);
		}
	}
}

UploadImage::~UploadImage()
{

}
void UploadImage::setRecentInsertTime(ec::Time time) {
	this->recentInsertTime = time;
}
ec::Time UploadImage::getRecentInsertTime() {
	return this->recentInsertTime;
}

void UploadImage::addImageName(UploadImage *ui,cv::Mat rgbImg, cv::Mat irImg, long userid, int channal) {
	if (!ui->isUploadimage) return;
	if (ui->imgfiles.size() > 1000) return;
	
	ec::Time now;
	std::string irfilename = now.toDate().format("%Y%m%d%H%M%S") + "_ir.jpg";
	std::string rgbfilename = now.toDate().format("%Y%m%d%H%M%S") + "_rgb.jpg";
	if (ui->saveImagePath.empty()) {
		std::string msg = "error:存储图片路径为空！";
		this->log->WriteErrorLog(msg);
		printf_s("%s\r\n", msg.c_str());
		return;
	}
	ec::Date date;
	ec::Time time;
	long timespan=time.diff(ui->recentInsertTime, ec::Duration::Second);
	//每间隔一段时间才可以插入
	if (timespan >= ui->IntervalUploadImageTime) {

		if (ui->uploadImageMode == 0) {

			LPNET_DVR_JPEGPARA jpegpara = new NET_DVR_JPEGPARA;
			if (jpegpara != NULL) {
				jpegpara->wPicQuality = 2;
				jpegpara->wPicSize = 5;
			}
			int w = 1280;
			int h = 720;
			int px = w * h;
			char * imgdata = new char[px];
			LPDWORD size = 0;
			std::vector<uchar>data(px);
			
			if (!NET_DVR_SetCapturePictureMode(BMP_MODE)) {
				this->log->WriteErrorLog("NET_DVR_SetCapturePictureMode error code:" + std::to_string(NET_DVR_GetLastError()));
				return;
			}
			bool flag = NET_DVR_CaptureJPEGPicture_NEW(userid, channal, jpegpara, imgdata, px, size);
			if (!flag) {
				
				this->log->WriteErrorLog("NET_DVR_CaptureJPEGPicture_NEW error code:" + std::to_string(NET_DVR_GetLastError()));
				return;
			}

			for (int i = 0; i < px; i++) {
				data[i] = imgdata[i];
			}
			delete imgdata;
			cv::Mat img = cv::imdecode(cv::Mat(data), 1);
			if (img.rows > 0 && img.cols > 0) {
				img.copyTo(rgbImg);
			}
		}
		if (rgbImg.cols > 0 && rgbImg.rows > 0) {
			//bool irflag = cv::imwrite(ui->saveImagePath + "/" + irfilename, irImg);
			bool rgbflag = cv::imwrite(ui->saveImagePath + "/" + rgbfilename, rgbImg);
			if (rgbflag) {
				std::unique_lock<std::mutex> ulk(mlx);
				ec::Time now;
				timespan = 0;
				ui->recentInsertTime.setSeconds(now.getUTCFullSeconds());
				ui->recentInsertTime.setMicroSeconds(now.tv_usec());
				if (ui->uploadImageMode == 1) {
					//ui->imgfiles.push_back(irfilename);
					ui->imgfiles.push_back(rgbfilename);
				}
			}
		}
	}
}

void UploadImage::start(UploadImage *ui) {

	UploadImage::isUploadThread = true;
	DWORD thread_id;
	if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ui->Upload, ui, 0, (LPDWORD)&thread_id) == NULL) {
		throw (std::runtime_error(std::string("CreateThread() failed")));
		printf_s("%s\r\n", "CreateThread() failed");
	}
	std::string trace_message = std::string("Upload Images  thread created (TID)" + std::to_string(thread_id));
	this->log->WriteTraceLog(trace_message);
	printf_s("%s\r\n", trace_message.c_str());
}
std::vector<std::string>::iterator UploadImage::getIterator(UploadImage *ui){
	std::unique_lock<std::mutex> ulk(mlx);
	std::vector<std::string>::iterator it = ui->imgfiles.begin();
	return it;
}
void UploadImage::Upload(UploadImage *ui) {

	while (UploadImage::isUploadThread)
	{
		if (ui->imgfiles.size() > 0) {
			std::vector<std::string>::iterator it = ui->getIterator(ui);
			//上传业务
			ui->FTPClient->UploadFile(ui->saveImagePath + "/" + *it, "/ " + ui->hospitalcatalog + "/" + *it);
			ui->imgfiles.erase(it);//移除对象
		}
		Sleep(1000);
	}
}
