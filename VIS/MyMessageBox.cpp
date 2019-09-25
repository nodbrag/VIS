#include "MyMessageBox.h"



MyMessageBox::MyMessageBox()
{
	
}


MyMessageBox::~MyMessageBox()
{
}
int MyMessageBox::showDialog(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds) {

	HMODULE hUser32 = LoadLibrary(_T("user32.dll"));
	int iRet = 0;
	if (hUser32)
	{
		
		UINT uiFlags = MB_OK | MB_SETFOREGROUND | MB_SYSTEMMODAL | MB_ICONINFORMATION;

		iRet = MessageBoxTimeoutA(hWnd, lpText,
			lpCaption, uType, wLanguageId, dwMilliseconds);

		FreeLibrary(hUser32);
	}
	return iRet;
}

int MessageBoxTimeoutA(HWND hWnd, LPCSTR lpText,
	LPCSTR lpCaption, UINT uType, WORD wLanguageId,
	DWORD dwMilliseconds)
{
	static MSGBOXAAPI MsgBoxTOA = NULL;

	if (!MsgBoxTOA)
	{
		HMODULE hUser32 = GetModuleHandle(_T("user32.dll"));
		if (hUser32)
		{
			MsgBoxTOA = (MSGBOXAAPI)GetProcAddress(hUser32,
				"MessageBoxTimeoutA");
			//fall through to 'if (MsgBoxTOA)...'
		}
		else
		{
			//stuff happened, add code to handle it here 
			//(possibly just call MessageBox())
			return 0;
		}
	}
	if (MsgBoxTOA)
	{
		return MsgBoxTOA(hWnd, lpText, lpCaption,
			uType, wLanguageId, dwMilliseconds);
	}

	return 0;
}

