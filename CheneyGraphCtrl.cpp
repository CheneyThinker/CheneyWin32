#include "CheneyGraphCtrl.h"

SPECIAL_HANDLER(CheneyGraphCtrl, {}, {
	int nCount = m_hCheneyGraphCtrlUnit.size();
    for(int i = 0; i < nCount; i++)
    {
        CheneyGraphCtrlUnit* pGraphCtrlUnit = (CheneyGraphCtrlUnit*)m_hCheneyGraphCtrlUnit.at(i);
		FREEP(pGraphCtrlUnit)
        m_hCheneyGraphCtrlUnit.clear();
    }
})

BOOL CheneyGraphCtrl::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CheneyWnd* parent, UINT nID)
{
	return CheneyWnd::CreateEx(0, _T("CHENEYGRAPHCTRL"), lpszWindowName, dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, parent->m_hWnd, (HMENU)nID);
}

LRESULT CheneyGraphCtrl::OnPaint(WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = ::BeginPaint(m_hWnd, &ps);
    assert(hdc);
    {
        SetBkMode(hdc, TRANSPARENT);
        ThinkerRect rect;
        GetClientRect(&rect);
		{
			HBRUSH hBrush = ::CreateSolidBrush(RGB(245, 247, 232));
			::FillRect(hdc, &rect, hBrush);
			::DeleteObject((HGDIOBJ)hBrush);
		}
        m_hRectGraph = rect;
		m_hRectGraph.DeflateRect(0, 0, 0, 50);
        DrawTip(hdc);
        OnPrepareDC(hdc);
        OnDraw(hdc);
    }
    ::EndPaint(m_hWnd, &ps);
    return TRUE;
}

void CheneyGraphCtrl::AddGraphCtrlUnit(CheneyGraphCtrlUnit& graphCtrlUnit)
{
    CheneyGraphCtrlUnit* pGraphCtrlUnit = new CheneyGraphCtrlUnit(graphCtrlUnit);
    m_hCheneyGraphCtrlUnit.push_back(pGraphCtrlUnit);
	InvalidateRect(m_hWnd, NULL, TRUE);
}

void CheneyGraphCtrl::OnPrepareDC(HDC hdc)
{
	int rate = 10;
	LONG width = m_hRectGraph.Width();
	LONG height = m_hRectGraph.Height();
	::SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, width, height, NULL);
	SetViewportOrgEx(hdc, width >> 1, height >> 1, NULL);
	SetWindowExtEx(hdc, width * rate, -height * rate, NULL);
}

void CheneyGraphCtrl::OnDraw(HDC hdc)
{
    DrawCoordinate(hdc);
    DrawGraph(hdc);
}

void CheneyGraphCtrl::DrawCoordinate(HDC hdc)
{
    ThinkerPoint ptLeftTop;
    ptLeftTop.x = m_hRectGraph.left;
    ptLeftTop.y = m_hRectGraph.top;
    DPtoLP(hdc, &ptLeftTop, 1);

    ThinkerPoint ptRightBottom;
    ptRightBottom.x = m_hRectGraph.right;
    ptRightBottom.y = m_hRectGraph.bottom;
    DPtoLP(hdc, &ptRightBottom, 1);

	HPEN hPen = ::CreatePen(PS_SOLID, 0, RGB(135,135,135));
	HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);
	{
		{
			MoveToEx(hdc, ptLeftTop.x, 0, NULL);
			LineTo(hdc, ptRightBottom.x, 0);
			CString str;
			str.Format(_T("%d"), ptRightBottom.x);
			SIZE szStr;
			GetTextExtentPoint32(hdc, str.GetBuffer(0), str.GetLength(), &szStr);
			TextOut(hdc, ptRightBottom.x - szStr.cx, 0, str.GetBuffer(0), str.GetLength());
		}
		{
			MoveToEx(hdc, 0, ptRightBottom.y, NULL);
			LineTo(hdc, 0, ptLeftTop.y);
			CString str;
			str.Format(_T("%d"), ptLeftTop.y);
			TextOut(hdc, 0, ptLeftTop.y, str.GetBuffer(0), str.GetLength());
		}
	}
	::SelectObject(hdc, (HGDIOBJ)hOldPen);
}

void CheneyGraphCtrl::DrawGraph(HDC hdc)
{
    int nCount = m_hCheneyGraphCtrlUnit.size();
    for(int i = 0; i < nCount; i++)
    {
        CheneyGraphCtrlUnit* pGraphCtrlUnit = m_hCheneyGraphCtrlUnit.at(i);
        pGraphCtrlUnit->Draw(hdc);
    }
}

void CheneyGraphCtrl::DrawTip(HDC hdc)
{
    m_hRectTip.clear();
    int nCount = m_hCheneyGraphCtrlUnit.size();
    for(int i = 0; i < nCount; i++)
    {
        ThinkerRect rect;
        rect.left = i * 50;
        rect.right = rect.left + 50;
        rect.top = m_hRectGraph.bottom;
        rect.bottom = rect.top + 50;
        m_hRectTip.push_back(rect);
        CheneyGraphCtrlUnit* pGraphCtrlUnit = (CheneyGraphCtrlUnit*)m_hCheneyGraphCtrlUnit.at(i);
		HBRUSH hBrush = ::CreateSolidBrush(pGraphCtrlUnit->GetColor());
        assert(hBrush);
        {
            FillRect(hdc, rect, hBrush);
        }
        ::DeleteObject((HGDIOBJ)hBrush);
		if(!pGraphCtrlUnit->IsVisible())
        {
            MoveToEx(hdc, rect.left, rect.top, NULL);
            LineTo(hdc, rect.right, rect.bottom);

            MoveToEx(hdc, rect.right, rect.top, NULL);
            LineTo(hdc, rect.left, rect.bottom);
        }
    }
}

LRESULT CheneyGraphCtrl::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
    ThinkerPoint p;
    p.x = LOWORD(lParam);
    p.y = HIWORD(lParam);
    int nCount = (int) m_hRectTip.size();
    for(int i = 0; i < nCount; i++)
    {
        ThinkerRect rect = m_hRectTip.at(i);
		if(rect.PtInRect(p))
        {
            CheneyGraphCtrlUnit* pGraphCtrlUnit = (CheneyGraphCtrlUnit*)m_hCheneyGraphCtrlUnit.at(i);
			pGraphCtrlUnit->SetVisible(!pGraphCtrlUnit->IsVisible());
            InvalidateRect(m_hWnd, NULL, TRUE);
			break;
        }
    }
    return CheneyWnd::OnLButtonUp(wParam, lParam);
}
