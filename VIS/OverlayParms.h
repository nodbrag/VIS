#pragma once
#include <opencv2\opencv.hpp>
#include <string>
class OverlayParms
{
public:
	OverlayParms();
	~OverlayParms();
private:
	 cv::Mat overlayImg;
	 int overlayChangeCount;
	 //摄像机ip
	 std::string _cameraIp;
	 //摄像机通道
	 long _cameraPass;

};

