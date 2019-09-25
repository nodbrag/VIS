#pragma once
#include <opencv2\opencv.hpp>
#include <string.h>


  
class ChannelImg
{
public:
	 ChannelImg();
	~ChannelImg(void);
	void setImg(cv::Mat mat);
	cv::Mat getImg();
	long getlRealPlayHandle();
	void setlRealPlayHandle(long lRealPlayHandle);
	void setCount(int imgcount);
	long getCount();
	int test;
private:
	cv::Mat img;
	long lRealPlayHandle;
	long imgcount;
	
};

