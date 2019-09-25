#pragma once
#include <opencv2\opencv.hpp>
#include<iostream>
#include <string>
#include<vector>
#include<map>
#include "Log.h"
#include "date.h"
#include "XmlConfig.h"
#include "FTPClient.h"
#include "FileHelper.h"
#include "HCNetSDK.h"




class UploadImage
{
public:
	UploadImage();
	~UploadImage();
	void start(UploadImage *ui);
	
	void addImageName(UploadImage *ui,cv::Mat rgbimg,cv::Mat irimg,long userid,int channal);
	static void Upload(UploadImage *ui);
	ec::Time getRecentInsertTime();
	void setRecentInsertTime(ec::Time time);
	std::vector<std::string> imgfiles;
	std::vector<std::string>::iterator getIterator(UploadImage *ui);
	bool isUploadimage;
	int uploadImageMode;
	static bool isUploadThread;
private: 
	 Log *log;
	 FileHelper file;
	 ec::Time recentInsertTime;
	 int IntervalUploadImageTime;
	
	 std::string saveImagePath;
	 std::string host;
	 std::string username;
	 std::string paassword;
	 std::string hospitalcatalog;
	
	 CFTPClient *FTPClient;
	 std::vector<std::string>::iterator it;
	 int port;
};

