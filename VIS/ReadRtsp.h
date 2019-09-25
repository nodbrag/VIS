#pragma once
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <iostream>
#include <thread>

#define __STDC_CONSTANT_MACROS

extern "C"
{
#include <libavcodec\avcodec.h>

#include <libavformat\avformat.h>
#include <libswscale\swscale.h>
#include <libavutil\imgutils.h>
};

#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

#include <chrono>

#pragma warning(disable:4996)

using namespace cv;


//DWORD WINAPI start(LPVOID pM);
typedef void (*VodieCallBack) (long lRealHandle, cv::Mat mat);

class ReadRtsp
{
public:
	AVFormatContext   *pFormatCtx;
	int				  i, videoindex;
	int frameRate;
	AVCodecContext	  *pCodecCtx;
	AVCodec			  *pCodec;
	AVFrame			  *pFrame, *pFrameYUV;
	unsigned char     *out_buffer;
	AVPacket		  *packet;
	int				  y_size;
	int				  ret, got_picture;
	struct SwsContext *img_convert_ctx;
	uint8_t           *outBuff = NULL;
	struct SwsContext *pSwsCtx;
	AVFrame           *video_frameRGB = NULL;
	int               frameSize;

	HANDLE             m_handle;
	DWORD			   thread_id;
	Mat                outMat;

	long               lRealHandle;
	std::string        error;
	VodieCallBack      callBackFun;
	std::time_t        now_time_stamp;
	std::string ip;


	std::time_t getTimeStamp();

	ReadRtsp::ReadRtsp();

	long VIInit(std::string &error, std::string ip, std::string url);

	void setDecoderType(int decoderType);


	long VIVideoDecoder(int decoderType, long lRealHandle, std::string &error, VodieCallBack callBackFun);

	friend DWORD WINAPI start(LPVOID pM);

	~ReadRtsp();


	std::string filePath;

	int decoderType;
};
