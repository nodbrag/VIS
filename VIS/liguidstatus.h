#pragma once
#include "defs.h"
#include <opencv2/opencv.hpp>		
class LT_API liguidstatus
{
public:
	liguidstatus();
	~liguidstatus();
public:
	int x;
	int y;
	int Lcnt;
	bool LhasSend;

};

