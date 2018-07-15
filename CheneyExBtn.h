#ifndef CHENEYEXBTN_H_INCLUDE
#define CHENEYEXBTN_H_INCLUDE
#pragma once

#include "CheneyButton.h"

class CheneyExBtn : public CheneyButton
{
	SPECIAL(CheneyExBtn)
	//按钮的外边框
	HPEN m_BoundryPen;
	//鼠标指针置于按钮之上时按钮的内边框
	HPEN m_InsideBoundryPenLeft;
	HPEN m_InsideBoundryPenRight;
	HPEN m_InsideBoundryPenTop;
	HPEN m_InsideBoundryPenBottom;
	//按钮获得焦点时按钮的内边框
	HPEN m_InsideBoundryPenLeftSel;
	HPEN m_InsideBoundryPenRightSel;
	HPEN m_InsideBoundryPenTopSel;
	HPEN m_InsideBoundryPenBottomSel;
	//按钮的底色，包括有效和无效两种状态
	HBRUSH m_FillActive;
	HBRUSH m_FillInactive;
	//按钮的状态
	BOOL m_bCLicking;
	BOOL m_bOver;
	BOOL m_bTracking;
	BOOL m_bSelected;
	BOOL m_bFocus;
	UINT id;
	virtual void PreSubclassWindow();
	void LoadImg(UINT ID);
	virtual void DrawItem(LPDRAWITEMSTRUCT);
	virtual void DoGradientFill(HDC, ThinkerRect*);
	virtual void DrawInsideBorder(HDC, ThinkerRect*);
	MESSAGE_MAP(MouseMove)
	MESSAGE_MAP(MouseLeave)
	MESSAGE_MAP(MouseHover)
	MESSAGE_MAP(LButtonDown)
	MESSAGE_MAP(EraseBkgnd)
};

#endif