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


// ������������
inline float CalcDistance(const Point2f &p0, const Point2f &p1)
{
	float dx = p0.x - p1.x;
	float dy = p0.y - p1.y;
	return sqrt(dx*dx + dy*dy);
}


class CTrace
{
private:
	int lost;		//��ʧ����

public:
	ofstream ofs;	//��������ļ�
	Point2f predict_pt;	//Ԥ��ֵ
	KalmanFilter kf;	//Ԥ��Ŀ��λ�ã����ڽ��桢�ڵ�ʱ�б�Ŀ��
	Mat measurement;	//����ֵ
	int head;		//ͷλ��
	int length;		//����
	int life;		//����
	string code;	//��Ȩ����
	string weightedCode;	//��Ȩ����
	Point2f tracePoint[MAX_LENGTH];	//�켣��
	bool usedFlag;	//��ʹ�ñ��
	vector<float> codeLevelWeighted; //��Ȩ����ռ�ձ�
	TagInfo tagInfo;	//��ǩ��Ϣ
	float minWeight;		//��СȨ��
	vector<float> decodeThres;	//������ֵ
public:
	CTrace();
	~CTrace();
	void Update(const TagInfo &ti);	//��Ŀ����¹켣
	void Update();	//��Ŀ����¹켣
	void Draw(Mat &img, Scalar color, float fx, float fy);	//���켣
	void Decode(const vector<float> &codeLevel, string &code);	//����
};

