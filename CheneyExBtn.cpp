#include "CheneyExBtn.h"

SPECIAL_HANDLER(CheneyExBtn, {
	m_BoundryPen = CreatePen(PS_INSIDEFRAME | PS_SOLID, 1,RGB(200,190,230));
	m_InsideBoundryPenLeft = CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(200,190,230)); 
	m_InsideBoundryPenRight = CreatePen(PS_INSIDEFRAME | PS_SOLID, 3,RGB(200,190,230));
	m_InsideBoundryPenTop = CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(200,190,230));
	m_InsideBoundryPenBottom = CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(200,190,230));

	m_FillActive = CreateSolidBrush(RGB(236,233,216));
	m_FillInactive = CreateSolidBrush(RGB(235, 234, 216));
	
	m_InsideBoundryPenLeftSel = CreatePen(PS_INSIDEFRAME | PS_SOLID, 2,RGB(220,210,250)); 
	m_InsideBoundryPenTopSel =CreatePen(PS_INSIDEFRAME | PS_SOLID, 2,RGB(210,200,240));
	m_InsideBoundryPenRightSel = CreatePen(PS_INSIDEFRAME | PS_SOLID,3, RGB(220,210,240));
	m_InsideBoundryPenBottomSel = CreatePen(PS_INSIDEFRAME | PS_SOLID,2,RGB(220,210,250));
	
	m_bCLicking = m_bOver = m_bSelected = m_bTracking = m_bFocus = FALSE;
	id = 1;
}, {
	::DeleteObject((HGDIOBJ)m_BoundryPen);
	::DeleteObject((HGDIOBJ)m_InsideBoundryPenLeft);
	::DeleteObject((HGDIOBJ)m_InsideBoundryPenRight);
	::DeleteObject((HGDIOBJ)m_InsideBoundryPenTop);
	::DeleteObject((HGDIOBJ)m_InsideBoundryPenBottom);
	::DeleteObject((HGDIOBJ)m_FillActive);
	::DeleteObject((HGDIOBJ)m_FillInactive);
	::DeleteObject((HGDIOBJ)m_InsideBoundryPenLeftSel);
	::DeleteObject((HGDIOBJ)m_InsideBoundryPenTopSel);
	::DeleteObject((HGDIOBJ)m_InsideBoundryPenRightSel);
	::DeleteObject((HGDIOBJ)m_InsideBoundryPenBottomSel);
})
	
void CheneyExBtn::PreSubclassWindow()
{
	SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) | BS_OWNERDRAW);
	HRGN rgn;
	ThinkerRect rc;
	GetClientRect(&rc);
	rgn = CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 5, 5);
	SetWindowRgn(m_hWnd, rgn, TRUE);
	::DeleteObject((HGDIOBJ)rgn);
}

void CheneyExBtn::DoGradientFill(HDC pDC, ThinkerRect* rect)
{
	HBRUSH brBk[64];
	int nWidth = rect->Width();
	int nHeight = rect->Height();
	ThinkerRect rct;
	for (int i = 0; i < 64; i ++)
	{
		if (m_bOver)
		{
			if (m_bFocus)
				brBk[i] = CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 3)));
			else
				brBk[i] = CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 5)));
		}
		else
		{
			if (m_bFocus)
				brBk[i] = CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 4)));
			else
				brBk[i] = CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 5)));
		}
	}
	for (int i = rect->top; i <= nHeight + 2; i ++)
	{
		rct.SetRect(rect->left, i, nWidth + 2, i + 1);
		FillRect(pDC, &rct, brBk[((i * 63) / nHeight)]);
	}
	for (int i = 0; i < 64; i ++)
		::DeleteObject((HGDIOBJ)brBk[i]);
}

void CheneyExBtn::DrawInsideBorder(HDC pDC, ThinkerRect* rect)
{
	HPEN *pLeft, *pRight, *pTop, *pBottom;
	if (m_bSelected && !m_bOver)
	{
		pLeft = &m_InsideBoundryPenLeftSel;
		pRight = &m_InsideBoundryPenRightSel;
		pTop = &m_InsideBoundryPenTopSel;
		pBottom = &m_InsideBoundryPenBottomSel;
	}
	else
	{
		pLeft = &m_InsideBoundryPenLeft;
		pRight = &m_InsideBoundryPenRight;
		pTop = &m_InsideBoundryPenTop;
		pBottom = &m_InsideBoundryPenBottom;
	}
	ThinkerPoint oldPoint = MoveToEx(pDC, rect->left, rect->bottom, NULL);
	HPEN pOldPen = (HPEN)::SelectObject(pDC, (HGDIOBJ)pLeft);
	LineTo(pDC, rect->left, rect->top);

	pOldPen = (HPEN)::SelectObject(pDC, (HGDIOBJ)pRight);
	MoveToEx(pDC, rect->right , rect->bottom, NULL);
	LineTo(pDC, rect->right , rect->top);

	pOldPen = (HPEN)::SelectObject(pDC, (HGDIOBJ)pTop);
	MoveToEx(pDC, rect->left-1 , rect->top, NULL);
	LineTo(pDC, rect->right , rect->top);

	pOldPen = (HPEN)::SelectObject(pDC, (HGDIOBJ)pBottom);
	MoveToEx(pDC, rect->left, rect->bottom, NULL);
	LineTo(pDC, rect->right , rect->bottom);
	::SelectObject(pDC, (HGDIOBJ)pOldPen);

	MoveToEx(pDC, oldPoint.x, oldPoint.y, NULL);
	if (m_bSelected && !m_bOver)
		DrawFocusRect(pDC, rect);
}

void CheneyExBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ThinkerRect rect = lpDrawItemStruct->rcItem;
	HDC pDC = lpDrawItemStruct->hDC;
	UINT state = lpDrawItemStruct->itemState;
	POINT pt;
	TCHAR strText[MAX_PATH + 1];
	::GetWindowText(m_hWnd, strText, MAX_PATH);
	pt.x = pt.y = 5;
	HPEN hOldPen = (HPEN)::SelectObject(pDC, (HGDIOBJ) m_BoundryPen);
	RoundRect(pDC, rect.left, rect.top, rect.right, rect.bottom, pt.x, pt.y);
	if (state & ODS_FOCUS)
	{
		m_bFocus = TRUE;
		m_bSelected = TRUE;
	}
	else
	{
		m_bFocus = FALSE;
		m_bSelected = FALSE;
	}
	if (state & ODS_SELECTED || state & ODS_DEFAULT)
	{
		m_bFocus = TRUE;
	}
	::SelectObject(pDC, (HGDIOBJ)hOldPen);
	rect.DeflateRect( ThinkerSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
	//HBRUSH pOldBrush;
	if(m_bOver)
	{
		//pOldBrush = (HBRUSH)::SelectObject(pDC, (HGDIOBJ)m_FillActive);
		DoGradientFill(pDC, &rect);
	}
	else
	{
		//pOldBrush = (HBRUSH)::SelectObject(pDC, (HGDIOBJ)m_FillInactive);
		DoGradientFill(pDC, &rect);
	}
	if(!m_bCLicking)
	{
		if (m_bOver || m_bSelected)
			DrawInsideBorder(pDC, &rect);
	}
	m_bCLicking = FALSE;
	//::SelectObject(pDC, (HGDIOBJ)pOldBrush);
	/*if (strText != NULL)
	{
		HFONT hFont = GetFont();
		CFont* hOldFont = pDC->SelectObject(hFont);
		CSize szExtent = pDC->GetTextExtent(strText, lstrlen(strText));
		CPoint pt( rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2);
		if (state & ODS_SELECTED) 
			pt.Offset(1, 1);
		int nMode = pDC->SetBkMode(TRANSPARENT);
		if (state & ODS_DISABLED)
			pDC->DrawState(pt, szExtent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		else
			pDC->DrawState(pt, szExtent, strText, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);
		pDC->SelectObject(hOldFont);
		pDC->SetBkMode(nMode);
	}
	CBitmap* pBitmap = new CBitmap;
	CBitmap* pOldBitmap;
	CDC* pDisplayMemDC=new CDC;
	pDisplayMemDC->CreateCompatibleDC(pDC);
	CRect rtButtons;
	GetClientRect(rtButtons);
	rtButtons.top+=3;
	rtButtons.left+=3;
	rtButtons.bottom-=3;
	pBitmap->LoadBitmap(id);
	pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
	pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
	pDisplayMemDC->SelectObject(pOldBitmap);
	pBitmap->DeleteObject();
	pDC->RestoreDC(nSaveDC);*/
}

void CheneyExBtn::LoadImg(UINT ID)
{
	id = ID;
}
MESSAGE_MAP_HANDLER(CheneyExBtn, LButtonDown, {
	m_bCLicking = TRUE;
	return CheneyButton::OnLButtonDown(wParam, lParam);
})
MESSAGE_MAP_HANDLER(CheneyExBtn, EraseBkgnd, {
	return TRUE;
})
MESSAGE_MAP_HANDLER(CheneyExBtn, MouseHover, {
	m_bOver = TRUE;
	InvalidateRect(m_hWnd, NULL, TRUE);
	return FALSE;
})
MESSAGE_MAP_HANDLER(CheneyExBtn, MouseLeave, {
	m_bOver = FALSE;
	m_bTracking = FALSE;
	InvalidateRect(m_hWnd, NULL, FALSE);
	return FALSE;
})
MESSAGE_MAP_HANDLER(CheneyExBtn, MouseMove, {
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	return CheneyButton::OnMouseMove(wParam, lParam);
})