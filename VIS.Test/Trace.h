#pragma once

#define MAX_LENGTH	30
#define MAX_LOST	25


#include <opencv2/imgproc.hpp> 
#include <opencv2/video/tracking.hpp>
#include <vector>
#include "TagPack.h"
#include <fstream>


using namespace cv;
using namespace std;


// 计算两点间距离
inline float CalcDistance(const Point2f &p0, const Point2f &p1)
{
	float dx = p0.x - p1.x;
	float dy = p0.y - p1.y;
	return sqrt(dx*dx + dy*dy);
}


class CTrace
{
private:
	int lost;		//丢失次数

public:
	ofstream ofs;	//输出数据文件
	Point2f predict_pt;	//预测值
	KalmanFilter kf;	//预测目标位置，用于交叉、遮挡时判别目标
	Mat measurement;	//测量值
	int head;		//头位置
	int length;		//长度
	int life;		//寿命
	string code;	//加权编码
	string weightedCode;	//加权编码
	Point2f tracePoint[MAX_LENGTH];	//轨迹点
	bool usedFlag;	//被使用标记
	vector<float> codeLevelWeighted; //加权编码占空比
	TagInfo tagInfo;	//标签信息
	float minWeight;		//最小权重
	vector<float> decodeThres;	//解码阈值
public:
	CTrace();
	~CTrace();
	void Update(const TagInfo &ti);	//有目标更新轨迹
	void Update();	//无目标更新轨迹
	void Draw(Mat &img, Scalar color, float fx, float fy);	//画轨迹
	void Decode(const vector<float> &codeLevel, string &code);	//解码
};

