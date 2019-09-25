#pragma once
#include "defs.h"

#include <opencv2/opencv.hpp>		


class LT_API GunUseStatus
{
public:
	GunUseStatus();
	~GunUseStatus();
public:
	std::string codeId;
	cv::Point BeginPnt;
	cv::Point Endpnt;
	bool  IsGunUse;


};

