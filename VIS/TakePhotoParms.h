#pragma once
#include <string>

class TakePhotoParms
{
public:
	TakePhotoParms(void);
	~TakePhotoParms(void);
	 std::string getCameraIp();
	 void setCameraIp(std::string cameraIp);
	 long getCameraPass();
	 void setCameraPass(long cameraPass);
	 int getFrequency();
	 void setFrequency(int frequency);
	 int getImageFormat();
	 void setImageFormat(int imageFormat);
	 bool getIsImageDrowBorder();
	 void setIsImageDrowBorder(bool isImageDrowBorder);
	 int getCompression();
	 void setCompession(int comperssion);
private:
	//相机ip 
	std::string _cameraIp; 
	//相机通道
	long _cameraPass;
	//frequency: 1 仅发生一次图片 0:执行发生图片数据 直到停止
	int _frequency;
	//图标格式(0:jpeg,1:png,2:bmp)
	int _imageFormat;
	//图片是否包含识别物体矩形框
	bool _IsImageDrowBorder;
	//压缩率 0-100
	int _compression;
};

