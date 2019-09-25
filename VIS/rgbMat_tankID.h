#pragma once
#include "defs.h"
#include <opencv2/opencv.hpp>	
class LT_API rgbMat_tankID
{
public:
	rgbMat_tankID();
	~rgbMat_tankID();
public:
	std::string irip;
	cv::Mat rgbmat;
	std::string tankGroupid;
	
};

