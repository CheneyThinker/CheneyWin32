#include "CheneyUtils.h"

SPECIAL_HANDLER(CheneyUtils, {}, {})

WMCOMMAND CheneyUtils::GetWMCommand(WPARAM wParam, LPARAM lParam)
{
	WMCOMMAND wm;
	wm.wNotifyCode = HIWORD(wParam);
	wm.wID = LOWORD(wParam);
	wm.hwndCtrl = (HWND) lParam;
	return wm;
}

BOOL CheneyUtils::TraceLog(TCHAR* lpszFormat, ...)
{
	assert(lpszFormat);
	if(lpszFormat == NULL)
		return FALSE;
	va_list args;
	TCHAR temp[512] = {0};
	va_start(args, lpszFormat);
	_vsnprintf_s(temp, sizeof(temp), ARRAYSIZE(temp), lpszFormat, args);
	va_end(args);
	SYSTEMTIME st;
	::GetLocalTime(&st);
	TCHAR trace[1024] = {0};
	_sntprintf_s(trace, ARRAYSIZE(trace), TEXT("[%02u:%02u:%02u: %02u:%02u:%02u] %s\r\n"),
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, temp);
	FILE* fp = NULL;
	errno_t err;
	err = fopen_s(&fp, TEXT("CheneyThinkerLog.txt"), TEXT("ab"));
	if(err != 0)
		return FALSE;
	fwrite(trace, sizeof(TCHAR), _tcslen(trace), fp);
	fclose(fp);
	fp = NULL;
	return TRUE;
}