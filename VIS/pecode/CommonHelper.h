
#include <string>
#include <wtypes.h>

#pragma once
class CommonHelper
{
public:
	CommonHelper();
	~CommonHelper();
	//CPU���к�
	bool GetCpuByCmd(char *lpszCpu, int len/*=128*/);
	void Wchar_tToString(std::string& szDst, wchar_t *wchar);
};

