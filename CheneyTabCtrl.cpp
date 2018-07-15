#include "CheneyTabCtrl.h"

SPECIAL_HANDLER(CheneyTabCtrl, {
	for(int i = 0; i < TabSum; i++)
		m_TabBtn[i].m_hWnd = NULL;
}, {})

BOOL CheneyTabCtrl::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CheneyWnd* parent, UINT nID)
{
	CheneyWnd* pWnd = this;
	return pWnd->CreateEx(NULL, WC_TABCONTROL, lpszCaption, dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, parent->m_hWnd, (HMENU) nID);
}
MESSAGE_MAP_HANDLER(CheneyTabCtrl, Command, {
	TCHAR temp[256];
	for(int i = 0; i < CheneyTabCtrl::TabSum; i++)
	{
		wsprintf(temp, TEXT("星期%d"), i);
		if(IDB_TABBTN + i == wParam)
			MessageBox(m_hWnd, temp, TEXT(""), MB_OK);
	}
	return CheneyWnd::OnCommand(wParam, lParam);
})
MESSAGE_MAP_HANDLER(CheneyTabCtrl, Create, {
	TCHAR temp[256];
	RECT rect;
	GetClientRect(&rect);
	for(int i = 0; i < TabSum; i++)
	{
		wsprintf(temp, TEXT("星期%d"), i);
		InsertItem(i, temp);
		if(NULL == m_TabBtn[i].m_hWnd)
		{
			m_TabBtn[i].Create(temp, WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, ThinkerRect(50, 50, 80, 30), this, IDB_TABBTN + i);
			MoveWindow(m_TabBtn[i].m_hWnd, 50, 50, rect.right - rect.left - 100, rect.bottom - rect.top - 60, FALSE);
			m_TabBtn[i].ShowWindow(i == 0 ? TRUE : FALSE);
		}
	}
	return TRUE;
})

MESSAGE_MAP_HANDLER(CheneyTabCtrl, Size, {
	RECT rect = GetClientRect();
	rect.right = rect.right - rect.left - 100;
	rect.bottom = rect.bottom - rect.top - 60;
	rect.left = rect.top = 50;
	for(int i = 0; i < TabSum; i++)
		RepaintWindow(&m_TabBtn[i], rect);
	return CheneyWnd::OnSize(wParam, lParam);
})

void CheneyTabCtrl::ShowItem(int iItem)
{
	for(int i = 0; i < CheneyTabCtrl::TabSum; i++)
	{
		if(i == iItem)
			m_TabBtn[i].ShowWindow(TRUE);
		else
			m_TabBtn[i].ShowWindow(FALSE);
	}
}

int CheneyTabCtrl::InsertItem(int iItem, const LPSTR pszText)
{
	TCITEM ti;
	ti.mask = TCIF_TEXT | TCIF_IMAGE;
	ti.iImage = -1;
	ti.pszText = pszText;
	return InsertItem(iItem, &ti);
}

int CheneyTabCtrl::InsertItem(int iItem, const TCITEM* pitem)
{
	assert(::IsWindow(m_hWnd));
	return (int)SendMessage(m_hWnd, TCM_INSERTITEM, (WPARAM)(int)(iItem), (LPARAM)(const TC_ITEM *)(pitem));
}

BOOL CheneyTabCtrl::DeleteItem(int iItem)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL)SendMessage(m_hWnd, TCM_DELETEITEM, (WPARAM)(int)(iItem), 0L);
}

BOOL CheneyTabCtrl::DeleteAllItems()
{
	assert(::IsWindow(m_hWnd));
	return (BOOL)SendMessage(m_hWnd, TCM_DELETEALLITEMS, 0, 0L);
}

BOOL CheneyTabCtrl::GetItemRect(int iItem, RECT* prc)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL)SendMessage(m_hWnd, TCM_GETITEMRECT, (WPARAM)(int)(iItem), (LPARAM)(RECT *)(prc));
}

int CheneyTabCtrl::GetCurSel()
{
	assert(::IsWindow(m_hWnd));
	return (int)SendMessage(m_hWnd, TCM_GETCURSEL, 0, 0);
}

int CheneyTabCtrl::SetCurSel(int iItem)
{
	assert(::IsWindow(m_hWnd));
	return (int)SendMessage(m_hWnd, TCM_SETCURSEL, (WPARAM)(iItem), 0);
}

int CheneyTabCtrl::HitTest(TC_HITTESTINFO* pinfo)
{
	assert(::IsWindow(m_hWnd));
	return (int)SendMessage(m_hWnd, TCM_HITTEST, 0, (LPARAM)(TC_HITTESTINFO *)(pinfo));
}

// cd what
BOOL CheneyTabCtrl::SetItemExtra(int cb)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL)SendMessage(m_hWnd, TCM_SETITEMEXTRA, (WPARAM)(cb), 0L);
}

int CheneyTabCtrl::AdjustRect(BOOL bLarger, RECT* prc)
{
	assert(::IsWindow(m_hWnd));
	return (int)SendMessage(m_hWnd, TCM_ADJUSTRECT, (WPARAM)(BOOL)(bLarger), (LPARAM)(RECT *)(prc));
}

DWORD CheneyTabCtrl::SetItemSize(int x, int y)
{
	assert(::IsWindow(m_hWnd));
	return (DWORD)SendMessage(m_hWnd, TCM_SETITEMSIZE, 0, MAKELPARAM(x, y));
}

void CheneyTabCtrl::RemoveImage(int i)
{
	assert(::IsWindow(m_hWnd));
	return (void)SendMessage(m_hWnd, TCM_REMOVEIMAGE, i, 0L);
}

void CheneyTabCtrl::SetPadding(int cx, int cy)
{
	assert(::IsWindow(m_hWnd));
	return (void)SendMessage(m_hWnd, TCM_SETPADDING, 0, MAKELPARAM(cx, cy));
}

int CheneyTabCtrl::GetRowCount()
{
	assert(::IsWindow(m_hWnd));
	return (int)SendMessage(m_hWnd, TCM_GETROWCOUNT, 0, 0L);
}

HWND CheneyTabCtrl::GetToolTips()
{
	assert(::IsWindow(m_hWnd));
	return (HWND)SendMessage(m_hWnd, TCM_GETTOOLTIPS, 0, 0L);
}

void CheneyTabCtrl::SetToolTips(HWND hwndTT)
{
	assert(::IsWindow(m_hWnd));
	return (void)SendMessage(m_hWnd, TCM_SETTOOLTIPS, (WPARAM)(hwndTT), 0L);
}

int CheneyTabCtrl::GetCurFocus()
{
	assert(::IsWindow(m_hWnd));
	return (int)SendMessage(m_hWnd, TCM_GETCURFOCUS, 0, 0);
}

void CheneyTabCtrl::SetCurFocus(int i)
{
	assert(::IsWindow(m_hWnd));
	return (void)SendMessage(m_hWnd, TCM_SETCURFOCUS, i, 0);
}

int CheneyTabCtrl::SetMinTabWidth(int x)
{
	assert(::IsWindow(m_hWnd));
	return (int)SendMessage(m_hWnd, TCM_SETMINTABWIDTH, 0, x);
}

void CheneyTabCtrl::DeselectAll(BOOL fExcludeFocus)
{
	assert(::IsWindow(m_hWnd));
	return (void)SendMessage(m_hWnd, TCM_DESELECTALL, fExcludeFocus, 0);
}

BOOL CheneyTabCtrl::HighlightItem(int iItem, BOOL fHighlight)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL)SendMessage(m_hWnd, TCM_HIGHLIGHTITEM, (WPARAM)(iItem), (LPARAM)MAKELONG (fHighlight, 0));
}

DWORD CheneyTabCtrl::SetExtendedStyle(DWORD dwStyle)
{
	assert(::IsWindow(m_hWnd));
	return (DWORD)SendMessage(m_hWnd, TCM_SETEXTENDEDSTYLE, 0, dwStyle);
}

DWORD CheneyTabCtrl::GetExtendedStyle()
{
	assert(::IsWindow(m_hWnd));
	return (DWORD)SendMessage(m_hWnd, TCM_GETEXTENDEDSTYLE, 0, 0);
}

BOOL CheneyTabCtrl::SetUnicodeFormat(BOOL fUnicode)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL)SendMessage(m_hWnd, TCM_SETUNICODEFORMAT, (WPARAM)(fUnicode), 0);
}

BOOL CheneyTabCtrl::GetUnicodeFormat()
{
	assert(::IsWindow(m_hWnd));
	return (BOOL)SendMessage(m_hWnd, TCM_GETUNICODEFORMAT, 0, 0);
}

/*CheneyTabCtrl* CheneyTabCtrl::m_pTabCtrl = NULL;
CheneyTabCtrl g_hCheneyTabCtrl;

SPECIAL_HANDLER(CheneyTabCtrl, {
	assert(m_pTabCtrl == NULL);
	if(m_pTabCtrl == NULL)
		m_pTabCtrl == this;
	ZeroMemory(m_TabHwnd, sizeof(m_TabHwnd));
}, {})

BOOL CheneyTabCtrl::OnInitTabCtrl(void)
{
	m_TabHwnd[0]=CreateDialog(win.hInst,MAKEINTRESOURCE(IDD_TAB1),win.hwnd,TAB1);
	m_TabHwnd[1]=CreateDialog(win.hInst,MAKEINTRESOURCE(IDD_TAB1),win.hwnd,TAB2);
	m_TabHwnd[2]=CreateDialog(win.hInst,MAKEINTRESOURCE(IDD_TAB1),win.hwnd,TAB3);
	win.hTable=GetDlgItem(win.hwnd,IDC_TAB1);
	TCITEM tic;
	tic.mask=TCIF_TEXT;
	tic.pszText=TEXT("标签3");
	SendMessage(win.hTable,TCM_SETITEMSIZE,0,MAKELPARAM(80,30));   //设置标签宽度和高度
	SendMessage(win.hTable, TCM_INSERTITEM, 0, (LPARAM) &tic);
	tic.pszText=TEXT("标签2");
	SendMessage(win.hTable,TCM_SETITEMSIZE,0,MAKELPARAM(80,30));   //设置标签宽度和高度
	SendMessage(win.hTable, TCM_INSERTITEM, 0, (LPARAM) &tic);
	tic.pszText=TEXT("标签1");
	SendMessage(win.hTable,TCM_SETITEMSIZE,0,MAKELPARAM(80,30));   //设置标签宽度和高
	SendMessage(win.hTable, TCM_INSERTITEM, 0, (LPARAM) &tic);
	RECT rtTabCtl;//Tab控件位置
	GetWindowRect(win.hTable,&rtTabCtl);
	for(int i = 0; i <TabSum; i++)
	{
		RECT rtTab={0};
		GetWindowRect(m_TablehWnd[i], &rtTab);
		int x,y,cx,cy;
		POINT point,point1;
		point.x=rtTabCtl.left;
		point.y=rtTabCtl.top;
		ScreenToClient(win.hwnd,&point);
		x=point.x;
		y=point.y;
		point1.x=rtTabCtl.right;
		point1.y=rtTabCtl.bottom;
		ScreenToClient(win.hwnd,&point1);
		cx=point1.x-x;
		cy=point1.y-y;
		SetWindowPos(m_TablehWnd[i], NULL, x, y+30, cx,cy,SWP_NOZORDER | SWP_NOREDRAW);
		//IDD_TAB1的XY坐标等于IDC_TABLE1控件的XY坐标  通过ScreenToClient函数将屏幕XY坐标转换客户区坐标。GetWindowRect是屏幕坐标
		//IDD_TAB1的CX,CY是。right-left,bottom-top就是宽带和高度
	}
	ShowWindow(m_TablehWnd[0],SW_SHOW);
	SendMessage(win.hTable, TCM_SETCURSEL, 0, 0);
	return true;
}

void CheneyTabCtrl::ShowMessage(void)
{
	MessageBox(NULL, TEXT("测试一下"), TEXT("提示"), MB_OK);
	return;
}

INT_PTR CALLBACK TAB1( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			CheneyTabCtrl::GetInstance()->ShowMessage();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TAB2( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			CheneyTabCtrl::GetInstance()->ShowMessage();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TAB3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			CheneyTabCtrl::GetInstance()->ShowMessage();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}*/