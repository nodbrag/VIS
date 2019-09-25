#pragma once
#include "TagPack.h"
#include "MultiTrace.h"
#include <map>
class LT_API CViTask
{
public:
	CTagPack tp;			//用于提取图像中所有的标签信息
	CMultiTrace traces;		//管理所有目标跟踪轨迹
public:
	CViTask();
	~CViTask();
	int ViCall(const string &rgbId, const Mat &rgbImg, const string &irId, const Mat &irImg, const vector<int> &flags, map<int, vector<Rect>> &roiRects, Mat &overlayImg, map<int, vector<vector<string>>> &objs, string &errorMsg);
};

