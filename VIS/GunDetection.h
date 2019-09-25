#ifndef GUNDETECTION_H_
#define GUNDETECTION_H_


#include "defs.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<cmath>



using namespace cv;
using namespace std;


class LT_API GunDetection
{
public:
	GunDetection();
	~GunDetection();
	
	void GunDetect(const Mat &src,  vector<Rect>&rectroi,  vector<Point> &points);
	bool rect_rank_x(vector<Rect> &vec_rects);
	
};

#endif