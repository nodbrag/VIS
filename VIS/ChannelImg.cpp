#include "ChannelImg.h"

ChannelImg::ChannelImg()
{
	this->imgcount=0;
	this->lRealPlayHandle=-1;
	this->test=0;
}


ChannelImg::~ChannelImg(void)
{
}

void ChannelImg::setImg(cv::Mat img )
{
	
	this->img=img;
}

cv::Mat ChannelImg::getImg()
{
	return this->img.clone();
}

long ChannelImg::getlRealPlayHandle( )
{
	return lRealPlayHandle;
}

void ChannelImg::setlRealPlayHandle(long lRealPlayHandle)
{
	this->lRealPlayHandle=lRealPlayHandle;
}

void ChannelImg::setCount(int imgcount)
{

	this->imgcount=imgcount;
	
}

long ChannelImg::getCount()
{
	
	return imgcount;
}
