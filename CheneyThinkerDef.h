#ifndef CHENEYTHINKERDEF_H_INCLUDE
#define CHENEYTHINKERDEF_H_INCLUDE
#pragma once

#define SPECIAL(CLS)		\
		CLS(void);			\
		virtual ~CLS(void);	\

#define SPECIAL_HANDLER(CLS, init, free)	\
		CLS::CLS(void)						\
			init							\
		CLS::~CLS(void)						\
			free							\

#define FREEP(pointer)		\
	if(NULL != pointer)		\
	{						\
		assert(pointer);	\
		if(pointer)			\
		{					\
			delete pointer;	\
			pointer = NULL;	\
		}					\
	}						\

#define STR(string) #string

#define DLLLIBRARY(method)						\
		typedef int (* lp##method)(int, int);	\
		lp##method method;						\

#define GETFUN(dll, fun)										\
		fun = (lp##fun)GetProcAddress(h##dll##DLL, STR(fun));	\

#define FREE(cheneyWndOfCls) FREEP(cheneyWndOfCls.m_hWnd)

#define DECLARE_PROC(name) virtual LRESULT name(UINT, WPARAM, LPARAM);

#define DECLARE_WNDPROC(result, name) result CALLBACK name(HWND, UINT, WPARAM, LPARAM);

#define MSGMAP(result, method) result method(WPARAM, LPARAM);

#define MESSAGE_MAP(method) virtual MSGMAP(LRESULT, On##method)

#define MESSAGE_MAP_HANDLER(CLS, method, code)					\
		LRESULT CLS::On##method(WPARAM wParam, LPARAM lParam)	\
			code												\

#define WINPROC_HANDLER(method, messages)			\
			case messages:							\
				return On##method(wParam, lParam);	\

#define DEFAULT_HANDLER(method, messages)						\
	LRESULT CheneyWnd::On##method(WPARAM wParam, LPARAM lParam)	\
	{															\
		if(messages == WM_CREATE || messages == WM_NCCREATE)	\
			return TRUE;										\
		return DefWinProc(messages, wParam, lParam);			\
	}															\

#define DEFAULT DEFAULT_HANDLER
#define WINPROC WINPROC_HANDLER
#define BEFORE	1
#define AFTER	2

#define DECLARE_MESSAGE_MAP()			\
		MESSAGE_MAP(CheneyThinker)		\
		MESSAGE_MAP(Activate)			\
		MESSAGE_MAP(ActivateApp)		\
		MESSAGE_MAP(AskCbFormatName)	\
		MESSAGE_MAP(CancelMode)			\
		MESSAGE_MAP(CaptureChanged)		\
		MESSAGE_MAP(ChangeCbChain)		\
		MESSAGE_MAP(Char)				\
		MESSAGE_MAP(CharToItem)			\
		MESSAGE_MAP(ChildActivate)		\
		MESSAGE_MAP(Close)				\
		MESSAGE_MAP(Command)			\
		MESSAGE_MAP(Compacting)			\
		MESSAGE_MAP(CompareItem)		\
		MESSAGE_MAP(ContextMenu)		\
		MESSAGE_MAP(CopyData)			\
		MESSAGE_MAP(Create)				\
		MESSAGE_MAP(CtlColorDlg)		\
		MESSAGE_MAP(CtlColorStatic)		\
		MESSAGE_MAP(DeadChar)			\
		MESSAGE_MAP(DeleteItem)			\
		MESSAGE_MAP(Destroy)			\
		MESSAGE_MAP(DestroyClipboard)	\
		MESSAGE_MAP(DeviceChange)		\
		MESSAGE_MAP(DevModeChange)		\
		MESSAGE_MAP(DrawClipboard)		\
		MESSAGE_MAP(DrawItem)			\
		MESSAGE_MAP(DropFiles)			\
		MESSAGE_MAP(Enable)				\
		MESSAGE_MAP(EndSession)			\
		MESSAGE_MAP(EnterIdle)			\
		MESSAGE_MAP(EraseBkgnd)			\
		MESSAGE_MAP(FontChange)			\
		MESSAGE_MAP(GetDlgCode)			\
		MESSAGE_MAP(GetMinMaxInfo)		\
		MESSAGE_MAP(Help)				\
		MESSAGE_MAP(HScroll)			\
		MESSAGE_MAP(HScrollClipboard)	\
		MESSAGE_MAP(IconEraseBkgnd)		\
		MESSAGE_MAP(InitMenu)			\
		MESSAGE_MAP(InitMenuPopup)		\
		MESSAGE_MAP(KeyDown)			\
		MESSAGE_MAP(KeyUp)				\
		MESSAGE_MAP(KillFocus)			\
		MESSAGE_MAP(LButtonDblClk)		\
		MESSAGE_MAP(LButtonDown)		\
		MESSAGE_MAP(LButtonUp)			\
		MESSAGE_MAP(MButtonDblClk)		\
		MESSAGE_MAP(MButtonDown)		\
		MESSAGE_MAP(MButtonUp)			\
		MESSAGE_MAP(MDIActivate)		\
		MESSAGE_MAP(MeasureItem)		\
		MESSAGE_MAP(MenuChar)			\
		MESSAGE_MAP(MenuSelect)			\
		MESSAGE_MAP(MouseActivate)		\
		MESSAGE_MAP(MouseMove)			\
		MESSAGE_MAP(MouseWheel)			\
		MESSAGE_MAP(Move)				\
		MESSAGE_MAP(Moving)				\
		MESSAGE_MAP(NcActivate)			\
		MESSAGE_MAP(NcCalcSize)			\
		MESSAGE_MAP(NcCreate)			\
		MESSAGE_MAP(NcDestroy)			\
		MESSAGE_MAP(NcHitTest)			\
		MESSAGE_MAP(NcLButtonDblClk)	\
		MESSAGE_MAP(NcLButtonDown)		\
		MESSAGE_MAP(NcLButtonUp)		\
		MESSAGE_MAP(NcMButtonDblClk)	\
		MESSAGE_MAP(NcMButtonDown)		\
		MESSAGE_MAP(NcMButtonUp)		\
		MESSAGE_MAP(NcMouseMove)		\
		MESSAGE_MAP(NcPaint)			\
		MESSAGE_MAP(NcRButtonDblClk)	\
		MESSAGE_MAP(NcRButtonDown)		\
		MESSAGE_MAP(NcRButtonUp)		\
		MESSAGE_MAP(Notify)				\
		MESSAGE_MAP(Paint)				\
		MESSAGE_MAP(PaintClipboard)		\
		MESSAGE_MAP(PaletteChanged)		\
		MESSAGE_MAP(PaletteIsChanging)	\
		MESSAGE_MAP(ParentNotify)		\
		MESSAGE_MAP(QueryDragIcon)		\
		MESSAGE_MAP(QueryEndSession)	\
		MESSAGE_MAP(QueryNewPalette)	\
		MESSAGE_MAP(QueryOpen)			\
		MESSAGE_MAP(RButtonDblClk)		\
		MESSAGE_MAP(RButtonDown)		\
		MESSAGE_MAP(RButtonUp)			\
		MESSAGE_MAP(RenderAllFormats)	\
		MESSAGE_MAP(RenderFormat)		\
		MESSAGE_MAP(SetCursor)			\
		MESSAGE_MAP(SetFocus)			\
		MESSAGE_MAP(ShowWindow)			\
		MESSAGE_MAP(Size)				\
		MESSAGE_MAP(SizeClipboard)		\
		MESSAGE_MAP(Sizing)				\
		MESSAGE_MAP(SpoolerStatus)		\
		MESSAGE_MAP(StyleChanged)		\
		MESSAGE_MAP(StyleChanging)		\
		MESSAGE_MAP(SysChar)			\
		MESSAGE_MAP(SysColorChange)		\
		MESSAGE_MAP(SysCommand)			\
		MESSAGE_MAP(SysDeadChar)		\
		MESSAGE_MAP(SysKeyDown)			\
		MESSAGE_MAP(SysKeyUp)			\
		MESSAGE_MAP(TCard)				\
		MESSAGE_MAP(TimeChange)			\
		MESSAGE_MAP(Timer)				\
		MESSAGE_MAP(VKeyToItem)			\
		MESSAGE_MAP(VScroll)			\
		MESSAGE_MAP(VScrollClipboard)	\
		MESSAGE_MAP(WindowPosChanged)	\
		MESSAGE_MAP(WindowPosChanging)	\
		MESSAGE_MAP(WinIniChange)

#define MESSAGE_HANDLER(pos, handler)							\
		handler(CheneyThinker, WM_CHENEYTHINKER)				\
		handler(Activate, WM_ACTIVATE)							\
		handler(ActivateApp, WM_ACTIVATEAPP)					\
		handler(AskCbFormatName, WM_ASKCBFORMATNAME)			\
		handler(CancelMode, WM_CANCELMODE)						\
		handler(CaptureChanged, WM_CAPTURECHANGED)				\
		handler(ChangeCbChain, WM_CHANGECBCHAIN)				\
		handler(Char, WM_CHAR)									\
		handler(CharToItem, WM_CHARTOITEM)						\
		handler(ChildActivate, WM_CHILDACTIVATE)				\
		handler(Close, WM_CLOSE)								\
		handler(Command, WM_COMMAND)							\
		handler(Compacting, WM_COMPACTING)						\
		handler(CompareItem, WM_COMPAREITEM)					\
		handler(ContextMenu, WM_CONTEXTMENU)					\
		handler(CopyData, WM_COPYDATA)							\
		handler(Create, WM_CREATE)								\
		handler(CtlColorDlg, WM_CTLCOLORDLG)					\
		handler(CtlColorStatic, WM_CTLCOLORSTATIC)				\
		handler(DeadChar, WM_DEADCHAR)							\
		handler(DeleteItem, WM_DELETEITEM)						\
		handler(Destroy, WM_DESTROY)							\
		handler(DestroyClipboard, WM_DESTROYCLIPBOARD)			\
		handler(DeviceChange, WM_DEVICECHANGE)					\
		handler(DevModeChange, WM_DEVMODECHANGE)				\
		handler(DrawClipboard, WM_DRAWCLIPBOARD)				\
		handler(DrawItem, WM_DRAWITEM)							\
		handler(DropFiles, WM_DROPFILES)						\
		handler(Enable, WM_ENABLE)								\
		handler(EndSession, WM_ENDSESSION)						\
		handler(EnterIdle, WM_ENTERIDLE)						\
		handler(EraseBkgnd, WM_ERASEBKGND)						\
		handler(FontChange, WM_FONTCHANGE)						\
		handler(GetDlgCode, WM_GETDLGCODE)						\
		handler(GetMinMaxInfo, WM_GETMINMAXINFO)				\
		handler(Help, WM_HELP)									\
		handler(HScroll, WM_HSCROLL)							\
		handler(HScrollClipboard, WM_HSCROLLCLIPBOARD)			\
		handler(IconEraseBkgnd, WM_ICONERASEBKGND)				\
		handler(InitMenu, WM_INITMENU)							\
		handler(InitMenuPopup, WM_INITMENUPOPUP)				\
		handler(KeyDown, WM_KEYDOWN)							\
		handler(KeyUp, WM_KEYUP)								\
		handler(KillFocus, WM_KILLFOCUS)						\
		handler(LButtonDblClk, WM_LBUTTONDBLCLK)				\
		handler(LButtonDown, WM_LBUTTONDOWN)					\
		handler(LButtonUp, WM_LBUTTONUP)						\
		handler(MButtonDblClk, WM_MBUTTONDBLCLK)				\
		handler(MButtonDown, WM_MBUTTONDOWN)					\
		handler(MButtonUp, WM_MBUTTONUP)						\
		handler(MDIActivate, WM_MDIACTIVATE)					\
		handler(MeasureItem, WM_MEASUREITEM)					\
		handler(MenuChar, WM_MENUCHAR)							\
		handler(MenuSelect, WM_MENUSELECT)						\
		handler(MouseActivate, WM_MOUSEACTIVATE)				\
		handler(MouseMove, WM_MOUSEMOVE)						\
		handler(MouseWheel, WM_MOUSEWHEEL)						\
		handler(Move, WM_MOVE)									\
		handler(Moving, WM_MOVING)								\
		handler(NcActivate, WM_NCACTIVATE)						\
		handler(NcCalcSize, WM_NCCALCSIZE)						\
		handler(NcCreate, WM_NCCREATE)							\
		handler(NcDestroy, WM_NCDESTROY)						\
		handler(NcHitTest, WM_NCHITTEST)						\
		handler(NcLButtonDblClk, WM_NCLBUTTONDBLCLK)			\
		handler(NcLButtonDown, WM_NCLBUTTONDOWN)				\
		handler(NcLButtonUp, WM_NCLBUTTONUP)					\
		handler(NcMButtonDblClk, pos == BEFORE ? WM_NCRBUTTONDBLCLK : WM_NCMBUTTONDBLCLK) \
		handler(NcMButtonDown, WM_NCMBUTTONDOWN)				\
		handler(NcMButtonUp, WM_NCMBUTTONUP)					\
		handler(NcMouseMove, WM_NCMOUSEMOVE)					\
		handler(NcPaint, WM_NCPAINT)							\
		handler(NcRButtonDblClk, WM_NCRBUTTONDBLCLK)			\
		handler(NcRButtonDown, WM_NCRBUTTONDOWN)				\
		handler(NcRButtonUp, WM_NCRBUTTONUP)					\
		handler(Notify, WM_NOTIFY)								\
		handler(Paint, WM_PAINT)								\
		handler(PaintClipboard, WM_PAINTCLIPBOARD)				\
		handler(PaletteChanged, WM_PALETTECHANGED)				\
		handler(PaletteIsChanging, WM_PALETTEISCHANGING)		\
		handler(ParentNotify, WM_PARENTNOTIFY)					\
		handler(QueryDragIcon, WM_QUERYDRAGICON)				\
		handler(QueryEndSession, WM_QUERYENDSESSION)			\
		handler(QueryNewPalette, WM_QUERYNEWPALETTE)			\
		handler(QueryOpen, WM_QUERYOPEN)						\
		handler(RButtonDblClk, WM_RBUTTONDBLCLK)				\
		handler(RButtonDown, WM_RBUTTONDOWN)					\
		handler(RButtonUp, WM_RBUTTONUP)						\
		handler(RenderAllFormats, WM_RENDERALLFORMATS)			\
		handler(RenderFormat, WM_RENDERFORMAT)					\
		handler(SetCursor, WM_SETCURSOR)						\
		handler(SetFocus, WM_SETFOCUS)							\
		handler(ShowWindow, WM_SHOWWINDOW)						\
		handler(Size, WM_SIZE)									\
		handler(SizeClipboard, WM_SIZECLIPBOARD)				\
		handler(Sizing, WM_SIZING)								\
		handler(SpoolerStatus, WM_SPOOLERSTATUS)				\
		handler(StyleChanged, WM_STYLECHANGED)					\
		handler(StyleChanging, WM_STYLECHANGING)				\
		handler(SysChar, WM_SYSCHAR)							\
		handler(SysColorChange, WM_SYSCOLORCHANGE)				\
		handler(SysCommand, WM_SYSCOMMAND)						\
		handler(SysDeadChar, pos == BEFORE ? WM_DEADCHAR : WM_SYSDEADCHAR) \
		handler(SysKeyDown, WM_SYSKEYDOWN)						\
		handler(SysKeyUp, WM_SYSKEYUP)							\
		handler(TCard, WM_TCARD)								\
		handler(TimeChange, WM_TIMECHANGE)						\
		handler(Timer, pos == BEFORE ? WM_TIMECHANGE : WM_TIMER)	\
		handler(VKeyToItem, WM_VKEYTOITEM)						\
		handler(VScroll, WM_VSCROLL)							\
		handler(VScrollClipboard, WM_VSCROLLCLIPBOARD)			\
		handler(WindowPosChanged, WM_WINDOWPOSCHANGED)			\
		handler(WindowPosChanging, WM_WINDOWPOSCHANGING)		\
		handler(WinIniChange, WM_WININICHANGE)

#endif