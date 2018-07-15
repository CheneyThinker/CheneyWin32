#ifndef CHENEYTREECTRL_H_INCLUDE
#define CHENEYTREECTRL_H_INCLUDE
#pragma once

#include "CheneyWnd.h"

class CheneyTreeCtrl : public CheneyWnd
{
public:
	SPECIAL(CheneyTreeCtrl)
	virtual BOOL Create(LPCTSTR, const RECT&, CheneyWnd*, UINT, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT);
	HTREEITEM InsertItem(const LPSTR);
	HTREEITEM InsertItem(HTREEITEM, const LPSTR);
	HTREEITEM InsertItem(HTREEITEM, CString);
	COLORREF SetLineColor(COLORREF);
	COLORREF GetLineColor() const;
	void SetItemState(HTREEITEM, UINT state, UINT stateMask);
	void SetCheckState(HTREEITEM, BOOL);
	UINT GetItemState(HTREEITEM, UINT mask);
	UINT GetCheckState(HTREEITEM);
	TV_INSERTSTRUCT tvis;
};

#endif