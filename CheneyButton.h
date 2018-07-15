#ifndef CHENEYBUTTON_H_INCLUDE
#define CHENEYBUTTON_H_INCLUDE
#pragma once

#include "CheneyWnd.h"

class CheneyButton : public CheneyWnd
{
public:
	SPECIAL(CheneyButton)
	virtual BOOL Create(LPCTSTR, DWORD, const RECT&, CheneyWnd*, UINT);
	UINT GetState() const;
	void SetState(BOOL);
	int GetCheck() const;
	void SetCheck(int);
	UINT GetButtonStyle() const;
	void SetButtonStyle(UINT, BOOL bRedraw = TRUE);
	HICON SetIcon(HICON);
	HICON GetIcon() const;
	HBITMAP SetBitmap(HBITMAP);
	HBITMAP GetBitmap() const;
	HCURSOR SetCursor(HCURSOR);
	HCURSOR GetCursor() const;
#if (_WIN32_WINNT >= 0x501)
	BOOL GetIdealSize(SIZE*);
	BOOL SetImageList(PBUTTON_IMAGELIST);
	BOOL GetImageList(PBUTTON_IMAGELIST);
	BOOL SetTextMargin(RECT*);
	BOOL GetTextMargin(RECT*);
#endif
	virtual void DrawItem(LPDRAWITEMSTRUCT);
};

#endif