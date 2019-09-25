#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "defs.h"


using namespace cv;
using namespace std;


//��ǩ��Ϣ
typedef struct tagTagInfo
{
	Point2f pos;	//λ��
	Rect2f boundingRect;	//���
	vector<float> codeLevel;	//����ռ�ձ�
	bool usedFlag;	//������
	float grayLevel;	//��ʼλƽ���Ҷ�
} TagInfo;


//��ǩ��
class CTagPack
{
private:
	Mat smallTagEle;	//��ͨ��С��ǩ����̬ѧ��������
	Mat tagEle;			//��ͨԭͼ��ǩ����̬ѧ��������
	Mat tagHoleEle;		//�ԭͼ��ǩ�׶�����̬ѧ��������
public:
	int codeLength;	//��ǩ����

	//���Բ���
	float downScale;	//ͼ����С���ʣ���Сͼ����ٴ���
	int thres;		//��ֵ����ֵ
	float clipScale;	//��ȡ��ǩͼƬ���Ŵ���
	float tagAreaMin;	//��ǩ�������
	float tagAreaMax;	//��ǩ�������
	bool showFlag;		//��ʾ����ͼ��

	CTagPack();
	~CTagPack();

	// ������̬ѧ��������
	void SetMorphElement(Mat &ele, int val, int shape);

	//��ȡ��ǩ��Ϣ
	void Extract(const Mat &img, vector<TagInfo> &ti, const vector<Rect> &roiRects);
};

