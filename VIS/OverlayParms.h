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
	 //�����ip
	 std::string _cameraIp;
	 //�����ͨ��
	 long _cameraPass;

};

