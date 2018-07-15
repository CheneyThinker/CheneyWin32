#ifndef CHENEYMAINFRAME_H_INCLUDE
#define CHENEYMAINFRAME_H_INCLUDE
#pragma once

/*#include "CheneyTask.h"
#include "CheneyGraph.h"
#include "CheneyApp.h"
#include "CheneyTabCtrl.h"
#include "CheneyGraphCtrl.h"
#include "CheneyNumberClock.h"
#include "CheneyLogListCtrl.h"*/
#include "CheneyButtonEx.h"
#include "CheneyImage.h"
#include "CheneyAnimateWnd.h"
#include "CheneyDialog.h"

//DECLARE_WNDPROC(BOOL, DialogProc)
//DECLARE_WNDPROC(BOOL, DialogProc2)

class CheneyMainFrame : public CheneyWnd
{
public:
	SPECIAL(CheneyMainFrame)
	/*CheneyLogListCtrl m_hCheneyLogListCtrl;
	void CreateCheneyLogListCtrl();
	ISpVoice* pVoice;
	BOOL DestroySAPI();
	BOOL InitializationSAPI();*/
	HBITMAP m_hBitmap;
	HDC s_hdcMem;
	CheneyDialog m_hCheneyDialog;
	CheneyImage m_hCheneyImage;
	int m_iShowID;
	CheneyAnimateWnd m_hCheneyAnimateWnd;
	HBRUSH m_hBrush;
	//CheneyTabCtrl m_hCheneyTabCtrl;
	//标准控件
	/*CheneyButtonEx m_hButtonEx;
	CheneyButtonEx m_hButtonEx2;
	CheneyButton m_hButton;
	CheneyWnd m_hEdit;
	CheneyWnd m_hListBox;
	CheneyWnd m_hScrollBar;
	CheneyWnd m_hStatic;
	//通用控件
	CheneyWnd m_hTreeCtrl;
	void CreateCommonCtrl();
	void UpdateIcon();
	void HandlerIcon(WPARAM);*/
	void CreateMenu();
	void HandlerMenu(WPARAM);
	//void CreateDlg();
	/*void CreateCheneyNumberClock();
	void CreateCheneyGraphCtrl();
	CheneyButton m_hCheneyButton;
	void CreateCheneyButton();
	CHENEYSHAPE m_hCheneyShape;
	BOOL m_bStart;
	ThinkerPoint m_ptOrigin;
	CheneyGraphCtrl m_hCheneyGraphCtrl;
	CheneyNumberClock m_hCheneyNumberClock;*/
	MESSAGE_MAP(Close)
	MESSAGE_MAP(Destroy)
	MESSAGE_MAP(Create)
	MESSAGE_MAP(CtlColorDlg)
	//MESSAGE_MAP(Notify)
	MESSAGE_MAP(Size)
	MESSAGE_MAP(CtlColorStatic)
	MESSAGE_MAP(Command)
	MESSAGE_MAP(KeyDown)
	MESSAGE_MAP(DropFiles)
	MESSAGE_MAP(Paint)
	MESSAGE_MAP(LButtonDown)
	MESSAGE_MAP(EraseBkgnd)
	/*CImage m_ImageBmp;
	Image* m_pImage;
	void DrawViewImage(HDC, CImage&, BYTE);
	BOOL DrawImagePng(HDC, INT, INT);
	MESSAGE_MAP(ContextMenu)
	MESSAGE_MAP(DrawItem)
	MESSAGE_MAP(Timer)
	MESSAGE_MAP(MouseMove)
	MESSAGE_MAP(LButtonDown)
	MESSAGE_MAP(LButtonUp)
	MESSAGE_MAP(WinIniChange)*/
};

#endif