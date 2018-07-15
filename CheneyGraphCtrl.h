#ifndef CHENEYGRAPHCTRL_H_INCLUDED
#define CHENEYGRAPHCTRL_H_INCLUDED
#pragma once

#include "CheneyWnd.h"

class CheneyGraphCtrlUnit
{
public:
    CheneyGraphCtrlUnit()
    {
        m_hTitle = _T("");
        m_hColor = RGB(0x00, 0x00, 0x00);
        m_hVisible = TRUE;
        m_hData.clear();
    }
    CheneyGraphCtrlUnit(const CheneyGraphCtrlUnit& graphCtrlUnit)
    {
		if(this == &graphCtrlUnit)
			return;
        m_hTitle = graphCtrlUnit.m_hTitle;
        m_hColor = graphCtrlUnit.m_hColor;
        m_hVisible = graphCtrlUnit.m_hVisible;
        m_hData = graphCtrlUnit.m_hData;
    }
    ~CheneyGraphCtrlUnit()
    {
        m_hData.clear();
    }
    CheneyGraphCtrlUnit& operator=(const CheneyGraphCtrlUnit& graphCtrlUnit)
	{
		if(this == &graphCtrlUnit)
			return *this;
		m_hTitle = graphCtrlUnit.m_hTitle;
        m_hColor = graphCtrlUnit.m_hColor;
        m_hVisible = graphCtrlUnit.m_hVisible;
        m_hData = graphCtrlUnit.m_hData;
		return *this;
	}
	void SetTitle(CString strTitle)
	{
		m_hTitle = strTitle;
	}
	void SetColor(COLORREF cColor)
	{
		m_hColor = cColor;
	}
	void SetVisible(BOOL bVisible)
	{
		m_hVisible = bVisible;
	}
	void AddData(int x, int y)
	{
		ThinkerPoint pt;
		pt.x = x;
		pt.y = y;
		m_hData.push_back(pt);
	}
	CString GetTitle()
	{
		return m_hTitle;
	}
	COLORREF GetColor()
	{
		return m_hColor;
	}
	BOOL IsVisible()
	{
		return m_hVisible;
	}
	vector<ThinkerPoint> GetData()
	{
		return m_hData;
	}
	void Draw(HDC hdc)
    {
		if(!m_hVisible)
            return;
        int nCount = m_hData.size();
        if(nCount <= 0)
            return;
        HPEN hPen = ::CreatePen(PS_SOLID, 20, m_hColor);
        assert(hPen);
        {
            HPEN hOldPen = (HPEN)::SelectObject(hdc, (HGDIOBJ)hPen);
            assert(hOldPen);
            {
                ThinkerPoint p = m_hData.at(0);
                MoveToEx(hdc, p.x, p.y, NULL);
                for(int i = 0; i < nCount; i++)
                {
                    p = m_hData.at(i);
                    LineTo(hdc, p.x, p.y);
                    MoveToEx(hdc, p.x, p.y, NULL);
                }
            }
            ::SelectObject(hdc, (HGDIOBJ)hOldPen);
        }
        ::DeleteObject((HGDIOBJ)hPen);
    }
    CString       m_hTitle;
    COLORREF      m_hColor;
    BOOL          m_hVisible;
    vector<ThinkerPoint> m_hData;
};

class CheneyGraphCtrl : public CheneyWnd
{
public:
	SPECIAL(CheneyGraphCtrl)
	MESSAGE_MAP(Paint)
	MESSAGE_MAP(LButtonUp)
    BOOL Create(LPCTSTR, DWORD, const RECT&, CheneyWnd*, UINT);
    void AddGraphCtrlUnit(CheneyGraphCtrlUnit&);
    void OnPrepareDC(HDC);
    void OnDraw(HDC);
    void DrawCoordinate(HDC);
    void DrawGraph(HDC);
    void DrawTip(HDC);
    vector<CheneyGraphCtrlUnit*> m_hCheneyGraphCtrlUnit;
    ThinkerRect m_hRectGraph;
    vector<ThinkerRect> m_hRectTip;
};

#endif // CHENEYGRAPHCTRL_H_INCLUDED
