#include "CheneyButtonEx.h"

SPECIAL_HANDLER(CheneyButtonEx, 
{
	m_bIsHover = FALSE;
	m_bIsDown = FALSE;
}, {})

void CheneyButtonEx::SetImage(UINT uID)
{
	if(!m_imgBtn.IsNull())
	{
		m_imgBtn.Destroy();
	}
	m_imgBtn.LoadFromResource((HINSTANCE)::GetModuleHandle(NULL), uID);
	InvalidateRect(m_hWnd, NULL, TRUE);
	
	HRGN hRgn = CreateRectRgn(0, 0, 0, 0);
	int nWidth = m_imgBtn.GetWidth()/4;
	int nHeight = m_imgBtn.GetHeight();
	COLORREF clrMask = m_imgBtn.GetPixel(0, 0);
	for(int i=0; i<nWidth; i++)
	{
		for(int j=0; j<nHeight; j++)
		{
			COLORREF clrPixel = m_imgBtn.GetPixel(i, j);
			if(clrMask!=clrPixel)
			{
				HRGN hRgnTemp = CreateRectRgn(i, j, i+1, j+1);
				::CombineRgn(hRgn, hRgn, hRgnTemp, RGN_OR);
				DeleteObject((HGDIOBJ)hRgnTemp);
			}
		}
	}
	SetWindowRgn(m_hWnd, hRgn, TRUE);
	DeleteObject((HGDIOBJ)hRgn);
}

MESSAGE_MAP_HANDLER(CheneyButtonEx, Paint, {
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(m_hWnd, &ps);
	assert(hDC);
	{
		RECT rc;
		GetClientRect(&rc);
		DRAWITEMSTRUCT dis;
		dis.hDC = hDC;
		dis.CtlType = ODT_BUTTON;
		dis.hwndItem = m_hWnd;
		dis.rcItem = rc;
		DrawItem(&dis);
	}
	EndPaint(m_hWnd, &ps);
	return TRUE;
})

void CheneyButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	HDC hDC = lpDrawItemStruct->hDC;
	ThinkerRect rc = lpDrawItemStruct->rcItem;
	if(!m_imgBtn.IsNull())
	{
		if(!m_bIsHover)
		{
			m_imgBtn.Draw(hDC, rc, ThinkerRect(0, 0, m_imgBtn.GetWidth() >> 2, m_imgBtn.GetHeight()));
		}
		else
		{
			if(m_bIsDown)
			{
				m_imgBtn.Draw(hDC, rc, ThinkerRect(m_imgBtn.GetWidth() / 4 * 2, 0, m_imgBtn.GetWidth() / 4 * 3, m_imgBtn.GetHeight()));
			}
			else
			{
				m_imgBtn.Draw(hDC, rc, ThinkerRect(m_imgBtn.GetWidth() >> 2, 0, m_imgBtn.GetWidth() / 4 * 2, m_imgBtn.GetHeight()));
			}
		}
	}
}

MESSAGE_MAP_HANDLER(CheneyButtonEx, Create, {
	return CheneyButton::OnCreate(wParam, lParam);
})

MESSAGE_MAP_HANDLER(CheneyButtonEx, MouseMove, {
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE | TME_HOVER;
	tme.hwndTrack = m_hWnd;
	tme.dwHoverTime = HOVER_DEFAULT;
	TrackMouseEvent(&tme);
	return CheneyButton::OnMouseMove(wParam, lParam);
})

LRESULT CheneyButtonEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == WM_MOUSEHOVER)
	{
		return OnMouseHover(wParam, lParam);
	}
	if(message == WM_MOUSELEAVE)
	{
		return OnMouseLeave(wParam, lParam);
	}
	return CheneyButton::WindowProc(message, wParam, lParam);
}

MESSAGE_MAP_HANDLER(CheneyButtonEx, MouseHover, {
	if(!m_bIsHover)
	{
		m_bIsHover = TRUE;
		InvalidateRect(m_hWnd, NULL, TRUE);
	}
	return TRUE;
})

MESSAGE_MAP_HANDLER(CheneyButtonEx, MouseLeave, {
	if(m_bIsHover)
	{
		m_bIsHover = FALSE;
		InvalidateRect(m_hWnd, NULL, TRUE);
	}
	return TRUE;
})

MESSAGE_MAP_HANDLER(CheneyButtonEx, LButtonDown, {
	if(!m_bIsDown)
	{
		m_bIsDown = TRUE;
		InvalidateRect(m_hWnd, NULL, TRUE);
	}
	return CheneyButton::OnLButtonDown(wParam, lParam);
})

MESSAGE_MAP_HANDLER(CheneyButtonEx, LButtonUp, {
	if(m_bIsDown)
	{
		m_bIsDown = FALSE;
		InvalidateRect(m_hWnd, NULL, TRUE);
	}
	return CheneyButton::OnLButtonUp(wParam, lParam);
})