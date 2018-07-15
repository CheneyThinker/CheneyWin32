#ifndef THINKERRECT_H_INCLUDED
#define THINKERRECT_H_INCLUDED

#pragma once

#include <windows.h>

class ThinkerSize;
class ThinkerPoint;
class ThinkerRect;

class ThinkerSize : public tagSIZE
{
public:
    ThinkerSize();
    ThinkerSize(int initCX, int initCY);
    ThinkerSize(SIZE size);
    ThinkerSize(POINT point);
    ThinkerSize(DWORD dwSize);
public:
    BOOL operator==(SIZE size);
	BOOL operator!=(SIZE size);
	void operator+=(SIZE size);
	void operator-=(SIZE size);
public:
	void SetSize(int cX, int cY);
	ThinkerSize operator+(SIZE size);
	ThinkerSize operator-(SIZE size);
	ThinkerSize operator-();
	ThinkerPoint operator+(POINT point);
	ThinkerPoint operator-(POINT point);
	ThinkerRect operator+(const RECT* lpRect);
	ThinkerRect operator-(const RECT* lpRect);
};

class ThinkerPoint : public tagPOINT
{
public:
    ThinkerPoint();
    ThinkerPoint(int initX, int initY);
    ThinkerPoint(POINT point);
	ThinkerPoint(SIZE size);
	ThinkerPoint(LPARAM dwPoint);
	void Offset(int xOffset, int yOffset);
	void Offset(POINT point);
	void Offset(SIZE size);
	void SetPoint(int X, int Y);
	BOOL operator==(POINT point);
	BOOL operator!=(POINT point);
	void operator+=(SIZE size);
	void operator-=(SIZE size);
	void operator+=(POINT point);
	void operator-=(POINT point);
	ThinkerPoint operator+(SIZE size);
	ThinkerPoint operator-(SIZE size);
	ThinkerPoint operator-();
	ThinkerPoint operator+(POINT point);
	ThinkerSize operator-(POINT point);
	ThinkerRect operator+(const RECT* lpRect);
	ThinkerRect operator-(const RECT* lpRect);
};

class ThinkerRect : public tagRECT
{
public:
	ThinkerRect();
	ThinkerRect(int l, int t, int r, int b);
	ThinkerRect(const RECT& rect);
	ThinkerRect(LPCRECT lpSrcRect);
	ThinkerRect(POINT point, SIZE size);
	ThinkerRect(POINT topLeft, POINT bottomRight);
	int Width();
	int Height();
	ThinkerSize Size();
	ThinkerPoint& TopLeft();
	ThinkerPoint& BottomRight();
	const ThinkerPoint& TopLeft() const;
	const ThinkerPoint& BottomRight() const;
	ThinkerPoint CenterPoint();
	void SwapLeftRight();
	static void WINAPI SwapLeftRight(LPRECT lpRect);
	operator LPRECT();
	operator LPCRECT();
	BOOL IsRectEmpty();
	BOOL IsRectNull();
	BOOL PtInRect(POINT point);
	void SetRect(int x1, int y1, int x2, int y2);
	void SetRect(POINT topLeft, POINT bottomRight);
	void SetRectEmpty();
	void CopyRect(LPCRECT lpSrcRect);
	BOOL EqualRect(LPCRECT lpRect);
	void InflateRect(int x, int y);
	void InflateRect(SIZE size);
	void InflateRect(LPCRECT lpRect);
	void InflateRect(int l, int t, int r, int b);
	void DeflateRect(int x, int y);
	void DeflateRect(SIZE size);
	void DeflateRect(LPCRECT lpRect);
	void DeflateRect(int l, int t, int r, int b);
	void OffsetRect(int x, int y);
	void OffsetRect(SIZE size);
	void OffsetRect(POINT point);
	void NormalizeRect();
	void MoveToY(int y);
	void MoveToX(int x);
	void MoveToXY(int x, int y);
	void MoveToXY(POINT point);
	BOOL IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2);
	BOOL UnionRect(LPCRECT lpRect1, LPCRECT lpRect2);
	BOOL SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2);
	void operator=(const RECT& srcRect);
	BOOL operator==(const RECT& rect);
	BOOL operator!=(const RECT& rect);
	void operator+=(POINT point);
	void operator+=(SIZE size);
	void operator+=(LPCRECT lpRect);
	void operator-=(POINT point);
	void operator-=(SIZE size);
	void operator-=(LPCRECT lpRect);
	void operator&=(const RECT& rect);
	void operator|=(const RECT& rect);
	ThinkerRect operator+(POINT point);
	ThinkerRect operator-(POINT point);
	ThinkerRect operator+(LPCRECT lpRect);
	ThinkerRect operator+(SIZE size);
	ThinkerRect operator-(SIZE size);
	ThinkerRect operator-(LPCRECT lpRect);
	ThinkerRect operator&(const RECT& rect2);
	ThinkerRect operator|(const RECT& rect2);
	ThinkerRect MulDiv(int nMultiplier, int nDivisor);
};

#endif // THINKERRECT_H_INCLUDED