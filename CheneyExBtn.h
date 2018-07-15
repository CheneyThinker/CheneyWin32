#ifndef CHENEYEXBTN_H_INCLUDE
#define CHENEYEXBTN_H_INCLUDE
#pragma once

#include "CheneyButton.h"

class CheneyExBtn : public CheneyButton
{
	SPECIAL(CheneyExBtn)
	//��ť����߿�
	HPEN m_BoundryPen;
	//���ָ�����ڰ�ť֮��ʱ��ť���ڱ߿�
	HPEN m_InsideBoundryPenLeft;
	HPEN m_InsideBoundryPenRight;
	HPEN m_InsideBoundryPenTop;
	HPEN m_InsideBoundryPenBottom;
	//��ť��ý���ʱ��ť���ڱ߿�
	HPEN m_InsideBoundryPenLeftSel;
	HPEN m_InsideBoundryPenRightSel;
	HPEN m_InsideBoundryPenTopSel;
	HPEN m_InsideBoundryPenBottomSel;
	//��ť�ĵ�ɫ��������Ч����Ч����״̬
	HBRUSH m_FillActive;
	HBRUSH m_FillInactive;
	//��ť��״̬
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