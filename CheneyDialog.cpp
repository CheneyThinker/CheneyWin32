#include "CheneyDialog.h"

SPECIAL_HANDLER(CheneyDialog, {}, {})
	
int CheneyDialog::CreateCheneyDialog(HWND hwnd)
{
	//HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
	assert(hInstance);
	return ::DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int INIT_TRANSPARENT = 200; //�����ʼ͸����
	static HBRUSH    s_hBitmapBrush; //λͼ��ˢ
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hDlg, TEXT("���öԻ������"));
		HBITMAP hBitmap;
		hBitmap = (HBITMAP)LoadImage(NULL, "res\\107.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (hBitmap == NULL)
		{
			MessageBox(hDlg, "LoadImage failed", "Error", MB_ICONERROR);
			exit(0);
		}
		s_hBitmapBrush = CreatePatternBrush(hBitmap);
		SetWindowLong(hDlg, GWL_EXSTYLE, GetWindowLong(hDlg, GWL_EXSTYLE) | WS_EX_LAYERED);
		//SetLayeredWindowAttributes(hDlg, 0, INIT_TRANSPARENT, LWA_ALPHA);
		SetLayeredWindowAttributes(hDlg, RGB(255, 244, 0), 0, LWA_COLORKEY);
		SendMessage(GetDlgItem(hDlg, IDC_SLIDER_TRANSPARENT), TBM_SETRANGE, (WPARAM)FALSE, MAKELONG(0, 255));
		SendMessage(GetDlgItem(hDlg, IDC_SLIDER_TRANSPARENT), TBM_SETPOS, (WPARAM)TRUE, INIT_TRANSPARENT);

		//SendMessage(GetDlgItem(hDlg, IDC_SLIDER_VTRANSPARENT), TBM_SETRANGE, (WPARAM)FALSE, MAKELONG(0, 255));
		//SendMessage(GetDlgItem(hDlg, IDC_SLIDER_VTRANSPARENT), TBM_SETPOS, (WPARAM)TRUE, INIT_TRANSPARENT);
		
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			DeleteObject(s_hBitmapBrush);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	case WM_HSCROLL: // slider control ����λ���б仯ʱ����Ӧ����
		{
			// ��ȡ��ǰ����λ��
			int nTransparent = SendMessage(GetDlgItem(hDlg, IDC_SLIDER_TRANSPARENT), TBM_GETPOS, 0, 0);
			// ������͸����
			//SetLayeredWindowAttributes(hDlg, 0, nTransparent, LWA_ALPHA);
			SetLayeredWindowAttributes(hDlg, RGB(255, 0, 0), nTransparent, LWA_ALPHA | LWA_COLORKEY);
		}
		break;
	case WM_VSCROLL: // slider control ����λ���б仯ʱ����Ӧ����
		{
			// ��ȡ��ǰ����λ��
			int nTransparent = SendMessage(GetDlgItem(hDlg, IDC_SLIDER_VTRANSPARENT), TBM_GETPOS, 0, 0);
			// ������͸����
			//SetLayeredWindowAttributes(hDlg, 0, nTransparent, LWA_ALPHA);
			SetLayeredWindowAttributes(hDlg, RGB(255, 0, 0), nTransparent, LWA_ALPHA | LWA_COLORKEY);
		}
		break;
	case WM_CTLCOLORDLG:  //�Ի���Ӱ
		return (BOOL)s_hBitmapBrush;
	}
	return FALSE;
	/*RECT       rcDialog;
	HBITMAP    hBitmap;
	static BITMAP s_bm;
	static HDC    s_hdcMem;
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hDlg, "���öԻ������");
		SetWindowLong(hDlg, GWL_STYLE, GetWindowLong(hDlg, GWL_STYLE) | WS_SIZEBOX);
		hBitmap = (HBITMAP)LoadImage(NULL, "res\\208.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (hBitmap == NULL)
		{
			MessageBox(hDlg, "LoadImage failed", "Error", MB_ICONERROR);
			exit(0);
		}		
		else
		{
			HDC        hdc;
			hdc = GetDC(hDlg);
			s_hdcMem = CreateCompatibleDC(hdc);
			SelectObject(s_hdcMem, hBitmap);	
			ReleaseDC(hDlg, hdc);
			GetObject(hBitmap, sizeof(s_bm), &s_bm);
		}
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			DeleteDC(s_hdcMem);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	case WM_SIZE:
		InvalidateRect(hDlg, NULL, TRUE);
		return TRUE;
 	case WM_CTLCOLORSTATIC:
 		SetBkMode((HDC)wParam, TRANSPARENT);
 		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	case WM_CTLCOLORDLG:
		GetClientRect(hDlg, &rcDialog);
		//ͨ��SetStretchBltMode��������ʹStretchBlt������ͼ���������
		SetStretchBltMode((HDC)wParam, COLORONCOLOR);
		StretchBlt((HDC)wParam, 0, 0, rcDialog.right, rcDialog.bottom, s_hdcMem, 0, 0, s_bm.bmWidth, s_bm.bmHeight, SRCCOPY);	
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	}
	return FALSE;*/
	/*
	RECT       rcDialog;
	HBITMAP    hBitmap;
	static BITMAP s_bm;
	static HDC    s_hdcMem;
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hDlg, "���öԻ������");
		SetWindowLong(hDlg, GWL_STYLE, GetWindowLong(hDlg, GWL_STYLE) | WS_SIZEBOX);
		hBitmap = (HBITMAP)LoadImage(NULL, "res\\207.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (hBitmap == NULL)
		{
			MessageBox(hDlg, "LoadImage failed", "Error", MB_ICONERROR);
			exit(0);
		}		
		else
		{
			HDC        hdc;
			hdc = GetDC(hDlg);
			s_hdcMem = CreateCompatibleDC(hdc);
			SelectObject(s_hdcMem, hBitmap);	
			ReleaseDC(hDlg, hdc);
			GetObject(hBitmap, sizeof(s_bm), &s_bm);
		}
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			DeleteDC(s_hdcMem);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	case WM_SIZE:
		InvalidateRect(hDlg, NULL, TRUE);
		return TRUE;
	case WM_CTLCOLORDLG:
		GetClientRect(hDlg, &rcDialog);
		//ͨ��SetStretchBltMode��������ʹStretchBlt������ͼ���������
		SetStretchBltMode((HDC)wParam, COLORONCOLOR);
		StretchBlt((HDC)wParam, 0, 0, rcDialog.right, rcDialog.bottom, s_hdcMem, 0, 0, s_bm.bmWidth, s_bm.bmHeight, SRCCOPY);	
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	}
	return FALSE;*/
	/*static HBRUSH s_hBitmapBrush;
	switch (message)
	{
	case WM_INITDIALOG:
		// ���öԻ������
		SetWindowText(hDlg, "Dialog");
		// ���öԻ����С�ɵ���
		SetWindowLong(hDlg, GWL_STYLE, GetWindowLong(hDlg, GWL_STYLE) | WS_SIZEBOX);
		// ���ر�ӰͼƬ
		HBITMAP hBitmap;
		hBitmap = (HBITMAP)LoadImage(NULL, "res\\107.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (hBitmap == NULL)
		{
			MessageBox(hDlg, "LoadImage failed", "Error", MB_ICONERROR);
			exit(0);
		}
		// ����λͼ��ˢ
		s_hBitmapBrush = CreatePatternBrush(hBitmap);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			DeleteObject(s_hBitmapBrush);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam, TRANSPARENT);
	case WM_CTLCOLORDLG:
		return (BOOL)s_hBitmapBrush;
	}
	return FALSE;*/
	/*switch(message)
	{
	case WM_CLOSE:
		{
			::EndDialog(hwndDlg, IDCANCEL);
		}
		return TRUE;
	case WM_COMMAND:
		{
			WORD wNotifyCode = HIWORD(wParam); 
			WORD wID = LOWORD(wParam); 
			HWND hwndCtl = (HWND) lParam;
			if(wID == IDCANCEL)
			{
				SendMessage(hwndDlg, WM_CLOSE, 0, 0);
				break;
			}
			if(wID==IDOK)
			{
				HWND hEditUserName = GetDlgItem(hwndDlg, IDC_EDIT_USERNAME);
				assert(hEditUserName);
				TCHAR lpszUserName[1024];
				::GetWindowText(hEditUserName, lpszUserName, 1024);
				HWND hEditPassWord = GetDlgItem(hwndDlg, IDC_EDIT_PASSWORD);
				assert(hEditPassWord);
				TCHAR lpszPassWord[1024];
				::GetWindowText(hEditPassWord, lpszPassWord, 1024);	
				if(_tcscmp(lpszUserName, _T("itxueba"))==0 && _tcscmp(lpszPassWord, _T("zhengyu"))==0)
				{
					MessageBox(NULL, _T("�û���������ȷ"), _T("��ʾ"), 0);
					EndDialog(hwndDlg, IDOK);
				}
				else
				{
					MessageBox(NULL, _T("�û������������"), _T("��ʾ"), 0);
					::SetWindowText(hEditPassWord, _T(""));
				}
			}
		}
		return TRUE;
	}
	return FALSE;*/
}