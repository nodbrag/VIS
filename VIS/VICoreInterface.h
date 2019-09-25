#pragma once
#include "endo_core.h"
class VICoreInterface
{
public:
	VICoreInterface();
	~VICoreInterface();
	int viCall(string rgbId, cv::Mat rgbImg, string irId, cv::Mat irImg, vector<int> flags, int tankWidth, map<int, vector<Rect> > roiRects, cv::Mat &overlayImg, map<int, vector<vector<string> > > &objs, string &errorMsg);
	int minlengthpx;
	int mincommonnum;
	bool isDrawCode;
	bool isDrawTail;
	float decodeInteval;
	int detectMinArea;
	int detectMaxArea;
	float decodeThresh;
	int lableRows;
	int lableCols;
	int lablemargin;
	int validatenum;
	int cellsize;
	int isCupUseOptimized;
	void init(int mincommonnum, bool isDrawCode, bool isDrawTail, float decodeInteval, float detectMinArea, float detectMaxArea, int eshiftx,int pshiftx, int bloodMax, float scale, int innerThresh, std::map<int, std::vector<int>> colorval);
	int IrCheck(cv::Rect irROI, std::string ip, Mat irimg, cv::Mat &overlayImg, map<int, vector<vector<string>>> &objs, string &errorMsg);
	void SaveRgbImageMat(cv::Mat rgb, std::string rgbip, std::string irip, std::string tankGroupid);
private:
	CEndoCore core;
	map<int, int> cmap;
};