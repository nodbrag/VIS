#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "defs.h"


using namespace cv;
using namespace std;


//标签信息
typedef struct tagTagInfo
{
	Point2f pos;	//位置
	Rect2f boundingRect;	//外框
	vector<float> codeLevel;	//编码占空比
	bool usedFlag;	//处理标记
	float grayLevel;	//起始位平均灰度
} TagInfo;


//标签包
class CTagPack
{
private:
	Mat smallTagEle;	//连通缩小标签的形态学操作参数
	Mat tagEle;			//连通原图标签的形态学操作参数
	Mat tagHoleEle;		//填补原图标签孔洞的形态学操作参数
public:
	int codeLength;	//标签长度

	//调试参数
	float downScale;	//图像缩小倍率，缩小图像加速处理
	int thres;		//二值化阈值
	float clipScale;	//截取标签图片外框放大倍率
	float tagAreaMin;	//标签面积下限
	float tagAreaMax;	//标签面积上限
	bool showFlag;		//显示调试图像

	CTagPack();
	~CTagPack();

	// 设置形态学操作参数
	void SetMorphElement(Mat &ele, int val, int shape);

	//提取标签信息
	void Extract(const Mat &img, vector<TagInfo> &ti, const vector<Rect> &roiRects);
};

