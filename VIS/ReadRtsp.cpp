#include "ReadRtsp.h"
#include "date.h"

std::time_t ReadRtsp::getTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	std::time_t timestamp = tmp.count();
	//std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
	return timestamp;
}

ReadRtsp::ReadRtsp()
{
}

ReadRtsp::~ReadRtsp()
{
	TerminateThread(this->m_handle, 0);


}

void ReadRtsp::setDecoderType(int decoderType)
{
	if (this->decoderType == 2)
		pCodec = avcodec_find_decoder_by_name("h264_cuvid");
}

long ReadRtsp::VIInit(std::string &error, std::string ip, std::string url)
{
	filePath = url;
	this->ip = ip;
	av_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();

	//![0]
	// 默认为tcp连接 
	AVDictionary* options = NULL;
	av_dict_set(&options, "rtsp_transport", "tcp", 0);
	if (avformat_open_input(&pFormatCtx, filePath.c_str(), NULL, &options) != 0)
	{
		error = "Couldn't open input stream.\n";
		return -1;
	}

	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		error = "Couldn't find stream information.\n";
		return -1;
	}

	videoindex = -1;
	for (i = 0; i < pFormatCtx->nb_streams; ++i)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoindex = i;
			break;
		}
	}

	if (videoindex == -1)
	{
		error = "Didn't find a video stream.\n";
		return -1;
	}

	this->now_time_stamp = getTimeStamp();

	return this->now_time_stamp;
}

long ReadRtsp::VIVideoDecoder(int decoderType, long lRealHandle, std::string &error, VodieCallBack callback)
{

	pCodecCtx = pFormatCtx->streams[videoindex]->codec;

	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	// GPU or CPU
	setDecoderType(decoderType);

	if (pCodec == NULL)
	{
		error = "Codec not found.\n";
		return -1;
	}
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		error = "Could not open codec.\n";
		return -1;
	}

	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();
	out_buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1));
	av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, out_buffer,
		AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);

	
	//Output Info-----------------------------
	//printf("--------------- File Information ----------------\n");
	//av_dump_format(pFormatCtx, 0, filePath.c_str(), 0);
	//printf("-------------------------------------------------\n");
	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);



	frameSize = avpicture_get_size(AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);

	video_frameRGB = av_frame_alloc();

	pSwsCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_BGR24,
		SWS_BICUBIC, NULL, NULL, NULL);
	outMat = cv::Mat::zeros(pCodecCtx->height, pCodecCtx->width, CV_8UC3);
	if (pFormatCtx->streams[videoindex]->avg_frame_rate.den != 0) {
		frameRate = (int)pFormatCtx->streams[videoindex]->avg_frame_rate.num / pFormatCtx->streams[videoindex]->avg_frame_rate.den;
	}
	else {
		frameRate = 25;
	}

	this->lRealHandle = lRealHandle;
	this->callBackFun = callback;
	m_handle = CreateThread(NULL, 0, start, this, 0, NULL);

	return lRealHandle;
}

DWORD WINAPI start(LPVOID pM)
{
	ReadRtsp* now = (ReadRtsp *)pM;

	uint8_t *outBuff = NULL;
	outBuff = (uint8_t*)av_malloc(now->frameSize);
	avpicture_fill((AVPicture*)now->video_frameRGB, outBuff, AV_PIX_FMT_BGR24, now->pCodecCtx->width, now->pCodecCtx->height);
	char tmp[20];
	char *cp = tmp;
	// change to opencv2 mat 
	int count = 0;
	long persecond = 0;
	while (1)
	{
		ec::Time n;
		long second = n.getUTCFullSeconds();
		
		now->packet = (AVPacket *)av_malloc(sizeof(AVPacket));
		if (av_read_frame(now->pFormatCtx, now->packet) >= 0) 
		{
			if (now->packet->stream_index == now->videoindex)
			{

				now->ret = avcodec_decode_video2(now->pCodecCtx, now->pFrame, &now->got_picture, now->packet);
				if (now->ret < 0)
				{
					now->error = "Decode Error.\n";
					//return -1;
				}
				//![1] 判断丢包
				if (now->got_picture)
				{

					sws_scale(now->pSwsCtx, now->pFrame->data,
						now->pFrame->linesize, 0, now->pCodecCtx->height,
						now->video_frameRGB->data, now->video_frameRGB->linesize);

					memcpy(now->outMat.data, outBuff, now->frameSize);

					//imshow("test", now->outMat);
					count++;
					
					now->callBackFun(now->lRealHandle, now->outMat);
					//av_free(outBuff);
				}
				else
				{
					now->error = "Packet loss.\n";
					//return -1;
				}
				av_free_packet(now->packet);
			}
		}
		
		if (persecond != second) {
			persecond = second;
			sprintf(cp, "%s:%d", now->ip, count);
			printf_s("%s\r\n",cp);
			count = 0;
		}
		Sleep(2);
	}

	av_frame_free(&now->pFrameYUV);
	av_frame_free(&now->pFrame);
	avcodec_close(now->pCodecCtx);
	avformat_close_input(&now->pFormatCtx);
	return 0;
}