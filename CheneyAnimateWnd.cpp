#include "CheneyAnimateWnd.h"

CheneyAnimateWnd::CheneyAnimateWnd(HWND hwnd)
{
	m_hWnd = hwnd;
	m_iAnimateType = GetRandomNumber();
}

CheneyAnimateWnd::~CheneyAnimateWnd()
{
}

void CheneyAnimateWnd::SetWindowHwnd(HWND hwnd)
{
	m_hWnd = hwnd;
}

HWND CheneyAnimateWnd::GetWindowHwnd()
{
	return m_hWnd;
}

BOOL CheneyAnimateWnd::AnimateWindow(DWORD dwTime, BOOL bShow, BOOL bSlide)
{
	DWORD dwFlags;
	dwFlags = bShow ? AW_ACTIVATE : AW_HIDE;
	dwFlags |= ( bSlide ? AW_SLIDE : AW_BLEND);
	if(m_iAnimateType == 0)
		dwFlags |= AW_HOR_POSITIVE;
	else if(m_iAnimateType == 1)
		dwFlags |= AW_VER_POSITIVE;
	else
		dwFlags |= AW_CENTER;
	return ::AnimateWindow(m_hWnd, dwTime, dwFlags);
}

int  CheneyAnimateWnd::GetRandomNumber()
{
	srand((UINT)time(NULL));
	return rand() % 3;
}