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
	Mat frame;				//ͼ��֡
	Mat frameRgb;			//RGBͼ��֡
	TickMeter tm;	//��ʱ��
	CViTask vt;		//ͼ��������
	vector<int> vtFlags;	//ͼ���������ʶ
	vtFlags.push_back(0);
	map<int, vector<vector<string>>> objs;	//����ʶ������Ϣ
	string errorMsg;	//���ش�����Ϣ


						// �����ò���
	int showWait = 1;
	int startFrame = 0;
	float weight = .01f;
	vt.tp.tagAreaMax = 9000;

	//���ñ������Ȩ��
	vt.traces.SetMinWeight(weight);

	//���ý�����ֵ
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
	// ��¼������ļ�
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
		// ������ͼ�����˳�
		if (frame.rows == 0 || frame.cols == 0)
			break;

		tm.reset();
		tm.start();

		vt.ViCall("RGB", frameRgb, "IR", frame, vtFlags, roiRects, frameShow, objs, errorMsg);

		tm.stop();
		cout << "frame " << cnt << " time cost:" << tm.getTimeMilli() << "ms" << endl;

		//��ʾ����ʶ����
		imshow("endoscope", frameShow);
		if (waitKey(showWait) == 27)
			break;

#ifdef OUTPUT_DATA
		//��¼����
		for (int i = 0; i <MAX_TRACE; ++i) {
			if (vt.traces.trace[i].length != 0) {
				if (!vt.traces.trace[i].ofs.is_open()) {
					string fn = format("./trace%02d.csv", i);
					vt.traces.trace[i].ofs.open(fn);
					vt.traces.trace[i].ofs << "֡��,ƽ���Ҷ�,����,��Ȩ����,";
					for (size_t j = 0, sz = vt.traces.trace[i].tagInfo.codeLevel.size(); j<sz; ++j) {
						vt.traces.trace[i].ofs << "ռ�ձ�" << j << ",";
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
		// д��¼������ļ�
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
	// �ر�¼������ļ�
	wr.release();
#endif
}
