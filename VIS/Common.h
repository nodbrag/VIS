#pragma once
#include<direct.h>
#include <string>
class Common
{
public:
	Common(void);
	~Common(void);
	//�����ֽ�char*ת��Ϊ���ֽ�wchar_t* 
    static	wchar_t* AnsiToUnicode( const char* szStr );
	 //�����ֽ�wchar_t*ת��Ϊ���ֽ�char*  
    static  char* UnicodeToAnsi( const wchar_t* szStr );
	static char*  GetCurrentPath();
	static std::string  GetLogPath();
	static std::string getLocalHostIp();
	static std::string GBK_To_UTF8(const std::string &source);
	static std::string UTF8_To_GBK(const std::string &source);
};

