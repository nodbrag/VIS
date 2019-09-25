/*----------------------------------------------
* Usage:
* endoscope_test <ir_video_name> <rgb_video_name>
*--------------------------------------------------*/

#include <opencv2/core/utility.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cstring>
#include "ViTask.h"


#define OUTPUT_DATA
//#define OUTPUT_VIDEO


using namespace std;
using namespace cv;


int main(int argc, char** argv) {
	Mat frame;				//图像帧
	Mat frameRgb;			//RGB图像帧
	TickMeter tm;	//计时器
	CViTask vt;		//图像处理任务
	vector<int> vtFlags;	//图像处理任务标识
	vtFlags.push_back(0);
	map<int, vector<vector<string>>> objs;	//返回识别结果信息
	string errorMsg;	//返回错误信息


						// 调试用参数
	int showWait = 1;
	int startFrame = 0;
	float weight = .01f;
	vt.tp.tagAreaMax = 9000;

	//设置编码更新权重
	vt.traces.SetMinWeight(weight);

	//设置解码阈值
	vector<float> decodeThres;
	decodeThres.push_back(0.78);
	decodeThres.push_back(0.46);
	decodeThres.push_back(0.14);
	vt.traces.SetDecodeThres(decodeThres);

	// set input video
	string video = argv[1];
	string videoRgb = argv[2];
	VideoCapture cap(video);
	VideoCapture capRgb(videoRgb);
	cap.set(CV_CAP_PROP_POS_FRAMES, startFrame);
	capRgb.set(CV_CAP_PROP_POS_FRAMES, startFrame + 30);

#ifdef OUTPUT_VIDEO
	// 打开录像输出文件
	VideoWriter wr("output.mp4", CV_FOURCC('M', 'J', 'P', 'G'), 25, frame.size());
#endif

	map<int, vector<Rect>> roiRects;
	roiRects[0].push_back(Rect(0, 0, 1200, 1400));
	roiRects[0].push_back(Rect(1220, 0, 1200, 1400));

	Mat frameShow(720, 1280, CV_8UC3);

	// do the tracking
	printf("Start the tracking process, press ESC to quit.\n");
	int cnt = 0;
	for (;; ) {
		cap >> frame;
		capRgb >> frameRgb;
		// 读不到图像则退出
		if (frame.rows == 0 || frame.cols == 0)
			break;

		tm.reset();
		tm.start();

		vt.ViCall("RGB", frameRgb, "IR", frame, vtFlags, roiRects, frameShow, objs, errorMsg);

		tm.stop();
		cout << "frame " << cnt << " time cost:" << tm.getTimeMilli() << "ms" << endl;

		//显示跟踪识别结果
		imshow("endoscope", frameShow);
		if (waitKey(showWait) == 27)
			break;

#ifdef OUTPUT_DATA
		//记录数据
		for (int i = 0; i <MAX_TRACE; ++i) {
			if (vt.traces.trace[i].length != 0) {
				if (!vt.traces.trace[i].ofs.is_open()) {
					string fn = format("./trace%02d.csv", i);
					vt.traces.trace[i].ofs.open(fn);
					vt.traces.trace[i].ofs << "帧号,平均灰度,编码,加权编码,";
					for (size_t j = 0, sz = vt.traces.trace[i].tagInfo.codeLevel.size(); j<sz; ++j) {
						vt.traces.trace[i].ofs << "占空比" << j << ",";
					}
					vt.traces.trace[i].ofs << endl;
				}
				vt.traces.trace[i].ofs << cnt << "," << vt.traces.trace[i].tagInfo.grayLevel << "," << vt.traces.trace[i].code << "," << vt.traces.trace[i].weightedCode << ",";
				for (size_t j = 0, sz = vt.traces.trace[i].tagInfo.codeLevel.size(); j<sz; ++j) {
					vt.traces.trace[i].ofs << vt.traces.trace[i].tagInfo.codeLevel[j] << ",";
				}
				vt.traces.trace[i].ofs << endl;
			}
		}
#endif

#ifdef OUTPUT_VIDEO
		// 写入录像输出文件
		wr << frame;
#endif	

		++cnt;
	}

#ifdef OUTPUT_DATA
	for (int i = 0; i <MAX_TRACE; ++i) {
		if (vt.traces.trace[i].ofs.is_open()) {
			vt.traces.trace[i].ofs.close();
		}
	}
#endif	

#ifdef OUTPUT_VIDEO
	// 关闭录像输出文件
	wr.release();
#endif
}
