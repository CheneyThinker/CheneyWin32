#ifndef CHENEYTABCTRL_H_INCLUDE
#define CHENEYTABCTRL_H_INCLUDE
#pragma once

#include "CheneyButton.h"

class CheneyTabCtrl : public CheneyWnd
{
public:
	SPECIAL(CheneyTabCtrl)
	virtual BOOL Create(LPCTSTR, DWORD, const RECT&, CheneyWnd*, UINT);
	virtual int InsertItem(int iItem, const TCITEM*);
	virtual int InsertItem(int iItem, const LPSTR);
	virtual BOOL DeleteItem(int iItem);
	virtual BOOL DeleteAllItems();
	virtual BOOL GetItemRect(int iItem, RECT*);
	virtual int GetCurSel();
	virtual int SetCurSel(int iItem);
	virtual int HitTest(TC_HITTESTINFO*);
	virtual BOOL SetItemExtra(int);
	virtual int AdjustRect(BOOL, RECT*);
	virtual DWORD SetItemSize(int, int);
	virtual void RemoveImage(int i);
	virtual void SetPadding(int cx, int cy);
	virtual int GetRowCount();
	virtual HWND GetToolTips();
	virtual void SetToolTips(HWND);
	virtual int GetCurFocus();
	virtual void SetCurFocus(int i);
	virtual int SetMinTabWidth(int);
	virtual void DeselectAll(BOOL);
	virtual BOOL HighlightItem(int iItem, BOOL);
	virtual DWORD SetExtendedStyle(DWORD dwStyle);
	virtual DWORD GetExtendedStyle();
	virtual BOOL SetUnicodeFormat(BOOL);
	virtual BOOL GetUnicodeFormat();
	virtual void ShowItem(int iItem);
	static const unsigned int TabSum = 7;
	CheneyButton m_TabBtn[TabSum];
	MESSAGE_MAP(Create)
	MESSAGE_MAP(Command)
	MESSAGE_MAP(Size)
};
/*
DECLARE_WNDPROC(INT_PTR, TAB1)
DECLARE_WNDPROC(INT_PTR, TAB2)
DECLARE_WNDPROC(INT_PTR, TAB3)
const unsigned int TabSum = 4;

class CheneyTabCtrl
{
public:
	SPECIAL(CheneyTabCtrl)
	HWND m_TabHwnd[TabSum];
	static CheneyTabCtrl* GetInstance() { return m_pTabCtrl; }
	static CheneyTabCtrl* m_pTabCtrl;
	BOOL OnInitTabCtrl(void);
	void ShowMessage(void);
};

extern CheneyTabCtrl g_hCheneyTabCtrl;
*/
#endif