#pragma once
#include <Windows.h>
#include <tchar.h>
typedef int(__stdcall *MSGBOXAAPI)(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
int MessageBoxTimeoutA(IN HWND hWnd, IN LPCSTR lpText,
	IN LPCSTR lpCaption, IN UINT uType,
	IN WORD wLanguageId, IN DWORD dwMilliseconds);

#define MB_TIMEDOUT 32000

#define MessageBoxTimeout MessageBoxTimeoutA

class MyMessageBox
{

public:
	MyMessageBox();
	~MyMessageBox();
	int showDialog(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds);
};

