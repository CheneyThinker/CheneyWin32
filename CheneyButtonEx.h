#ifndef CHENEYBUTTONEX_H_INCLUDE
#define CHENEYBUTTONEX_H_INCLUDE
#pragma once

#include "CheneyButton.h"

class CheneyButtonEx : public CheneyButton
{
public:
	SPECIAL(CheneyButtonEx)
	CImage m_imgBtn;
	BOOL m_bIsHover;
	BOOL m_bIsDown;
	void SetImage(UINT);
	MESSAGE_MAP(Create)
	MESSAGE_MAP(MouseMove)
	MESSAGE_MAP(MouseHover)
	MESSAGE_MAP(MouseLeave)
	MESSAGE_MAP(LButtonDown)
	MESSAGE_MAP(LButtonUp)
	MESSAGE_MAP(Paint)
	DECLARE_PROC(WindowProc)
	virtual void DrawItem(LPDRAWITEMSTRUCT);
};

#endif