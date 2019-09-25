#pragma once
#include "ThreadArguments.h";
class VINotify
{
public:
	VINotify(void);
	~VINotify(void);
	static void ThreadRunnableHandleRequest(THREAD_ARGUMENTS * thread_arguments);
};

