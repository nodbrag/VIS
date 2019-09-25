#pragma once
#ifdef _WIN32
#define OPENCV
#endif
#include "yolo_v2_class.hpp"	// imported functions from DLL

#ifdef OPENCV
#include <opencv2/opencv.hpp>			// C++
#include "opencv2/core/version.hpp"
#ifndef CV_VERSION_EPOCH
#include "opencv2/videoio/videoio.hpp"
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_MAJOR)""CVAUX_STR(CV_VERSION_MINOR)""CVAUX_STR(CV_VERSION_REVISION)
//#pragma comment(lib, "opencv_world" OPENCV_VERSION ".lib")
#else
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_EPOCH)""CVAUX_STR(CV_VERSION_MAJOR)""CVAUX_STR(CV_VERSION_MINOR)
#pragma comment(lib, "opencv_core" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_imgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_highgui" OPENCV_VERSION ".lib")
#endif
#endif
struct IRbox {
	unsigned int x, y;	// (x,y) - top-left corner, (w, h) - width & height of bounded box
						//float prob;					// confidence - probability that the object was found correctly
	std::string obj_name;		// class of object - from range [0, classes-1]
								//unsigned int track_id;		// tracking id for video (0 - untracked, 1 - inf - tracked object)
};
struct bbox {
	unsigned int x, y, w, h;	// (x,y) - top-left corner, (w, h) - width & height of bounded box
	float prob;					// confidence - probability that the object was found correctly
	unsigned int obj_id;		// class of object - from range [0, classes-1]
	unsigned int track_id;		// tracking id for video (0 - untracked, 1 - inf - tracked object)
	std::string obj_name;		// class of object - from range [0, classes-1]
								
};

class RgbDetector
{
public:
	RgbDetector();
	~RgbDetector();
	void initDetector(std::string cfg_filename, std::string weight_filename, std::string obj_names, int gpu_id=0);
	std::vector<std::string> objects_names_from_file(std::string const filename);
	std::vector<std::string> obj_names;
	void RgbDetect(const cv::Mat &mat_img, const cv::Rect &roi,  std::vector<bbox> *ResultVec);
	Detector *detector;
};

