#pragma once

#define MAX_TRACE	40
#define MAX_DIST	100	//跟踪距离上限

#define COLOR_RED	Scalar(0,0,0xFF)
#define COLOR_CYAN	Scalar(0xFF,0xFF,0)
#define COLOR_LIGHTBLUE	Scalar(0xE6,0xD8,0xAD)
#define COLOR_PURPLE	Scalar(0x80,0,0x80)
#define COLOR_YELLOW	Scalar(0,0xFF,0xFF)
#define COLOR_LIME	Scalar(0,0xFF,0)
#define COLOR_MAGENTA	Scalar(0xFF,0,0xFF)
#define COLOR_SILVER	Scalar(0xC0,0xC0,0xC0)
#define COLOR_GRAY	Scalar(0x80,0x80,0x80)
#define COLOR_ORENGE	Scalar(0,0xA5,0xFF)
#define COLOR_BROWN	Scalar(0x2A,0x2A,0xA5)
#define COLOR_MAROON	Scalar(0,0,0x80)
#define COLOR_BLUE	Scalar(0xFF,0,0)
#define COLOR_GREEN	Scalar(0,0x80,0)
#define COLOR_OLIVE	Scalar(0,0x80,0x80)
#define COLOR_DARKBLUE	Scalar(0xA0,0,0)

#include "Trace.h"


typedef struct tagPair
{
	float dist;	//距离
	int traceIdx;	//轨迹标号
	int tagIdx;	//目标标号
} Pair;


class LT_API CMultiTrace
{
private:
	Scalar colorName[16];
public:
	CTrace trace[MAX_TRACE];

public:
	CMultiTrace();
	~CMultiTrace();
	void Update(vector<TagInfo> &ti);
	void Draw(const Mat &src, Mat &dst, const Size &dstSize = Size());
	void SetMinWeight(float weight);
	void SetDecodeThres(const vector<float> &val);
};

