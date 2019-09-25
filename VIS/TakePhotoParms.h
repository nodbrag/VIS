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
	//���ip 
	std::string _cameraIp; 
	//���ͨ��
	long _cameraPass;
	//frequency: 1 ������һ��ͼƬ 0:ִ�з���ͼƬ���� ֱ��ֹͣ
	int _frequency;
	//ͼ���ʽ(0:jpeg,1:png,2:bmp)
	int _imageFormat;
	//ͼƬ�Ƿ����ʶ��������ο�
	bool _IsImageDrowBorder;
	//ѹ���� 0-100
	int _compression;
};

