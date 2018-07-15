#include "CheneyImage.h"

SPECIAL_HANDLER(CheneyImage, {}, {})

void CheneyImage::Show(HWND m_hWnd, int m_iShowID)
{
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(m_hWnd, &ps);
	switch(m_iShowID)
	{
	case 0:
		Draw(hdc);
		break;
	case 1:
		StaggeredHorizontal(hdc);
		break;
	case 2:
		StaggeredVertical(hdc);
		break;
	case 3:
		JalousieHorizontal(hdc);
		break;
	case 4:
		JalousieVertical(hdc);
		break;
	case 5:
		RandomBlocks(hdc);
		break;
	case 6:
		FlyingTopToBottom(hdc, 2, TRUE);
		break;
	case 7:
		FlyingBottomToTop(hdc, 2, FALSE);
		break;
	case 8:
		FlyingLeftToRight(hdc, 2, FALSE);
		break;
	case 9:
		FlyingRightToLeft(hdc, 2, FALSE);
	case 10:
		FlyingTopToBottom(hdc);
		break;
	case 11:
		FlyingBottomToTop(hdc);
		break;
	case 12:
		FlyingLeftToRight(hdc);
		break;
	case 13:
		FlyingRightToLeft(hdc);
		break;
	}
	if(m_iShowID != 0)
	{
		m_iShowID = 0;
		InvalidateRect(m_hWnd, NULL, FALSE);
	}
	EndPaint(m_hWnd, &ps);
}

BOOL CheneyImage::Load(HWND hwnd, UINT hID)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HBITMAP hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(hID));
	return Check(hwnd, hBitmap);
}

BOOL CheneyImage::Load(HWND hwnd, LPCSTR lpszFileName)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HBITMAP hBitmap = (HBITMAP)LoadImage(hInstance, lpszFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	return Check(hwnd, hBitmap);
}

BOOL CheneyImage::Check(HWND hwnd, HBITMAP hBitmap)
{
	if(hBitmap == NULL)
	{
		MessageBox(NULL, TEXT("LoadImage Failed!"), TEXT("Error"), MB_ICONERROR);
		return FALSE;
	}
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(bitmap), &bitmap);
	m_hCheneyImageUnit.SetHBitmap(hBitmap);
	m_hCheneyImageUnit.SetBitmap(bitmap);
	CreateCompatibleDC(hwnd);
	return TRUE;
}

void CheneyImage::CreateCompatibleDC(HWND hwnd)
{
	if(m_hdcMem)
		DeleteDC();
	HDC hdc = GetDC(hwnd);
	m_hdcMem = ::CreateCompatibleDC(hdc);
	SelectObject(m_hdcMem, m_hCheneyImageUnit.GetHBitmap());
	ReleaseDC(hwnd, hdc);
}

void CheneyImage::DeleteDC()
{
	::DeleteDC(m_hdcMem);
}

void CheneyImage::Draw(HDC hdc, RECT rect)
{
	Draw(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, GetWidth(), GetHeight());
}

void CheneyImage::Draw(HDC hdc, RECT dest, RECT src)
{
	Draw(hdc, dest.left, dest.top, dest.right - dest.left, dest.bottom - dest.top, src.left, src.top, src.right - src.left, src.bottom - src.top);
}

void CheneyImage::Draw(HDC hdc, int destX, int destY, int destWidth, int destHeight, int srcX, int srcY, int srcWidth, int srcHeight)
{
	::StretchBlt(hdc, destX, destY, destWidth, destHeight, m_hdcMem, srcX, srcY, srcWidth, srcHeight, SRCCOPY);
}

void CheneyImage::Draw(HDC hdc, int cx, int cy)
{
	SetStretchBltMode(hdc, COLORONCOLOR);
	::StretchBlt(hdc, 0, 0, cx, cy, m_hdcMem, 0, 0, GetWidth(), GetHeight(), SRCCOPY);
}

void CheneyImage::Draw(HDC hdc)
{
	::BitBlt(hdc, 0, 0, GetWidth(), GetHeight(), m_hdcMem, 0, 0, SRCCOPY);
}

void CheneyImage::StaggeredHorizontal(HDC hdc, UINT nIntervalTime)
{
	int i, j;
	int nHeight = (int) GetHeight();
	int nWidth = (int) GetWidth();
	for(i = 0; i <= nHeight; i += 2)
	{
		for(j = i; j > 0; j -= 2)
		{
			::BitBlt(hdc, 0, j - 1, nWidth, 1, m_hdcMem, 0, nHeight - (i - j - 1), SRCCOPY);
			::BitBlt(hdc, 0, nHeight - j, nWidth, 1, m_hdcMem, 0, i - j, SRCCOPY);
		}
		Sleep(nIntervalTime);
	}
	::BitBlt(hdc, 0, 0, nWidth, nHeight, m_hdcMem, 0, 0, SRCCOPY);
}

void CheneyImage::StaggeredVertical(HDC hdc, UINT nIntervalTime)
{
	int i, j;
	int nHeight = (int) GetHeight();
	int nWidth = (int) GetWidth();
	for (i = 0; i <= nWidth; i += 2)
	{
		for (j = i; j > 0; j -= 2)
		{
			::BitBlt(hdc, j - 1, 0, 1, nHeight, m_hdcMem, nWidth - (i - j - 1), 0, SRCCOPY);
			::BitBlt(hdc, nWidth - j, 0, 1, nHeight, m_hdcMem, i - j, 0, SRCCOPY);
		}
		Sleep(nIntervalTime);
	}
	::BitBlt(hdc, 0, 0, nWidth, nHeight, m_hdcMem, 0, 0, SRCCOPY);
}

void CheneyImage::JalousieHorizontal(HDC hdc, UINT nIntervalTime, UINT nJalousieNum)
{
	int i;
	unsigned int j;
	int nHeight = (int) GetHeight();
	int nWidth = (int) GetWidth();
	int nJalousieHeight;
	nJalousieHeight = nHeight / nJalousieNum;
	for (i = 0; i <= nJalousieHeight; i++)
	{
		for(j = 0; j < nJalousieNum; j++)
			::BitBlt(hdc, 0, j * nJalousieHeight, nWidth, i, m_hdcMem, 0, j * nJalousieHeight, SRCCOPY);
		Sleep(nIntervalTime);
	}
	::BitBlt(hdc, 0, 0, nWidth, nHeight, m_hdcMem, 0, 0, SRCCOPY);
}

void CheneyImage::JalousieVertical(HDC hdc, UINT nIntervalTime, UINT nJalousieNum)
{
	int i;
	unsigned int j;
	int nHeight = (int) GetHeight();
	int nWidth = (int) GetWidth();
	int nStep;
	nStep = nWidth / nJalousieNum;
	for (i = 0; i <= nStep; i++)
	{
		for(j = 0; j < nJalousieNum; j++)
			::BitBlt(hdc, j * nStep, 0, i, nHeight,m_hdcMem, j * nStep, 0, SRCCOPY);
		Sleep(nIntervalTime);
	}
	::BitBlt(hdc, 0, 0, nWidth, nHeight, m_hdcMem, 0, 0, SRCCOPY);
}

void CheneyImage::RandomBlocks(HDC hdc, UINT nIntervalTime, int nRowBlocks, int nColBlocks)
{
	int nHeight = (int) GetHeight();
	int nWidth = (int) GetWidth();
	int nStepRow, nStepCol, nDisplayCount;
	int nSumBlocks = nRowBlocks * nColBlocks;
	bool *pFlagArray = new bool[nSumBlocks];
	memset(pFlagArray, 0, sizeof(bool) * nSumBlocks);
	nStepRow = nWidth / nRowBlocks;
	nStepCol = nHeight / nColBlocks;
	srand((unsigned)time(NULL));
	nDisplayCount = 0;
	while (true)
	{
		int row = rand() % nRowBlocks;
		int col = rand() % nColBlocks;
		if (pFlagArray[row * nColBlocks + col])
			continue;
		pFlagArray[row * nColBlocks + col] = true;
		::BitBlt(hdc, row * nStepRow, col * nStepCol, nStepRow, nStepCol, m_hdcMem, row * nStepRow, col * nStepCol, SRCCOPY);
		nDisplayCount++;
		if (nDisplayCount >= nSumBlocks)
			break;
		Sleep(nIntervalTime);
	}
	::BitBlt(hdc, 0, 0, nWidth, nHeight, m_hdcMem, 0, 0, SRCCOPY);
}

void CheneyImage::FlyingTopToBottom(HDC hdc, UINT nIntervalTime, BOOL bFade)
{
	int nHeight = (int) GetHeight();
	int nWidth = (int) GetWidth();
	int j;
	if (bFade)
	{
		for (j = 0; j <= nHeight; j++)
		{
			::BitBlt(hdc, 0, 0, nWidth, j, m_hdcMem, 0, 0, SRCCOPY); 
			Sleep(nIntervalTime);
		}
	}
	else
	{
		for (j = 0; j <= nHeight; j++)
		{
			::BitBlt(hdc, 0, 0, nWidth, j, m_hdcMem, 0, nHeight - j, SRCCOPY);
			Sleep(nIntervalTime);
		}
	}
	::BitBlt(hdc, 0, 0, nWidth, nHeight, m_hdcMem, 0, 0, SRCCOPY);
}

void CheneyImage::FlyingBottomToTop(HDC hdc, UINT nIntervalTime, BOOL bFade)
{
	int nHeight = (int) GetHeight();
	int nWidth = (int) GetWidth();
	int j;
	if(bFade)
	{
		for (j = nHeight; j >= 0; j--)
		{
			::BitBlt(hdc, 0, j, nWidth, nHeight - j, m_hdcMem, 0, j, SRCCOPY);
			Sleep(nIntervalTime);
		}
	}
	else
	{
		for (j = nHeight; j >= 0; j--)
		{
			::BitBlt(hdc, 0, j, nWidth, nHeight - j, m_hdcMem, 0, 0, SRCCOPY);
			Sleep(nIntervalTime);
		}
	}
	::BitBlt(hdc, 0, 0, nWidth, nHeight, m_hdcMem, 0, 0, SRCCOPY);
}

void CheneyImage::FlyingLeftToRight(HDC hdc, UINT nIntervalTime, BOOL bFade)
{
	int nHeight = (int) GetHeight();
	int nWidth = (int) GetWidth();
	int i;
	if (bFade)
	{
		for (i = 0; i <= nWidth; i++)
		{
			::BitBlt(hdc, 0, 0, i, nHeight, m_hdcMem, 0, 0, SRCCOPY);
			Sleep(nIntervalTime);
		}
	}
	else
	{
		for (i = 0; i <= nWidth; i++)
		{
			::BitBlt(hdc, 0, 0, i, nHeight, m_hdcMem, nWidth - i, 0, SRCCOPY);
			Sleep(nIntervalTime);
		}
	}
	::BitBlt(hdc, 0, 0, nWidth, nHeight, m_hdcMem, 0, 0, SRCCOPY);
}

void CheneyImage::FlyingRightToLeft(HDC hdc, UINT nIntervalTime, BOOL bFade)
{
	int nHeight = (int) GetHeight();
	int nWidth = (int) GetWidth();
	int i;
	if (bFade)
	{
		for (i = nWidth; i >= 0; i--)
		{
			::BitBlt(hdc, i, 0, nWidth - i, nHeight, m_hdcMem, i, 0, SRCCOPY);
			Sleep(nIntervalTime);
		}
	}
	else
	{
		for (i = nWidth; i >= 0; i--)
		{
			::BitBlt(hdc, i, 0, nWidth - i, nHeight, m_hdcMem, 0, 0, SRCCOPY);
			Sleep(nIntervalTime);
		}
	}
	::BitBlt(hdc, 0, 0, nWidth, nHeight, m_hdcMem, 0, 0, SRCCOPY);
}