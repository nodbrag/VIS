#pragma once
#include<direct.h>
#include <string>
class Common
{
public:
	Common(void);
	~Common(void);
	//将单字节char*转化为宽字节wchar_t* 
    static	wchar_t* AnsiToUnicode( const char* szStr );
	 //将宽字节wchar_t*转化为单字节char*  
    static  char* UnicodeToAnsi( const wchar_t* szStr );
	static char*  GetCurrentPath();
	static std::string  GetLogPath();
	static std::string getLocalHostIp();
	static std::string GBK_To_UTF8(const std::string &source);
	static std::string UTF8_To_GBK(const std::string &source);
};

