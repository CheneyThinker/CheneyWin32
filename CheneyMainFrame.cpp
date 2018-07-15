#include "CheneyMainFrame.h"

SPECIAL_HANDLER(CheneyMainFrame, {
	/*m_bStart = FALSE;
	m_hCheneyButton.m_hWnd = NULL;
	m_hCheneyGraphCtrl.m_hWnd = NULL;
	m_hCheneyLogListCtrl.m_hWnd = NULL;
	pVoice = NULL;*/
	//m_hCheneyTabCtrl.m_hWnd = NULL;
	m_iShowID = 0;
}, {
	//FREE(m_hCheneyButton)
	//FREE(m_hCheneyGraphCtrl)
	//g_hCheneyThreadLog.Stop();
	//DestroySAPI();
})
MESSAGE_MAP_HANDLER(CheneyMainFrame, Close, {
	//AnimateOut();
	return DestroyWindow();
})
MESSAGE_MAP_HANDLER(CheneyMainFrame, Destroy, {
	//KillTimer(m_hWnd, IDT_TIMER);
	m_hCheneyImage.DeleteDC();
	DeleteObject(m_hBitmap);
	DeleteDC(s_hdcMem);
	PostQuitMessage(0);
	return TRUE;
})
MESSAGE_MAP_HANDLER(CheneyMainFrame, CtlColorDlg, {
	//return (BOOL)m_hBrush;
	RECT rect = GetClientRect();
	m_hCheneyImage.Draw((HDC)wParam, rect.right, rect.bottom);
	return (BOOL)((HBRUSH) GetStockObject(NULL_BRUSH));
})
MESSAGE_MAP_HANDLER(CheneyMainFrame, CtlColorStatic, {
	return CheneyWnd::OnCtlColorStatic(wParam, lParam);
})
MESSAGE_MAP_HANDLER(CheneyMainFrame, LButtonDown, {
		PostMessage(m_hWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
		return TRUE;
})
MESSAGE_MAP_HANDLER(CheneyMainFrame, Create, {
	/*SetWindowText(m_hWnd, TEXT("CheneyThinker"));
	SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) | WS_SIZEBOX);
	CenterWindow();
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
	HBITMAP hBitmap = ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_GIRL));
	m_hBrush = CreatePatternBrush(hBitmap);
	m_hCheneyAnimateWnd.SetWindowHwnd(m_hWnd);
	m_hCheneyAnimateWnd.AnimateWindow(600);
	DragAcceptFiles(m_hWnd, TRUE);
	m_hCheneyImage.Load(m_hWnd, TEXT("res\\107.bmp"));
	m_iShowID = 0;
	//m_hBitmap = (HBITMAP)::LoadImage(NULL, TEXT("res\\background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//::LoadBitmap((HINSTANCE)GetModuleHandle(NULL), MAKEINTERSOURCE(IDB_BG));
	/*int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	RECT windowRect;
	GetWindowRect(m_hWnd, &windowRect);
	int cx = (x - windowRect.right) >> 1;
	int cy = (y - windowRect.bottom) >> 1;
	SetWindowPos(m_hWnd, NULL, cx, cy, NULL, NULL, SWP_SHOWWINDOW | SWP_NOSIZE);
	m_ImageBmp.Load(TEXT("res\\background.bmp"));
	CT2CW strFileName(TEXT("res\\background.png"));
	m_pImage = Image::FromFile((LPCWSTR)strFileName);
	if(m_pImage == NULL || m_pImage->GetLastStatus() != Ok)
	{
		try
		{
			delete m_pImage;
		} catch (...)
		{
			assert(FALSE);
		}
		m_pImage = NULL;
	}
	if(NULL == m_hCheneyTabCtrl.m_hWnd)
	{
		ThinkerRect rcClient;
		GetClientRect(&rcClient);
		rcClient.DeflateRect(10, 10, 10, 10);
		m_hCheneyTabCtrl.Create(_T("TabCtrl"), WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_BORDER, rcClient, this, IDT_TABCTRL);
	}*/
	//m_hButtonEx.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_OWNERDRAW|WS_CLIPSIBLINGS, ThinkerRect(300, 200, 369, 224), this, 10008);
	//m_hButtonEx.SetImage(IDB_BTNBITMAP2);
	//m_hButtonEx.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, ThinkerRect(300, 100, 351, 140), this, 10007);
	//m_hButtonEx.SetImage(IDB_BTNBITMAP2);
	//CreateCheneyButton();
	//CreateCheneyGraphCtrl();
	//CreateCheneyNumberClock();
	//CreateCommonCtrl();
	//UpdateIcon();
	//CreateMenu();
	//CreateDlg();
	//CreateCheneyLogListCtrl();
	//g_hCheneyThreadLog.Start();
	//AnimateEnter();
	//FlashWindow(10, 1000);
	//InitializationSAPI();
	m_hBitmap = (HBITMAP)LoadImage(NULL, "res\\Kitty.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (m_hBitmap == NULL)
	{
		MessageBox(NULL, "位图加载失败", "Error", MB_ICONERROR);
		return 0;
	}
	
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_TOPMOST | WS_EX_LAYERED);
	SetWindowLong(m_hWnd, GWL_STYLE, (GetWindowLong(m_hWnd, GWL_STYLE) & 0X0000) | WS_POPUP);
	int iWidth;
	int iHeight;
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	iWidth = rc.right - rc.left;
	iHeight = rc.bottom - rc.top;
	RECT rect;
	rect.left = rect.top = 0;
	rect.right = iWidth;
	rect.bottom = (3*iHeight)>>1;
	RepaintWindow(this, rect);
	COLORREF clTransparent = RGB(0, 0, 0);
	SetLayeredWindowAttributes(m_hWnd, clTransparent, 0, LWA_COLORKEY);
	
	HDC hdc = GetDC(m_hWnd);
	s_hdcMem = CreateCompatibleDC(hdc);
	SelectObject(s_hdcMem, m_hBitmap);
	HDC hdcTemp = CreateCompatibleDC(hdc);
	HBITMAP hbmp = CreateCompatibleBitmap(hdc, iWidth, (3*iHeight)>>1);
	SelectObject(hdcTemp, hbmp);
	BITMAP bm;
	GetObject(m_hBitmap, sizeof(bm), &bm);
	StretchBlt(hdcTemp, 0, 0, iWidth, (3*iHeight)>>1, s_hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	DeleteDC(s_hdcMem);
	s_hdcMem = hdcTemp;
	ReleaseDC(m_hWnd, hdc);
	/*int iWidth;
	int iHeight;
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	iWidth = rc.right - rc.left;
	iHeight = rc.bottom - rc.top;

	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	COLORREF clTransparent = RGB(0, 0, 0);
	SetLayeredWindowAttributes(m_hWnd, clTransparent, 0, LWA_COLORKEY);
	
	HDC hdc = GetDC(m_hWnd);
	s_hdcMem = CreateCompatibleDC(hdc);
	HDC hdcTemp = CreateCompatibleDC(hdc);
	HBITMAP hbmp = CreateCompatibleBitmap(hdc, iWidth, iHeight);
	ReleaseDC(m_hWnd, hdc);
	SelectObject(s_hdcMem, hbmp);
	SelectObject(hdcTemp, m_hBitmap);
	BITMAP bm;
	GetObject(m_hBitmap, sizeof(bm), &bm);
	StretchBlt(s_hdcMem, 0, 0, iWidth, iHeight, hdcTemp, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	DeleteDC(hdcTemp);
	DeleteObject(hbmp);*/
	/*BITMAP bm;
	GetObject(m_hBitmap, sizeof(bm), &bm);
	RECT rect;
	rect.left = rect.top = 0;
	rect.right = bm.bmWidth;
	rect.bottom = bm.bmHeight + 100;
	RepaintWindow(this, rect);
	
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	COLORREF clTransparent = RGB(0, 0, 0);
	SetLayeredWindowAttributes(m_hWnd, clTransparent, 0, LWA_COLORKEY);
	HDC hdc = GetDC(m_hWnd);
	HDC hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, m_hBitmap);

	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	s_hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmp = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
	SelectObject(s_hdcMem, hbmp);
	StretchBlt(s_hdcMem, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hdcTemp, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	::DeleteDC(hdcTemp);
	ReleaseDC(m_hWnd, hdc);*/
	return TRUE;
})/*
MESSAGE_MAP_HANDLER(CheneyMainFrame, Notify, {
	if((INT)wParam == IDT_TABCTRL)
		if(((LPNMHDR)lParam)->code == TCN_SELCHANGE)
			m_hCheneyTabCtrl.ShowItem(m_hCheneyTabCtrl.GetCurSel());
	return CheneyWnd::OnNotify(wParam, lParam);
})*/
MESSAGE_MAP_HANDLER(CheneyMainFrame, KeyDown, {
	switch (wParam)
	{
	case VK_ESCAPE:
		SendMessage(m_hWnd, WM_DESTROY, 0, 0);
		return 0;
	}
	return CheneyWnd::OnKeyDown(wParam, lParam);
})
MESSAGE_MAP_HANDLER(CheneyMainFrame, EraseBkgnd, {
	HDC hdc = (HDC)wParam;
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, s_hdcMem, 0, 0, SRCCOPY);
	/*if(m_hBitmap)
	{
		HDC hdc = GetDC(m_hWnd);
		HDC dcCompatibleDC = CreateCompatibleDC(hdc);
		//选择一个对象到设备上下文
		HBITMAP hdcOld = (HBITMAP)SelectObject(dcCompatibleDC, m_hBitmap);
		RECT rect = {0};
		::GetClientRect(m_hWnd, &rect);
		//复制一个位图从源设备上下文当前设备上下文
		BitBlt(hdc,0,0,rect.right,rect.bottom,dcCompatibleDC,0,0,SRCCOPY);
		//将源矩形中的位图拷贝到目标矩形，必要时拉伸或压缩位图以适合目标矩形的尺寸。
		//StretchBlt(hdc,0,0,rect.right,rect.bottom,dcCompatibleDC,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
		SelectObject(dcCompatibleDC,hdcOld);
		DeleteDC(dcCompatibleDC);
	}*/
	return TRUE;
})
/*
BOOL CheneyMainFrame::DestroySAPI()
{
	if (pVoice)
		pVoice->Release();
	::CoUninitialize();
	return TRUE;
}

BOOL CheneyMainFrame::InitializationSAPI()
{
	if (FAILED(CoInitialize(NULL)))
		return FALSE;
	HRESULT hRes;
	hRes = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (FAILED(hRes))
		return FALSE;
	hRes = pVoice->SetInterest(SPFEI(SPEI_VISEME), SPFEI(SPEI_VISEME));
	if (FAILED(hRes))
		return FALSE;
	return TRUE;
}

void CheneyMainFrame::DrawViewImage(HDC hdc, CImage& bitImage, BYTE cbDrawMode)
{
	ThinkerRect rcClient;
	::GetClientRect(m_hWnd, &rcClient);
	RECT rcDirty = {0};
	GetClipBox(hdc, &rcDirty);
	switch(cbDrawMode)
	{
	case DRAW_MODE_SPREAD:
		{
			INT nImageWidth = bitImage.GetWidth();
			INT nImageHeight = bitImage.GetHeight();
			for(INT nXPos = 0; nXPos < rcClient.right; nXPos += nImageWidth)
			{
				for(INT nYPos = 0; nYPos < rcClient.bottom; nYPos += nImageHeight)
				{
					bitImage.BitBlt(hdc, nXPos, nYPos);
				}
			}
		}
		break;
	case DRAW_MODE_CENTENT:
		{
			INT nImageWidth = bitImage.GetWidth();
			INT nImageHeight = bitImage.GetHeight();
			INT nXPos = (rcClient.Width() - bitImage.GetWidth()) >> 1;
			INT nYPos = (rcClient.Height() - bitImage.GetHeight()) >> 1;
			bitImage.BitBlt(hdc, nXPos, nYPos);
		}
		break;
	case DRAW_MODE_ELONGGATE:
		{
			INT nImageWidth = bitImage.GetWidth();
			INT nImageHeight = bitImage.GetHeight();
			bitImage.StretchBlt(hdc,0,0,rcClient.Width(),rcClient.Height(),0,0,nImageWidth,nImageHeight);
		}
		break;
	}
}

BOOL CheneyMainFrame::DrawImagePng( HDC hdc, INT nXPos, INT nYPos)
{
	assert(m_pImage != NULL);
	if (m_pImage == NULL)
		return FALSE;
	assert(hdc != NULL);
	Graphics graphics(hdc);
	INT nImageWidth = m_pImage->GetWidth();
	INT nImageHeight=m_pImage->GetHeight();
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXPos;
	rcDrawRect.Y=(REAL)nYPos;
	rcDrawRect.Width=(REAL)nImageWidth;
	rcDrawRect.Height=(REAL)nImageHeight;
	graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)nImageWidth,(REAL)nImageHeight,UnitPixel);  
	return TRUE;
}
*/
MESSAGE_MAP_HANDLER(CheneyMainFrame, DropFiles, {
	HDROP hDrop = (HDROP)wParam;
	UINT nFileNum = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
	char strFileName[MAX_PATH];
	DragQueryFile(hDrop, 0, strFileName, MAX_PATH);
	DragFinish(hDrop);
	m_hCheneyImage.Load(m_hWnd, strFileName);
	InvalidateRect(m_hWnd, NULL, TRUE);
	return 0;
})
MESSAGE_MAP_HANDLER(CheneyMainFrame, Command, {
	int wmId = LOWORD(wParam);
	int wmEvent = HIWORD(wParam);
	HandlerMenu(wParam);
	if (wmId >= IDC_MENU_STAGGEREDHORIZONTAL && wmId <= IDC_MENU_FADE_RIGHTTOLEFT)
	{
		m_iShowID = wmId - IDC_MENU_START;
		InvalidateRect(m_hWnd, NULL, TRUE);
		return 0;
	}
	/*UINT idButton = (int) LOWORD(wParam);
	WORD wNotifyCode = HIWORD(wParam);
	HWND hWnd = (HWND) lParam;
	switch(wNotifyCode)
	{
	case BN_CLICKED:
		{
			if(idButton == GetDlgCtrlID(m_hButton.m_hWnd))
			{
				DWORD dwState = (DWORD)::SendMessage(m_hButton.m_hWnd, BM_GETCHECK, 0, 0);
				if(dwState == BST_CHECKED)
				{
					m_hButton.SetCheck(BST_UNCHECKED);
					//SendMessage(m_hButton.m_hWnd, BM_SETCHECK, BST_UNCHECKED, 0);
				}
				else
				{
					m_hButton.SetCheck(BST_CHECKED);
					//SendMessage(m_hButton.m_hWnd, BM_SETCHECK, BST_CHECKED, 0);
				}
			}
			if(idButton == GetDlgCtrlID(m_hButtonEx.m_hWnd))
			{
				DWORD dwState = (DWORD)::SendMessage(m_hButtonEx.m_hWnd, BM_GETCHECK, 0, 0);
				if(dwState == BST_CHECKED)
				{
					m_hButtonEx.SetCheck(BST_UNCHECKED);
					//SendMessage(m_hButton.m_hWnd, BM_SETCHECK, BST_UNCHECKED, 0);
				}
				else
				{
					m_hButtonEx.SetCheck(BST_CHECKED);
					//SendMessage(m_hButton.m_hWnd, BM_SETCHECK, BST_CHECKED, 0);
				}
			}
		}
		break;
	}*/
	return CheneyWnd::OnCommand(wParam, lParam);
})

MESSAGE_MAP_HANDLER(CheneyMainFrame, Paint, {
	m_hCheneyImage.Show(m_hWnd, m_iShowID);
	/*{
		if(m_ImageBmp)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(m_hWnd, &ps);
			DrawViewImage(hdc, m_ImageBmp, DRAW_MODE_CENTENT);
			DrawImagePng(hdc, 0, 0);
			EndPaint(m_hWnd, &ps);
		}
	}*/
	/*{
		if(m_hBitmap)
		{
			PAINTSTRUCT ps;
			HDC hdc = ::BeginPaint(m_hWnd, &ps);
			HDC dcCompatibleDC = CreateCompatibleDC(hdc);
			HBITMAP hdcOld = (HBITMAP) SelectObject(dcCompatibleDC, m_hBitmap);
			RECT rect = {0};
			::GetClientRect(m_hWnd, &rect);
			//复制一个位图从源设备上下文当前设备上下文
			BitBlt(hdc, 0, 0,rect.right,rect.bottom,dcCompatibleDC,0,0,SRCCOPY);
			//将源矩形中的位图拷贝到目标矩形，必要时拉伸或压缩位图以适合目标矩形的尺寸。
			//StretchBlt(hdc,0,0,rect.right,rect.bottom,dcCompatibleDC,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
			SelectObject(dcCompatibleDC, hdcOld);
			::DeleteDC(dcCompatibleDC);
			EndPaint(m_hWnd, &ps);
		}
	}*/
	//HandlerOne(m_hWnd);
	//HandlerTwo(m_hWnd);
	//HandlerThree(m_hWnd);
	//HandlerFour(m_hWnd, m_hCheneyNumberClock);
	return CheneyWnd::OnPaint(wParam, lParam);
})

MESSAGE_MAP_HANDLER(CheneyMainFrame, Size, {
	//m_hCheneyNumberClock.cxClient = LOWORD(lParam);
	//m_hCheneyNumberClock.cyClient = HIWORD(lParam);
	//ThinkerRect rcClient = GetClientRect();
	//RepaintWindow(&m_hCheneyGraphCtrl, rcClient);
	/*rcClient.DeflateRect(10, 10, 10, 10);
	RepaintWindow(&m_hCheneyLogListCtrl, rcClient);*/
	/*RepaintWindow(&m_hCheneyTabCtrl, rcClient);
	return CheneyWnd::OnSize(wParam, lParam);*/
	InvalidateRect(m_hWnd, NULL, TRUE);
	return TRUE;
})
/*
MESSAGE_MAP_HANDLER(CheneyMainFrame, ContextMenu, {
	ThinkerPoint pt;
	GetCursorPos(&pt);
	HMENU hSubMenu1 = CreatePopupMenu();
	AppendMenu(hSubMenu1, MF_BYCOMMAND | MF_STRING, ID_OPEN_FILE, _T("打开文件"));
	AppendMenu(hSubMenu1, MF_SEPARATOR, 0, _T(""));
	AppendMenu(hSubMenu1, MF_BYCOMMAND | MF_STRING, ID_SAVE_FILE, _T("保存文件"));
	TrackPopupMenu(hSubMenu1, TPM_LEFTALIGN|TPM_TOPALIGN, pt.x, pt.y, 0, m_hWnd, NULL);
	return CheneyWnd::OnContextMenu(wParam, lParam);
})

/*
LRESULT CheneyMainFrame::OnDrawItem(WPARAM wParam, LPARAM lParam)
{
	UINT idCtl = (UINT) wParam;
	LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam;
	HWND hWndItem = lpdis->hwndItem;
	assert(hWndItem);
	if(lpdis->CtlType == ODT_BUTTON)
	{
		CheneyButton* pButton = (CheneyButton*)CheneyWnd::FromHandle(hWndItem);
		if(pButton)
		{
			//pButton->DrawItem(lpdis);
		}
	}
	return TRUE;
}

LRESULT CheneyMainFrame::OnNotify(WPARAM wParam, LPARAM lParam)
{
	UINT idCtrl = (int) wParam;
	NM_TREEVIEW* pNmtv = (NM_TREEVIEW*) lParam;
	int nCode = pNmtv->hdr.code;
	switch(nCode)
	{
	case TVN_SELCHANGED:
	{
		if(pNmtv->hdr.hwndFrom == m_hTreeCtrl.m_hWnd)
		{
			HTREEITEM hItemNew = pNmtv->itemNew.hItem;
			TCHAR pszText[1024];
			TVITEM tvi;
			tvi.mask = TVIF_TEXT | TVIF_HANDLE;
			tvi.hItem = hItemNew;
			tvi.pszText = pszText;
			tvi.cchTextMax = 1024;
			::SendMessage(m_hTreeCtrl.m_hWnd, TVM_GETITEM, 0, (LPARAM)&tvi);
			MessageBox(NULL, pszText, _T(""), 0);
		}
	}
	break;
	}
	return CheneyWnd::OnNotify(wParam, lParam);
}
*/

/*LRESULT CheneyMainFrame::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	SetCapture(m_hWnd);
	m_bStart = TRUE;
	m_hCheneyShape.clear();
	m_ptOrigin.x = LOWORD(lParam); 
	m_ptOrigin.y = HIWORD(lParam);
	m_hCheneyShape.push_back(m_ptOrigin);
	return CheneyWnd::OnLButtonDown(wParam, lParam);
}

LRESULT CheneyMainFrame::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	ThinkerPoint pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	if(m_bStart)
	{
		HDC hdc = ::GetDC(m_hWnd);
		assert(hdc);
		{
			MoveToEx(hdc, m_ptOrigin.x, m_ptOrigin.y, NULL);
			LineTo(hdc, pt.x, pt.y);
			m_ptOrigin = pt;
		}
		::ReleaseDC(m_hWnd, hdc);
		m_hCheneyShape.push_back(pt);
	}
	return CheneyWnd::OnMouseMove(wParam, lParam);
}

LRESULT CheneyMainFrame::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	ReleaseCapture();
	m_bStart = FALSE;
	g_hCheneyGraph.AddCheneyShape(m_hCheneyShape);
	return CheneyWnd::OnLButtonUp(wParam, lParam);
}

LRESULT CheneyMainFrame::OnWinIniChange(WPARAM wParam, LPARAM lParam)
{
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ITIME, m_hCheneyNumberClock.szBuffer, 2);
	m_hCheneyNumberClock.f24Hour = (m_hCheneyNumberClock.szBuffer[0] == '1');
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ITLZERO, m_hCheneyNumberClock.szBuffer, 2);
	m_hCheneyNumberClock.fSuppress = (m_hCheneyNumberClock.szBuffer[0] == '0');
	InvalidateRect(m_hWnd, NULL, TRUE);
	return CheneyWnd::OnWinIniChange(wParam, lParam);
}

LRESULT CheneyMainFrame::OnTimer(WPARAM wParam, LPARAM lParam)
{
	InvalidateRect(m_hWnd, NULL, TRUE);
	HandlerIcon(wParam);
	return CheneyWnd::OnTimer(wParam, lParam);
}*/
/*
void CheneyMainFrame::CreateCheneyLogListCtrl()
{
	if(NULL == m_hCheneyLogListCtrl.m_hWnd)
	{
		ThinkerRect rcClient;
		GetClientRect(&rcClient);
		rcClient.DeflateRect(10, 10, 10, 10);
		m_hCheneyLogListCtrl.Create(_T("ListCtrl"), LVS_REPORT | WS_CHILD | WS_VISIBLE | WS_BORDER, rcClient, this, IDL_LISTCTRL);
	}
}

void CheneyMainFrame::CreateDlg()
{
	HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
	assert(hInstance);
	HWND hDlg = ::CreateDialog(hInstance, MAKEINTRESOURCE(IDD_ABOUT_DLG), m_hWnd, DialogProc2);
}
*/
void CheneyMainFrame::CreateMenu()
{
	HMENU hMenu = (HMENU)::LoadMenu((HINSTANCE)::GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
	//HMENU hMenu = CreateMenu();
	//HMENU hSubMenu1 = CreatePopupMenu();
	//AppendMenu(hSubMenu1, MF_BYCOMMAND | MF_STRING, ID_OPEN_FILE, _T("打开文件"));
	//AppendMenu(hSubMenu1, MF_SEPARATOR, 0, _T(""));
	//AppendMenu(hSubMenu1, MF_BYCOMMAND | MF_STRING, ID_SAVE_FILE, _T("保存文件"));
	//AppendMenu(hMenu, MF_POPUP | MF_STRING, (UINT)hSubMenu1, _T("文件"));
	//HMENU hSubMenu1 = GetSystemMenu(m_hWnd, FALSE);
	//HMENU hMenu = CreateMenu();
	//AppendMenu(hMenu, MF_POPUP | MF_STRING, (UINT)hSubMenu1, _T("文件"));
	SetMenu(m_hWnd, hMenu);
}

void CheneyMainFrame::HandlerMenu(WPARAM wParam)
{
	WORD wNitofyCode = HIWORD(wParam);
	WORD wID = LOWORD(wParam);
	if(wNitofyCode == 0)
	{
		switch(wID)
		{
			case ID_OPEN_FILE:
				{
					m_hCheneyDialog.CreateCheneyDialog(m_hWnd);
				}
				break;
			case ID_ABOUT:
				{
					//m_hCheneyAnimateWnd.AnimateWindow(400, FALSE);
					//SendMessage(m_hWnd, WM_DESTROY, 0, 0);
					//return;
					m_hCheneyDialog.CreateCheneyDialog(m_hWnd);
				}
				break;
		}
		/*switch(wID)
		{
		case ID_OPEN_FILE:
			{
				TCHAR lpszFilePath[MAX_PATH]={};
				TCHAR lpszFileName[MAX_PATH]={};
				OPENFILENAME ofn;
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = m_hWnd;
				ofn.hInstance = (HINSTANCE)::GetModuleHandle(NULL);
				ofn.lpstrFilter = _T("THINKER Files(*.thinker)\0\0");
				ofn.lpstrCustomFilter = NULL;
				ofn.nMaxCustFilter = 0;
				ofn.nFilterIndex = 0;
				ofn.lpstrFile = lpszFilePath;
				ofn.nMaxFile = MAX_PATH;
				ofn.lpstrFileTitle = lpszFileName;
				ofn.nMaxFileTitle = MAX_PATH;
				ofn.lpstrInitialDir = NULL;
				ofn.lpstrTitle = NULL;
				ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
				ofn.nFileOffset = 0;
				ofn.nFileExtension = 0;
				ofn.lpstrDefExt = _T("thinker");
				ofn.lCustData = 0;
				ofn.lpfnHook = NULL;
				ofn.lpTemplateName = NULL;
				int nRet = GetOpenFileName(&ofn);
				if(nRet!=0)
				{
					g_hCheneyGraph.GetCheneyGraphFromFile(lpszFilePath);
					InvalidateRect(m_hWnd, NULL, TRUE);
				}
			}
			break;
		case ID_SAVE_FILE:
			{
				TCHAR lpszFilePath[MAX_PATH]={};
				TCHAR lpszFileName[MAX_PATH]={};
				OPENFILENAME ofn;
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = m_hWnd;
				ofn.hInstance = (HINSTANCE)::GetModuleHandle(NULL);
				ofn.lpstrFilter = _T("THINKER Files(*.thinker)\0\0");
				ofn.lpstrCustomFilter = NULL;
				ofn.nMaxCustFilter = 0;
				ofn.nFilterIndex = 0;
				ofn.lpstrFile = lpszFilePath;
				ofn.nMaxFile = MAX_PATH;
				ofn.lpstrFileTitle = lpszFileName;
				ofn.nMaxFileTitle = MAX_PATH;
				ofn.lpstrInitialDir = NULL;
				ofn.lpstrTitle = NULL;
				ofn.Flags = OFN_OVERWRITEPROMPT;
				ofn.nFileOffset = 0;
				ofn.nFileExtension = 0;
				ofn.lpstrDefExt = _T("thinker");
				ofn.lCustData = 0;
				ofn.lpfnHook = NULL;
				ofn.lpTemplateName = NULL;
				int nRet = GetSaveFileName(&ofn);
				if(nRet!=0)
				{
					g_hCheneyGraph.SaveCheneyGraphToFile(lpszFilePath);
				}
			}
			break;
		case ID_ABOUT:
			{
				pVoice->Speak((LPCWSTR)TEXT("abcdefghijklmnopqrstuvwxyz"), NULL, NULL);
				HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
				assert(hInstance);
				int nRes = ::DialogBox(hInstance, MAKEINTRESOURCE(IDD_PANEL_DLG), m_hWnd, DialogProc);
				if(nRes == IDCANCEL)
				{
				}
			}
			break;
		}*/
	}
}
/*
void CheneyMainFrame::HandlerIcon(WPARAM wParam)
{
	WORD wTimerID = wParam;
	if(wTimerID == 1)
	{
		static int nCount = 0;
		HICON hIcon;
		// 修改应用程序锁关联的图标
		if(nCount%3==0)
			hIcon = (HICON)::LoadIcon((HINSTANCE)::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_UP));
		if(nCount%3==1)
			hIcon = (HICON)::LoadIcon((HINSTANCE)::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_RIGHT));
		if(nCount%3==2)
			hIcon = (HICON)::LoadIcon((HINSTANCE)::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DN));
		SetClassLong(m_hWnd, GCL_HICON, (DWORD)hIcon);
		SetClassLong(m_hWnd, GCL_HICONSM, (DWORD)hIcon);
		SendMessage(m_hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		SendMessage(m_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		nCount++;
	}
}

void CheneyMainFrame::UpdateIcon()
{
	SetTimer(m_hWnd, 1, 500, NULL);
	HICON hIcon = (HICON)::LoadIcon((HINSTANCE)::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_UP));
	SetClassLong(m_hWnd, GCL_HICON, (DWORD)hIcon);
	SetClassLong(m_hWnd, GCL_HICONSM, (DWORD)hIcon);
}

void CheneyMainFrame::CreateCheneyButton()
{
	if(NULL == m_hCheneyButton.m_hWnd)
		m_hCheneyButton.Create(_T("CheneyThinker"), WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, ThinkerRect(0, 180, 150, 220), this, IDB_BUTTON);
}

void CheneyMainFrame::CreateCheneyGraphCtrl()
{
	if(NULL == m_hCheneyGraphCtrl.m_hWnd)
	{
		ThinkerRect rcClient;
		GetClientRect(rcClient);
		m_hCheneyGraphCtrl.Create(_T(""), WS_CHILD | WS_VISIBLE, rcClient, this, IDC_GRAGHCTRL);
		{
			CheneyGraphCtrlUnit gragh;
			gragh.SetTitle(_T("正弦曲线"));
			gragh.SetColor(0x0000FF);
			for(int i=-10000; i<10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (1000 * sin(2 * 3.1415926 * i / 1000.0f));
				gragh.AddData((int) fX, (int) fY);
			}
			m_hCheneyGraphCtrl.AddGraphCtrlUnit(gragh);
		}
		{
			CheneyGraphCtrlUnit gragh;
			gragh.SetTitle(_T("混合曲线"));
			gragh.SetColor(0x00FF00);
			for(int i=-10000; i<10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (1000 * sin(2 * 3.1415926 * i / 1000.0f) + 500 * cos( 3.1415926 * i / 80.0f));
				gragh.AddData((int) fX, (int) fY);
			}
			m_hCheneyGraphCtrl.AddGraphCtrlUnit(gragh);
		}
		{
			CheneyGraphCtrlUnit gragh;
			gragh.SetTitle(_T("圆曲线"));
			gragh.SetColor(0xFF0000);
			for(int i=-10000; i<10000; i++)
			{
				float fX = (float) (1000 * cos(2 * 3.1415926 * i / 1000.0f));
				float fY = (float) (1000 * sin(2 * 3.1415926 * i / 1000.0f));
				gragh.AddData((int) fX, (int) fY);
			}
			m_hCheneyGraphCtrl.AddGraphCtrlUnit(gragh);
		}
		{
			CheneyGraphCtrlUnit gragh;
			gragh.SetTitle(_T("混合曲线"));
			gragh.SetColor(0x00FFFF);
			for(int i=-10000; i<10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (1000 * sin( 2 * 3.1415926 * i / 1000.0f) * cos(3.1415926 * i / 99.0f) + 1000);
				gragh.AddData((int) fX, (int) fY);
			}
			m_hCheneyGraphCtrl.AddGraphCtrlUnit(gragh);
		}
		{
			CheneyGraphCtrlUnit gragh;
			gragh.SetTitle(_T("混合曲线"));
			gragh.SetColor(0xFFFF00);
			for(int i=-10000; i<10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (100000 * 1.0f / i);
				gragh.AddData((int) fX, (int) fY);
			}
			m_hCheneyGraphCtrl.AddGraphCtrlUnit(gragh);
		}
		{
			CheneyGraphCtrlUnit gragh;
			gragh.SetTitle(_T("混合曲线"));
			gragh.SetColor(0xFF00FF);
			for(int i=-10000; i<10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (0.0001 * i * i);
				gragh.AddData((int) fX, (int) fY);
			}
			m_hCheneyGraphCtrl.AddGraphCtrlUnit(gragh);
		}
	}
}

void CheneyMainFrame::CreateCheneyNumberClock()
{
	SetTimer(m_hWnd, IDT_TIMER, 1000, NULL);
}

void CheneyMainFrame::CreateCommonCtrl()
{
	m_hButton.Create(_T("BUTTON"), WS_CHILD|WS_VISIBLE|WS_BORDER|BS_CHECKBOX, ThinkerRect(300, 0, 400, 50), this, 10001);
	//SendMessage(m_hButton.m_hWnd, BM_SETCHECK, BST_CHECKED, 0);
	m_hButtonEx.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, ThinkerRect(300, 100, 351, 140), this, 10007);
	m_hButtonEx.SetImage(IDB_BTNBITMAP);
	m_hButtonEx2.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_OWNERDRAW|WS_CLIPSIBLINGS, ThinkerRect(300, 200, 369, 224), this, 10008);
	m_hButtonEx2.SetImage(IDB_BTNBITMAP2);

	m_hEdit.CreateEx(0, _T("EDIT"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE|WS_VSCROLL|ES_AUTOVSCROLL, 300, 230, 100, 50, m_hWnd, (HMENU)10002);
	SendMessage(m_hEdit.m_hWnd, WM_SETTEXT, 0, (LPARAM)(_T("www.itxueba.org")));
	
	m_hListBox.CreateEx(0, _T("LISTBOX"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|LBS_HASSTRINGS, 300, 300, 100, 50, m_hWnd, (HMENU)10003);
	SendMessage(m_hListBox.m_hWnd, LB_ADDSTRING, 0, (LPARAM)(_T("www.itxueba.org")));
	SendMessage(m_hListBox.m_hWnd, LB_ADDSTRING, 0, (LPARAM)(_T("xiaojinyu")));
	
	m_hScrollBar.CreateEx(0, _T("SCROLLBAR"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|SBS_HORZ , 300, 360, 200, 20, m_hWnd, (HMENU)10004);
	m_hStatic.CreateEx(0, _T("STATIC"), _T(""), WS_CHILD|WS_VISIBLE, 300, 390, 100, 50, m_hWnd, (HMENU)10005);
	
	m_hTreeCtrl.CreateEx(0, WC_TREEVIEW, _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT, 300, 500, 200, 200, m_hWnd, (HMENU)10006);
	TV_INSERTSTRUCT tvis;
	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item.mask = TVIF_TEXT | TVIF_STATE;
	tvis.item.pszText = _T("Windows 程序设计");
	tvis.item.cchTextMax = sizeof(_T("Windows 程序设计"));
	tvis.item.state = TVIS_EXPANDED;
	tvis.item.stateMask = TVIS_EXPANDED;
	HTREEITEM hTreeRoot = (HTREEITEM)::SendMessage(m_hTreeCtrl.m_hWnd, TVM_INSERTITEM, 0, (LPARAM)(&tvis));
	for(int i=1; i<=20; i++)
	{
		tvis.hParent = hTreeRoot;
		CString str;
		str.Format(_T("第%d讲"),  i);
		tvis.item.pszText = str.GetBuffer(0);
		tvis.item.cchTextMax = str.GetLength();
		SendMessage(m_hTreeCtrl.m_hWnd, TVM_INSERTITEM, 0, (LPARAM)(&tvis));
	}
}

BOOL CALLBACK DialogProc2(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwndDlg, message, wParam, lParam);
}
*/