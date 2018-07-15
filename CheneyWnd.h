#ifndef CHENEYWND_H_INCLUDE
#define CHENEYWND_H_INCLUDE
#pragma once
	
#include "CheneyThinker.h"

class CheneyWnd
{
public:
	HWND m_hWnd;
	WNDPROC m_lpfnOldWndProc;
	SPECIAL(CheneyWnd)
	BOOL ShowWindow(int);
	BOOL UpdateWindow();
	BOOL DestroyWindow();
	BOOL SubClassWindow(HWND);
	BOOL GetClientRect(LPRECT);
	RECT GetClientRect();
	void CenterWindow();
	virtual void RepaintWindow(CheneyWnd*, const RECT&);
	virtual void AnimateEnter();
	virtual void AnimateOut();
	void FlashWindow(UINT uCount, DWORD dwTimeout);
	static DECLARE_WNDPROC(LRESULT, WndProc)
	static CheneyWnd* FromHandle(HWND);
	virtual BOOL PreCreateWindow(CREATESTRUCT&);
	virtual BOOL CreateEx(DWORD, LPCTSTR, LPCTSTR, DWORD, int, int, int, int, HWND, HMENU, LPVOID lpParam = NULL);
	DECLARE_PROC(WindowProc)
	DECLARE_PROC(DefWinProc)
	DECLARE_MESSAGE_MAP()
};

#endif