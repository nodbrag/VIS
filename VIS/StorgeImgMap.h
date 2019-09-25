#pragma once
#include <map>
#include "ChannelImg.h"
#include "date.h"
using namespace std;

class StorgeImgMap
{
public:
	StorgeImgMap(void);
	~StorgeImgMap(void);
	void add(long,cv::Mat img);
	map<long, cv::Mat>  getImg(long IRlRealHandle,long RGBRealHanle);
	map<long,ChannelImg *> *Imgmaps;
	cv::Mat getImg(long IRlRealHandle);
	map<long, ec::Time> RgbMonitor;
private:
	int flag;
	 
};

