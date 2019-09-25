#include "Common.h"
#include <Windows.h>

Common::Common(void)
{
}


Common::~Common(void)
{
}
//将单字节char*转化为宽字节wchar_t*  
wchar_t* Common::AnsiToUnicode( const char* szStr )  
{  
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );  
	if (nLen == 0)  
	{  
		return NULL;  
	}  
	wchar_t* pResult = new wchar_t[nLen];  
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen );  
	return pResult;  
}  

//将宽字节wchar_t*转化为单字节char*  
 char* Common::UnicodeToAnsi( const wchar_t* szStr )  
{  
	int nLen = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );  
	if (nLen == 0)  
	{  
		return NULL;  
	}  
	char* pResult = new char[nLen];  
	WideCharToMultiByte( CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL );  
	return pResult;  
}
 //路径
 char* Common::GetCurrentPath() {
  
	// char currentPath[MAX_PATH];
	// getcwd(currentPath, MAX_PATH);

	 char currentPath[MAX_PATH] = {0};
     int n= GetModuleFileNameA(NULL, currentPath, MAX_PATH);
	 currentPath[strrchr(currentPath, '\\') - currentPath + 1] = 0;//将最后一个"\\"后的字符置为0  

	 return currentPath; 
 }
 std::string Common::GetLogPath() {

	 std::string path(GetCurrentPath());
	 return  path+ "Log\\";
 }


 std::string  Common::getLocalHostIp()
 {
	 WORD wVersionRequested = MAKEWORD(2, 2);

	 WSADATA wsaData;
	 if (WSAStartup(wVersionRequested, &wsaData) != 0)
		 return "";

	 char local[255] = { 0 };
	 gethostname(local, sizeof(local));
	 hostent* ph = gethostbyname(local);
	 if (ph == NULL)
		 return "";

	 in_addr *pAddr = (in_addr *)*ph->h_addr_list;
	 std::string localIP;
	 for (int i = 0; i < (strlen((char*)*ph->h_addr_list) - strlen(ph->h_name)) / 4 && pAddr; i++) {
		 std::string addr;
		 addr.assign(inet_ntoa(pAddr[i]));
		 std::string firstaddr = addr.substr(0, 3);
		 if (firstaddr.compare("169") == 0) {   //获取169段的ip
			 localIP = addr;
			 break;
		 }
	 }
	 WSACleanup();
	 return localIP;
 
 }

 std::string Common::GBK_To_UTF8(const std::string &source)
 {
	 enum { GB2312 = 936 };

	 unsigned long len = ::MultiByteToWideChar(GB2312, NULL, source.c_str(), -1, NULL, NULL);
	 if (len == 0)
		 return std::string();
	 wchar_t *wide_char_buffer = new wchar_t[len];
	 ::MultiByteToWideChar(GB2312, NULL, source.c_str(), -1, wide_char_buffer, len);

	 len = ::WideCharToMultiByte(CP_UTF8, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
	 if (len == 0)
	 {
		 delete[] wide_char_buffer;
		 return std::string();
	 }
	 char *multi_byte_buffer = new char[len];
	 ::WideCharToMultiByte(CP_UTF8, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);

	 std::string dest(multi_byte_buffer);
	 delete[] wide_char_buffer;
	 delete[] multi_byte_buffer;
	 return dest;
 }

 std::string Common::UTF8_To_GBK(const std::string &source)
 {
	 enum { GB2312 = 936 };

	 unsigned long len = ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL);
	 if (len == 0)
		 return std::string();
	 wchar_t *wide_char_buffer = new wchar_t[len];
	 ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, wide_char_buffer, len);

	 len = ::WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
	 if (len == 0)
	 {
		 delete[] wide_char_buffer;
		 return std::string();
	 }
	 char *multi_byte_buffer = new char[len];
	 ::WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);

	 std::string dest(multi_byte_buffer);
	 delete[] wide_char_buffer;
	 delete[] multi_byte_buffer;
	 return dest;
 }
 
