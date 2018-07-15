#ifndef CHENEYLISTCTRL_H_INCLUDE
#define CHENEYLISTCTRL_H_INCLUDE
#pragma once

#include "CheneyWnd.h"

class CheneyListCtrl : public CheneyWnd
{
public:
	SPECIAL(CheneyListCtrl)
	virtual BOOL Create(LPCTSTR, DWORD, const RECT&, CheneyWnd*, UINT);
	int GetItemCount() const;
	BOOL DeleteItem(int nItem);
	BOOL DeleteAllItems();
	UINT GetCallbackMask() const;
	BOOL SetCallbackMask(UINT nMask);
	int GetNextItem(int nItem, int nFlags) const;
	BOOL SetItemPosition(int nItem, POINT);
	BOOL GetItemPosition(int nItem, LPPOINT) const;
	int GetStringWidth(LPCTSTR) const;
	BOOL EnsureVisible(int nItem, BOOL bPartialOK);
	BOOL Scroll(ThinkerSize size);
	BOOL RedrawItems(int nFirst, int nLast);
	BOOL Arrange(UINT nCode);
	void InsertColumn(int, const LPSTR, int);
	int InsertColumn(int, const LPSTR, int, int, int);
	int InsertColumn(int, const LV_COLUMN*);
	BOOL DeleteColumn(int);
	BOOL SetColumnWidth(int, int);
	int InsertItem(int nItem, const LPSTR, int nImage);
	int InsertItem(int nItem, const LPSTR);
	int InsertItem(const LVITEM*);
	BOOL GetItem(LVITEM*) const;
	BOOL SetItem(const LVITEM*);
	BOOL SetItemData(int nItem, DWORD_PTR);
	BOOL SetTextColor(COLORREF);
	BOOL SetTextBkColor(COLORREF);
	BOOL SetBkColor(COLORREF);
	COLORREF GetBkColor() const;
};

#endif