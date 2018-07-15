#ifndef CHENEYIMAGE_H_INCLUDED
#define CHENEYIMAGE_H_INCLUDED
#pragma once

#include "CheneyThinker.h"

class CheneyImageUnit
{
public:
	CheneyImageUnit(void) {}
	virtual ~CheneyImageUnit(){}
	inline void SetHBitmap(HBITMAP hBitmap) { m_hBitmap = hBitmap; }
	inline HBITMAP GetHBitmap() const { return m_hBitmap; }
	inline void SetBitmap(BITMAP bitmap) { m_bitmap = bitmap; }
	inline BITMAP GetBitmap() const { return m_bitmap; }
	inline LONG GetHeight() const { return m_bitmap.bmHeight; }
	inline LONG GetWidth() const { return m_bitmap.bmWidth; }
private:
	HBITMAP m_hBitmap;
	BITMAP m_bitmap;
};

class CheneyImage
{
public:
	SPECIAL(CheneyImage)
	void Show(HWND, int);
	BOOL Load(HWND, UINT);
	BOOL Load(HWND, LPCSTR);
	BOOL Check(HWND, HBITMAP);
	void CreateCompatibleDC(HWND);
	void DeleteDC();
	void Draw(HDC);
	void Draw(HDC, int cx, int cy);
	void Draw(HDC, RECT);
	void Draw(HDC, RECT, RECT);
	inline LONG GetHeight() const { return m_hCheneyImageUnit.GetHeight(); }
	inline LONG GetWidth() const { return m_hCheneyImageUnit.GetWidth(); }
	void Draw(HDC, int destX, int destY, int destWidth, int destHeight, int srcX, int srcY, int srcWidth, int srcHeight);
	void StaggeredHorizontal(HDC, UINT nIntervalTime = 10);
	void StaggeredVertical(HDC, UINT nIntervalTime = 10);
	void JalousieHorizontal(HDC, UINT nIntervalTime = 15, UINT nJalousieNum = 10);
	void JalousieVertical(HDC, UINT nIntervalTime = 15, UINT nJalousieNum = 10);
	void RandomBlocks(HDC, UINT nIntervalTime = 15, int nRowBlocks = 10, int nColBlocks = 10);
	void FlyingTopToBottom(HDC, UINT nIntervalTime = 2, BOOL bFade = TRUE);
	void FlyingBottomToTop(HDC, UINT nIntervalTime = 2, BOOL bFade = TRUE);
	void FlyingLeftToRight(HDC, UINT nIntervalTime = 2, BOOL bFade = TRUE);
	void FlyingRightToLeft(HDC, UINT nIntervalTime = 2, BOOL bFade = TRUE);
	CheneyImageUnit m_hCheneyImageUnit;
	HDC m_hdcMem;
};

#endif