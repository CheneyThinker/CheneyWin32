#include "CheneyWnd.h"

SPECIAL_HANDLER(CheneyWnd, {
	m_hWnd = NULL;
	m_lpfnOldWndProc = NULL;
}, {})

BOOL CheneyWnd::SubClassWindow(HWND hwnd)
{
	assert(hwnd);
	if(m_hWnd == hwnd)
		return TRUE;
	m_lpfnOldWndProc = (WNDPROC) GetWindowLong(hwnd, GWL_WNDPROC);
	if(m_lpfnOldWndProc != CheneyWnd::WndProc)
	{
		m_hWnd = hwnd;
		SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
		SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)CheneyWnd::WndProc);
		return TRUE;
	}
	return FALSE;
}

CheneyWnd* CheneyWnd::FromHandle(HWND hwnd)
{
	assert(hwnd);
	CheneyWnd* pWnd = (CheneyWnd*) GetWindowLong(hwnd, GWL_USERDATA);
	return pWnd;
}

BOOL CheneyWnd::GetClientRect(LPRECT lpRect)
{
	assert(m_hWnd);
	return ::GetClientRect(m_hWnd, lpRect);
}

RECT CheneyWnd::GetClientRect()
{
	RECT rect;
	GetClientRect(&rect);
	return rect;
}

void CheneyWnd::CenterWindow()
{
	RECT rc;
	int iWidth, iHeight, iScreenWidth, iScreenHeight;
	iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(m_hWnd, &rc);
	iWidth = rc.right - rc.left;
	iHeight = rc.bottom - rc.top;
	MoveWindow(m_hWnd, (iScreenWidth - iWidth) >> 1, (iScreenHeight - iHeight) >> 1, iWidth, iHeight, FALSE);
}

void CheneyWnd::RepaintWindow(CheneyWnd* parent, const RECT& rect)
{
	if(NULL != parent->m_hWnd)
		MoveWindow(parent->m_hWnd, rect.left, rect.top, rect.right, rect.bottom, TRUE);
}

BOOL CheneyWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	BOOL flag = GetClassInfoEx(cs.hInstance, cs.lpszClass, &wcex);
	if(flag)
		return TRUE;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = cs.hInstance;
	wcex.hIcon = (HICON)::LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON));
	wcex.hIconSm = (HICON)::LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON));
	wcex.hbrBackground = (HBRUSH)::GetStockObject(NULL_BRUSH);//(HBRUSH)::GetStockObject(WHITE_BRUSH);
	wcex.hCursor = (HCURSOR)::LoadCursor((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR1));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName =  cs.lpszClass;
	flag = ::RegisterClassEx(&wcex);
	if(!flag)
		return FALSE;
	return TRUE;
}

BOOL CheneyWnd::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
{
	HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
	assert(hInstance);
	CREATESTRUCT cs;
	cs.cx = nWidth;
	cs.cy = nHeight;
	cs.dwExStyle = dwExStyle;
	cs.hInstance = hInstance;
	cs.hMenu = nIDorHMenu;
	cs.hwndParent = hWndParent;
	cs.lpCreateParams = lpParam;
	cs.lpszClass = lpszClassName;
	cs.lpszName = lpszWindowName;
	cs.style = dwStyle;
	cs.x = x;
	cs.y = y;
	BOOL flag = PreCreateWindow(cs);
	if(!flag)
	{
		MessageBox(NULL, _T("Register Window Failed!"), _T("Register Window"), MB_OK);
		return FALSE;
	}
	HWND hWnd = CreateWindowEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y, 
		cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, this);
	if(NULL == hWnd)
	{
		return FALSE;
	}
	m_hWnd = hWnd;
	SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
	m_lpfnOldWndProc = (WNDPROC)GetWindowLong(m_hWnd, GWL_WNDPROC);
	if(m_lpfnOldWndProc != CheneyWnd::WndProc)
	{
		SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)CheneyWnd::WndProc);
		WindowProc(WM_CREATE, 0, 0);
		WindowProc(WM_NCCREATE, 0, 0);
	}
	return TRUE;
}

BOOL CheneyWnd::ShowWindow(int nCmdShow)
{
	assert(m_hWnd);
	return ::ShowWindow(m_hWnd, nCmdShow);
}

BOOL CheneyWnd::UpdateWindow()
{
	assert(m_hWnd);
	return ::UpdateWindow(m_hWnd);
}

BOOL CheneyWnd::DestroyWindow()
{
	assert(m_hWnd);
	return ::DestroyWindow(m_hWnd);
}

void CheneyWnd::AnimateEnter()
{
	AnimateWindow(m_hWnd, 1000, AW_ACTIVATE | AW_BLEND);
	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow();
}

void CheneyWnd::AnimateOut()
{
	AnimateWindow(m_hWnd, 1000, AW_HIDE | AW_BLEND);
}

void CheneyWnd::FlashWindow(UINT uCount, DWORD dwTimeout)
{
	FLASHWINFO info = {0};
	info.cbSize = sizeof(FLASHWINFO);
	info.hwnd = m_hWnd;
	info.dwFlags = FLASHW_TRAY;
	info.uCount = uCount;
	info.dwTimeout = dwTimeout;
	::FlashWindowEx(&info);
}

LRESULT CheneyWnd::DefWinProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(m_lpfnOldWndProc == CheneyWnd::WndProc)
	{
		return ::DefWindowProc(m_hWnd, message, wParam, lParam);
	}
	return CallWindowProc(m_lpfnOldWndProc, m_hWnd, message, wParam, lParam);
}

LRESULT CALLBACK CheneyWnd::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == WM_CREATE || message == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
		assert(lpcs);
		if(lpcs)
		{
			CheneyWnd* pWnd = (CheneyWnd*)lpcs->lpCreateParams;
			assert(pWnd);
			if(pWnd)
			{
				pWnd->m_hWnd = hwnd;
				pWnd->m_lpfnOldWndProc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
				return pWnd->WindowProc(message, wParam, lParam);
			}
		}
	}
	CheneyWnd* pWnd = (CheneyWnd*)GetWindowLong(hwnd, GWL_USERDATA);
	if(pWnd)
	{
		return pWnd->WindowProc(message, wParam, lParam);
	}
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CheneyWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		MESSAGE_HANDLER(AFTER, WINPROC)
	}
	return DefWinProc(message, wParam, lParam);
}

MESSAGE_HANDLER(BEFORE, DEFAULT)