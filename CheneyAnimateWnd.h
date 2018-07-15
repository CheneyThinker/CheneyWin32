#ifndef CHENEYANIMATEWND_H_INCLUDE
#define CHENEYANIMATEWND_H_INCLUDE
#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <time.h>

class CheneyAnimateWnd
{
public:
	CheneyAnimateWnd(HWND hwnd = NULL);
	virtual ~CheneyAnimateWnd();
	void SetWindowHwnd(HWND hwnd);
	HWND GetWindowHwnd();
	BOOL AnimateWindow(DWORD dwTime = 400, BOOL bShow = TRUE, BOOL bSlide = TRUE);
	int GetRandomNumber();
	int m_iAnimateType;
	HWND m_hWnd;
};

#endif