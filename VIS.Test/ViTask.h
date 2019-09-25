#pragma once
#include "TagPack.h"
#include "MultiTrace.h"
#include <map>
class LT_API CViTask
{
public:
	CTagPack tp;			//������ȡͼ�������еı�ǩ��Ϣ
	CMultiTrace traces;		//��������Ŀ����ٹ켣
public:
	CViTask();
	~CViTask();
	int ViCall(const string &rgbId, const Mat &rgbImg, const string &irId, const Mat &irImg, const vector<int> &flags, map<int, vector<Rect>> &roiRects, Mat &overlayImg, map<int, vector<vector<string>>> &objs, string &errorMsg);
};

