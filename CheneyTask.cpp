#include "CheneyTask.h"

void HandlerOne(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hwnd, &ps);
	assert(hDC);
	{
		POINT pt;
		pt.x = 20;
		pt.y = 20;
		int nWidth = 0;
		int nHortWidth_PX = GetDeviceCaps(hDC, HORZRES);		// 返回屏幕的像素单位 1280
		int nHortWidth_MM = GetDeviceCaps(hDC, HORZSIZE);		// 返回屏幕的MM毫米单位 320mm  1 ---> 0.25mm
		int nVertWidth_PX = GetDeviceCaps(hDC, VERTRES);		// 返回屏幕的像素单位 800
		int nVertWidth_MM = GetDeviceCaps(hDC, VERTSIZE);		// 返回屏幕的MM毫米单位 200mm
		{
			/*
			MM_LOMETRIC   1个单位 0.1mm
			?(1000)	  100mm
			*/
			int nOldMap = SetMapMode(hDC, MM_LOMETRIC);
			nWidth = 1000;
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x+nWidth, pt.y);
			TextOut(hDC, pt.x+nWidth, pt.y, _T("MM_LOMETRIC"), _tcslen(_T("MM_LOMETRIC")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*
			MM_LOMETRIC   1个单位 0.01mm
			?(10000)	  100mm
			*/
			pt.x = 20;
			pt.y = 40;
			int nOldMap = SetMapMode(hDC, MM_HIMETRIC);
			nWidth = 10000;
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x+nWidth, pt.y);
			TextOut(hDC, pt.x+nWidth, pt.y, _T("MM_HIMETRIC"), _tcslen(_T("MM_HIMETRIC")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*
			MM_LOMETRIC   1个单位 0.01in (0.01*25.4)
			?(10000)	  100mm
			*/
			pt.x = 20;
			pt.y = 60;
			int nOldMap = SetMapMode(hDC, MM_LOENGLISH);
			nWidth = (int) (100 * 100 / 25.4);
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x+nWidth, pt.y);
			TextOut(hDC, pt.x+nWidth, pt.y, _T("MM_LOENGLISH"), _tcslen(_T("MM_LOENGLISH")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*
			MM_LOMETRIC   1个单位 0.001in (0.01*25.4)
			?(10000)	  100mm
			*/
			pt.x = 20;
			pt.y = 80;
			int nOldMap = SetMapMode(hDC, MM_HIENGLISH);
			nWidth = (int) (1000 * 100 / 25.4);
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x+nWidth, pt.y);
			TextOut(hDC, pt.x+nWidth, pt.y, _T("MM_HIENGLISH"), _tcslen(_T("MM_HIENGLISH")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*
			MM_LOMETRIC   1个单位 1/1440in (1/1440*25.4)
			?(10000)	  100mm
			*/
			pt.x = 20;
			pt.y = 100;
			int nOldMap = SetMapMode(hDC, MM_TWIPS);
			nWidth = (int) (1440 * 100 / 25.4);
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x+nWidth, pt.y);
			TextOut(hDC, pt.x+nWidth, pt.y, _T("MM_TWIPS"), _tcslen(_T("MM_TWIPS")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*					1280  320mm
								400	  100
			MM_ANISOTROPIC   1个单位 0.25MM
		
						?(400)	  100mm
			*/
			pt.x = 20;
			pt.y = 120;
			int nOldMap = SetMapMode(hDC, MM_ANISOTROPIC);
			SetViewportExtEx(hDC, 4, 4, NULL);//1280*800  1.25  = 1/8
			SetWindowExtEx(hDC, 1, 1, NULL);//320*200
			nWidth = 100;
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x+nWidth, pt.y);
			TextOut(hDC, pt.x+nWidth, pt.y, _T("MM_ANISOTROPIC"), _tcslen(_T("MM_ANISOTROPIC")));
			SetMapMode(hDC, nOldMap);
		}
	}
	::EndPaint(hwnd, &ps);
}

void HandlerTwo(HWND hwnd)
{
	RECT rcClient;
	GetClientRect(hwnd, &rcClient);
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(hwnd, &ps);
	assert(hDC);
	{
		// 输出位图
		HDC hMemDC = ::CreateCompatibleDC(hDC);
		assert(hMemDC);
		{
			HBITMAP hBitmap = (HBITMAP)::LoadBitmap((HINSTANCE)GetModuleHandle(NULL),  MAKEINTRESOURCE(IDB_BITMAP1));
			assert(hBitmap);
			BITMAP bm;
			GetObject((HGDIOBJ)hBitmap, sizeof(BITMAP), &bm);
			{
				HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);
				{
					for(int i=0; i<100; i++)
					{
						for(int j=0; j<100; j++)
						{
							::BitBlt(hDC, rcClient.left+bm.bmWidth*i, rcClient.top+bm.bmHeight*j, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top,
								hMemDC, 0, 0, SRCCOPY);
						}
					}
					//::StretchBlt(hDC, rcClient.left, rcClient.top, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
				}
				::SelectObject(hMemDC, hOldBitmap);
			}
			::DeleteObject((HGDIOBJ)hBitmap);
		}
		::DeleteDC(hMemDC);

		/* 
		// 双缓冲绘图模式
		HDC hMemDC = ::CreateCompatibleDC(hDC);
		assert(hMemDC);
		{
			HBITMAP hCompatibleBitmap = ::CreateCompatibleBitmap(hDC, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top);
 			assert(hCompatibleBitmap);
			{
				HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hCompatibleBitmap);
				{
					HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255,0,0));
					HPEN hOldPen = (HPEN)::SelectObject(hMemDC, (HGDIOBJ)hPen);
					{
						HBRUSH hBrush = CreateSolidBrush(RGB(0,0,255));
						HBRUSH hOldBrush = (HBRUSH)::SelectObject(hMemDC, (HGDIOBJ)hBrush);
						{
							for(int i=0; i<1280; i++)
							{
								for(int j=0; j<800; j++)
								{
									SetPixel(hMemDC, i, j, RGB(0,0,255));
								}
							}
							//::Rectangle(hMemDC, 0, 0, 100, 50);
							//::Ellipse(hDC, 0, 0, 100, 50);
						}
						::SelectObject(hMemDC, (HGDIOBJ)hOldBrush);
						DeleteObject((HGDIOBJ)hOldBrush);
					}
					::SelectObject(hMemDC, (HGDIOBJ)hOldPen);
					::DeleteObject((HGDIOBJ)hPen);

					::BitBlt(hDC, rcClient.left, rcClient.top, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top,
						hMemDC, 0, 0, SRCCOPY);
				}
				::SelectObject(hMemDC, hOldBitmap);
			}
			::DeleteObject((HGDIOBJ)hCompatibleBitmap);
		}
		::DeleteDC(hMemDC);
		*/
		
		/*
		//HPEN hPen = (HPEN)::GetStockObject(NULL_PEN);
		HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255,0,0));
		
		HPEN hOldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)hPen);
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(0,0,255));
			HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, (HGDIOBJ)hBrush);
			{
				::Rectangle(hDC, 0, 0, 100, 50);
				//::Ellipse(hDC, 0, 0, 100, 50);
			}
			::SelectObject(hDC, (HGDIOBJ)hOldBrush);
			DeleteObject((HGDIOBJ)hOldBrush);
		}
		::SelectObject(hDC, (HGDIOBJ)hOldPen);
		::DeleteObject((HGDIOBJ)hPen);
		*/
		

		/*
		HPEN hPen = CreatePen(PS_DASHDOT, 1, RGB(255,0,0));
		HPEN hOldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)hPen);
		{
			MoveToEx(hDC, 0, 0, NULL);
			LineTo(hDC, rcClient.right, rcClient.bottom);
		}
		::SelectObject(hDC, (HGDIOBJ)hOldPen);
		DeleteObject((HGDIOBJ)hPen);
		*/
		

		/*
		//输出点
		for(int i=0; i<100; i++)
		{
			for(int j=0; j<100; j++)
			{
				SetPixel(hDC, i, j, RGB(0,0,255));
			}
		}
		*/
		/*
		//DrawText(hDC, _T("www.itxueba.org"), _tcslen(_T("www.itxueba.org")), &rcClient, DT_CENTER | DT_VCENTER | DT_WORD_ELLIPSIS | DT_SINGLELINE);
		//DrawText(hDC, _T("www.itxueba.org"), _tcslen(_T("www.itxueba.org")), &rcClient, DT_LEFT|DT_TOP| DT_WORD_ELLIPSIS | DT_SINGLELINE);
		COLORREF clrOldTextColor = SetTextColor(hDC, RGB(255,0,0));
		COLORREF clrBackColor = SetBkColor(hDC, RGB(0,255,0));

		HFONT hFont = CreateFont(
			200						// nHeight
			, 0						// nWidth
			, 0						// nEscapement
			, 0						// nOrientation
			, 500						// nWeight
			, FALSE					// nItalic
			, FALSE					// nUnderline
			, 0						// cStrikeOut
			, ANSI_CHARSET			// nTCHARSet
			, OUT_DEFAULT_PRECIS	// nOutPrecision
			, CLIP_DEFAULT_PRECIS	// nClipPrecision
			, DEFAULT_QUALITY		// nQuality
			, DEFAULT_PITCH|FF_SWISS// nPitchAndFamily
			, _T("arial") );        // lpszFacename
		HFONT hOldFont = (HFONT)::SelectObject(hDC, (HGDIOBJ)hFont);
		{
			DrawText(hDC, _T("www.itxueba.org"), _tcslen(_T("www.itxueba.org")), &rcClient, DT_LEFT|DT_TOP | DT_SINGLELINE);
			//TextOut(hDC, 0, 0,_T("www.itxueba.org"), _tcslen(_T("www.itxueba.org")));
		}
		::SelectObject(hDC, (HGDIOBJ)hOldFont);
		DeleteObject((HGDIOBJ)hFont);

		SetBkColor(hDC, clrBackColor);
		SetTextColor(hDC, clrOldTextColor);
		*/
	}
	::EndPaint(hwnd, &ps);
}

void HandlerThree(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = ::BeginPaint(hwnd, &ps);
	assert(hdc);
	{
		g_hCheneyGraph.Draw(hdc);
	}
	::EndPaint(hwnd, &ps);
}

void HandlerFour(HWND hwnd, CheneyNumberClock m_hCheneyNumberClock)
{
	int cxClient = m_hCheneyNumberClock.cxClient;
	int cyClient = m_hCheneyNumberClock.cyClient;
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, 276, 72, NULL);
	SetViewportExtEx(hdc, cxClient, cyClient, NULL);
	
	SetWindowOrgEx(hdc, 138, 36, NULL);
	SetViewportOrgEx(hdc, cxClient >> 1, cyClient >> 1, NULL);
	SelectObject(hdc, GetStockObject(NULL_PEN));
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(hdc, (HGDIOBJ) hBrush);
	m_hCheneyNumberClock.DisplayTime(hdc, m_hCheneyNumberClock.f24Hour, m_hCheneyNumberClock.fSuppress);
	DeleteObject((HGDIOBJ) hBrush);
	EndPaint(hwnd, &ps);
}

BOOL CheckFileRelation(const TCHAR* suffix, const TCHAR* appKey)
{
    HKEY hExtKey;
    if(!RegOpenKey(HKEY_CLASSES_ROOT, suffix, &hExtKey))
    {
        return FALSE;
    }
    TCHAR szPath[_MAX_PATH];
    DWORD dwSize = sizeof(szPath);
    RegQueryValueEx(hExtKey, NULL, NULL, NULL, (LPBYTE)szPath, &dwSize);
    if(_tcscmp(szPath, appKey) == 0)
    {
        RegCloseKey(hExtKey);
        return TRUE;
    }
    RegCloseKey(hExtKey);
    return FALSE;
}

void RegisterFileRelation(TCHAR* suffix, TCHAR* appKey, TCHAR* appName)
{
    HKEY hKey;
    ::RegCreateKey(HKEY_CLASSES_ROOT, suffix, &hKey);
    ::RegSetValue(hKey, _T(""), REG_SZ, appKey, _tcslen(appKey) + 1);
    ::RegCloseKey(hKey);
    TCHAR strTemp[_MAX_PATH];
	sprintf_s(strTemp, sizeof(strTemp), _T("%s\\shell\\open\\command"), appKey);
    ::RegCreateKey(HKEY_CLASSES_ROOT, strTemp, &hKey);
    sprintf_s(strTemp, sizeof(strTemp), _T("%s \"%%1\""), appName);
    ::RegSetValue(hKey, _T(""), REG_SZ, strTemp, _tcslen(strTemp) + 1);
    ::RegCloseKey(hKey);
}
