#pragma once
#include "ThreadArguments.h";

const long EchoBufferSize = 1024*900;

class EchoService
{
public:
	EchoService(void);
	~EchoService(void);
	void HandleRequest(THREAD_ARGUMENTS *);
	void StartNotifyThread(THREAD_ARGUMENTS * thread_arguments,std::string cammadType);
private:
	int echoBufferSize;
};

