/*
 * endo_core.h
 *
 *  Created on: Oct 28, 2017
 *      Author: gyz
 */

#ifndef ENDO_CORE_H_
#define ENDO_CORE_H_
#define NOMINMAX
#include <windows.h>
#include "yolo_v2_class.hpp"	
#include <tag.hpp>
#include <trace.hpp>
#include <map>
#include <chrono>
//#include "windows.h"
#include <io.h>
#include<experimental\/filesystem>
#include <thread>
#include <queue>

#include "GunDetection.h"
#ifndef WITHOUT_CUDA
#include "RgbDetector.h"
#include "GunUseStatus.h"
#include "liguidstatus.h"
#include "rgbMat_tankID.h"
#include "Cv310Text.h"
#endif



using namespace std;
using namespace aip;

typedef void(*RgbCallBack)(std::string tankGroupid, std::string rgbip, std::string irip, std::string  eventType,std::string TankType,cv::Rect roi,bool isHasPerson);

typedef void(*notifyCallBack)(std::string rgbip, cv::Mat img);

struct Rectcnt {

	int g_endoNum;
	//int g_endocnt;
	bool Resultp;

	bool autoStop;
};
class LT_API CEndoCore {
protected:
	bool firstTime;
public:
	Tag tag;
	Trace trace;
	map<string, vector<Mat>> icons;
	vector<int> flags;					//图像处理任务标识
	map<int, vector<Rect>> roiRects;	//图像处理任务对应的工作区域
	map<int, vector<Point2f>> roiStatus;	//图像处理任务对应的工作区域的状态值
	map<int, vector<int>> colorVal; //HSV 标准值及范围浮动值 外层map key 0，1，2 分代表 枪，酶洗液，消毒液  
	double MaxDistance;                              //value 0,1,2，3，4，5，6，7，8 分别对应  h（ 标准值0 ，向下浮动值1 ，向上浮动值2） s（ 标准值3 ，向下浮动值4，向上浮动值5） v（ 标准值6 ，向下浮动值7，向上浮动值8）							
	double minArea;
	double maxArea;
	double scale;
	double innerthresh;        // 算法 decode 参数的二值化阈值量
	int eshiftx;  //内镜map偏移量
	int pshiftx;  //人员map偏移量
	int preProcThreshRange;
	double preProcThreshInner;
	double preProcThreshOuter;
	float liquidRatioThresh;
	float liquidRatioThreshH;
	float liquidRatioThreshL;
	GunDetection GunDetect;
	
	

#ifndef WITHOUT_CUDA
	static RgbDetector RgbDetector;
#endif
	static bool f_perframe;
	int numframe;
	bool sw;
	//static Mat rmap[2][2];	
	static map<long, GunUseStatus> pntGun;
	static map<string, Mat **>SteroParm;
	
	//气枪有关参数
	static vector<vector<Point>> gunps;

	static map<string, map<string, Rect>>CEndoCore::EndoRect;
	static queue <map<std::string, rgbMat_tankID>> RgbMatQ;
	static std::map<string, map<std::string, cv::Rect>> rgbROI;
	static RgbCallBack callback;
	static map<std::string, rgbMat_tankID> tank;
	static map<string, map<std::string, Rectcnt>> rectcnt;
	//槽体流程
	static std::map<string, vector<std::string>> * flowtypemap;

	static std::map<string, map<string, string>>  TankTypeToIP;
	 
public:
	CEndoCore();
	~CEndoCore();
	int Process(string rgbip,int tankwidth,const Mat &srcIr, const Mat &srcRgb, Mat &dst, map<int, vector<vector<string>>> &objs, string &errorMsg);
	int ImportIcon(const string &code, const string &filename);
	static int LoadStereoParam();
	static int loadfile();
	static bool isRgbCheck;
	static void setUserCodes(std::string code);
	static void setEnableShowRect(bool enable);
	static void setisRgbCheck(bool isRgbCheckP);
	static void setPath(std::string path);
	static void setWeightsPath(std::string cfg, std::string weights, std::string names);
	static void initRgbCheck(std::map<string, map<std::string, cv::Rect>> rgbROI, RgbCallBack callback);
	static void startRgbCheck(void(*notifyCallBack)(std::string rgbip, cv::Mat img));
	static void stopRgbCheck();
	static void RgbCheck();
	static void setPopEndoscope(std::string ip, std::string workstep);
	static void SetFlow(std::map<string, vector<std::string>> * flowtypemap);
	static void SetPersonDefaultNameForDemo(string name);
	static void SetEndoscopeDefaultNameForDemo(string name);
	static void setRgbCheckFrameNum(int num);
	static void setIsOutByIshasEndoscope(bool IsOutByIshasEndoscope);
	static map<string, std::string> findSaticPreSetp(std::string tanktype);
	int IrCheck(cv::Rect irROI, std::string irip, Mat irimg, Mat &dst, map<int, vector<vector<string>>> &objs, string &errorMsg);
	//void SaveRgbImageMat(cv::Mat rgb, std::string ip, std::string tankGroupid);
	void SaveRgbImageMat(cv::Mat rgb, std::string rgbip, std::string irip, std::string tankGroupid);
	static bool isAtefficailArea(Point point);
private:
	static std::string userCodes;
	static std::string path;
	static std::string cfg;
	static std::string weights;
	static std::string names;
	bool IsRgbCheckByTrace();
	vector<IRbox> ConvertIRBox(Mat rmap[2][2],std::vector<bbox> rgbBox,float scalex,float scaley);
	long getTimeStamp();
	bool IsExistGunUse(int i,Point &Gunxy);
	//long FindMinDis(Point &Gunxy);
	void RemoveTrace();
	bool isExistTrace(int code, vector<TraceInfo>::iterator &ti);
	//void IsGunUse(const Mat &srcRgb, const Rect &roi, const vector<RotatedRect> &minRect, vector<Point> &pntGunHeads);
	vector<liguidstatus>liguid;
	static bool IsEnableShowRect;
	static bool isRgbCheckStop;
	static notifyCallBack notifyCallBackfun;
	static int addFrameNum;
	static string personDefaultNameForDemo;
	static string endoscopeDefaultNameForDemo;
	static bool ishaspersonbydemo;
	static bool IsoutByIshasEndoscope;
};

#endif /* ENDO_CORE_H_ */
