#pragma once
#include <string>
using std::string;

class DataParms
{
public:
	DataParms();
	DataParms(string cameraIp, string cameraPass,int type,string idCode, string personCode, int gunStopID,int x,int y,int width,int height,string imagedatas,int imageFormart);
	DataParms(string cameraIp, string cameraPass, int type, string idCode, string personCode, int dryischeck, int cleanStatus, string cleanStartTime, string cleanEndTime, string tankType,int gunStopID, int x, int y, int width, int height, string imagedatas, int imageFormart);
	~DataParms(void);
	//设置摄像机ip
	void setCameraIp(string cameraIp);
	string getCameraIp();
	string getCameraPass();
	//设置摄像机通道
	void setCameraPass(string cameraPass);
	int getType();
	//设置信息类别 1：人员信息 2：内镜信息 3：枪信息 4：换液信息 5：换布信息 10：图片信息
	void setType(int type);
	string getIdCode();
	//设置标识码(人员标识码或 内镜标识码, 抢标识码 其他 为空)
	void setIdCode(string idCode);
	int getGunStopID();
	//设置枪使用停止标识 (0:开始使用 1:结束使用) 
	void setGunStopID(int gunStopID);
	int getX();
	//设置左上角X  坐标
	void setX(int x);
	int getY();
	//设置左上角Y 坐标
	void setY(int y);
	int getWidth();
	//设置识别矩形宽度
	void setWidth(int width);
	int getHeight();
	//识别矩形高度
	void setHeight(int height);
	string getImageDatas();
	//图片数据
	void setImageDatas(string imagedatas);
	int getImageFormart();
	//图片格式(0:jpeg,1:png,2:bmp)
	void setImageFormart(int imageFormart);

	string getPersonCode();
	void setPersonCode(string personCode);

	//内镜清洗状态 0 结束清洗 1 开始清洗
	int getCleanStatus();
	void setCleanStatus(int cleanStatus);
	//内镜开始时间
	string getCleanStartTime();
	void setCleanStartTime(string cleanstarttime);
	//内镜结束时间
	string getCleanEndTime();
	void setCleanEndTime(string cleanendtime);
	//槽体类型
	string  getTankType();
	void setTankType(string tankType);
	//干燥是否检测出来
	int getDryischeck();
	void setDryischeck(int dryischeck);

private:
	//摄像机ip
	string _cameraIp;
	//摄像机通道
	string _cameraPass;
	//信息类别 1：人员信息 2：内镜信息 3：枪信息 4：换液信息 5：换布信息 10：图片信息
	int _type;
	//标识码(人员标识码或 内镜标识码, 抢标识码 其他 为空)
	string _idCode;
	//枪使用停止标识 (0:开始使用 1:结束使用) 
	int  _gunStopID;
	//左上角X  坐标
	int _x;
	//左上角Y 坐标
	int _y;
	//识别矩形宽度
	int _width;
	//识别矩形高度
	int _height;
	//图片数据
	string _imagedatas;
	//图片格式(0:jpeg,1:png,2:bmp)
	int _imageFormart;
	//内镜绑定人员code；
	string personCode;
	//内镜清洗状态 0 结束清洗 1 开始清洗
	int cleanStatus;
	//内镜开始时间
	string cleanStartTime;
	//内镜结束时间
	string cleanEndTime;
	//槽体类型
	string  tankType;
	//干燥是否检测出来
	int dryischeck;
	
	

};

