#include "ThinkerRect.h"

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

ThinkerSize::ThinkerSize()
{
    cx = 0;
    cy = 0;
}

ThinkerSize::ThinkerSize(int initCX, int initCY)
{
    cx = initCX;
    cy = initCY;
}

ThinkerSize::ThinkerSize(SIZE size)
{
    *(SIZE*)this = size;
}

ThinkerSize::ThinkerSize(POINT point)
{
    *(POINT*)this = point;
}

ThinkerSize::ThinkerSize(DWORD dwSize)
{
    cx = (short)LOWORD(dwSize);
    cy = (short)HIWORD(dwSize);
}

BOOL ThinkerSize::operator==(SIZE size)
{
    return (cx == size.cx && cy == size.cy);
}

BOOL ThinkerSize::operator!=(SIZE size)
{
    return (cx != size.cx || cy != size.cy);
}

void ThinkerSize::operator+=(SIZE size)
{
    cx += size.cx;
    cy += size.cy;
}

void ThinkerSize::operator-=(SIZE size)
{
    cx -= size.cx;
    cy -= size.cy;
}

void ThinkerSize::SetSize(int CX, int CY)
{
    cx = CX;
    cy = CY;
}

ThinkerSize ThinkerSize::operator+(SIZE size)
{
    return ThinkerSize(cx + size.cx, cy + size.cy);
}

ThinkerSize ThinkerSize::operator-(SIZE size)
{
    return ThinkerSize(cx - size.cx, cy - size.cy);
}

ThinkerSize ThinkerSize::operator-()
{
    return ThinkerSize(-cx, -cy);
}

ThinkerPoint ThinkerSize::operator+(POINT point)
{
    return ThinkerPoint(cx + point.x, cy + point.y);
}

ThinkerPoint ThinkerSize::operator-(POINT point)
{
    return ThinkerPoint(cx - point.x, cy - point.y);
}

ThinkerRect ThinkerSize::operator+(const RECT* lpRect)
{
    return ThinkerRect(lpRect) + *this;
}

ThinkerRect ThinkerSize::operator-(const RECT* lpRect)
{
    return ThinkerRect(lpRect) - *this;
}

ThinkerPoint::ThinkerPoint()
{
    x = 0;
    y = 0;
}

ThinkerPoint::ThinkerPoint(int initX, int initY)
{
    x = initX;
    y = initY;
}

ThinkerPoint::ThinkerPoint(POINT point)
{
    *(POINT*)this = point;
}

ThinkerPoint::ThinkerPoint(SIZE size)
{
    *(SIZE*)this = size;
}

ThinkerPoint::ThinkerPoint(LPARAM dwPoint)
{
    x = (short)GET_X_LPARAM(dwPoint);
    y = (short)GET_Y_LPARAM(dwPoint);
}

void ThinkerPoint::Offset(int xOffset, int yOffset)
{
    x += xOffset;
    y += yOffset;
}

void ThinkerPoint::Offset(POINT point)
{
    x += point.x;
    y += point.y;
}

void ThinkerPoint::Offset(SIZE size)
{
    x += size.cx;
    y += size.cy;
}

void ThinkerPoint::SetPoint(int X, int Y)
{
    x = X;
    y = Y;
}

BOOL ThinkerPoint::operator==(POINT point)
{
    return (x == point.x && y == point.y);
}

BOOL ThinkerPoint::operator!=(POINT point)
{
    return (x != point.x || y != point.y);
}

void ThinkerPoint::operator+=(SIZE size)
{
    x += size.cx;
    y += size.cy;
}

void ThinkerPoint::operator-=(SIZE size)
{
    x -= size.cx;
    y -= size.cy;
}

void ThinkerPoint::operator+=(POINT point)
{
    x += point.x;
    y += point.y;
}

void ThinkerPoint::operator-=(POINT point)
{
    x -= point.x;
    y -= point.y;
}

ThinkerPoint ThinkerPoint::operator+(SIZE size)
{
    return ThinkerPoint(x + size.cx, y + size.cy);
}

ThinkerPoint ThinkerPoint::operator-(SIZE size)
{
    return ThinkerPoint(x - size.cx, y - size.cy);
}

ThinkerPoint ThinkerPoint::operator-()
{
    return ThinkerPoint(-x, -y);
}

ThinkerPoint ThinkerPoint::operator+(POINT point)
{
    return ThinkerPoint(x + point.x, y + point.y);
}

ThinkerSize ThinkerPoint::operator-(POINT point)
{
    return ThinkerSize(x - point.x, y - point.y);
}

ThinkerRect ThinkerPoint::operator+(const RECT* lpRect)
{
    return ThinkerRect(lpRect) + *this;
}

ThinkerRect ThinkerPoint::operator-(const RECT* lpRect)
{
    return ThinkerRect(lpRect) - *this;
}

ThinkerRect::ThinkerRect()
{
    left = 0;
    top = 0;
    right = 0;
    bottom = 0;
}

ThinkerRect::ThinkerRect(int l, int t, int r, int b)
{
    left = l;
    top = t;
    right = r;
    bottom = b;
}

ThinkerRect::ThinkerRect(const RECT& srcRect)
{
    ::CopyRect(this, &srcRect);
}

ThinkerRect::ThinkerRect(LPCRECT lpSrcRect)
{
    ::CopyRect(this, lpSrcRect);
}

ThinkerRect::ThinkerRect(POINT point, SIZE size)
{
    right = (left = point.x) + size.cx;
    bottom = (top = point.y) + size.cy;
}

ThinkerRect::ThinkerRect(POINT topLeft, POINT bottomRight)
{
    left = topLeft.x; top = topLeft.y;
    right = bottomRight.x; bottom = bottomRight.y;
}

int ThinkerRect::Width()
{
    return right - left;
}

int ThinkerRect::Height()
{
    return bottom - top;
}

ThinkerSize ThinkerRect::Size()
{
    return ThinkerSize(right - left, bottom - top);
}

ThinkerPoint& ThinkerRect::TopLeft()
{
    return *((ThinkerPoint*)this);
}

ThinkerPoint& ThinkerRect::BottomRight()
{
    return *((ThinkerPoint*)this+1);
}

const ThinkerPoint& ThinkerRect::TopLeft() const
{
    return *((ThinkerPoint*)this);
}

const ThinkerPoint& ThinkerRect::BottomRight() const
{
    return *((ThinkerPoint*)this+1);
}

ThinkerPoint ThinkerRect::CenterPoint()
{
    return ThinkerPoint((left+right)/2, (top+bottom)/2);
}

void ThinkerRect::SwapLeftRight()
{
    SwapLeftRight(LPRECT(this));
}

void WINAPI ThinkerRect::SwapLeftRight(LPRECT lpRect)
{
    LONG temp = lpRect->left;
    lpRect->left = lpRect->right;
    lpRect->right = temp;
}

ThinkerRect::operator LPRECT()
{
    return this;
}

ThinkerRect::operator LPCRECT()
{
    return this;
}

BOOL ThinkerRect::IsRectEmpty()
{
    return ::IsRectEmpty(this);
}

BOOL ThinkerRect::IsRectNull()
{
    return (left == 0 && right == 0 && top == 0 && bottom == 0);
}

BOOL ThinkerRect::PtInRect(POINT point)
{
    return ::PtInRect(this, point);
}

void ThinkerRect::SetRect(int x1, int y1, int x2, int y2)
{
    ::SetRect(this, x1, y1, x2, y2);
}

void ThinkerRect::SetRect(POINT topLeft, POINT bottomRight)
{
    ::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

void ThinkerRect::SetRectEmpty()
{
    ::SetRectEmpty(this);
}

void ThinkerRect::CopyRect(LPCRECT lpSrcRect)
{
    ::CopyRect(this, lpSrcRect);
}

BOOL ThinkerRect::EqualRect(LPCRECT lpRect)
{
    return ::EqualRect(this, lpRect);
}

void ThinkerRect::InflateRect(int x, int y)
{
    ::InflateRect(this, x, y);
}

void ThinkerRect::InflateRect(SIZE size)
{
    ::InflateRect(this, size.cx, size.cy);
}

void ThinkerRect::DeflateRect(int x, int y)
{
    ::InflateRect(this, -x, -y);
}

void ThinkerRect::DeflateRect(SIZE size)
{
    ::InflateRect(this, -size.cx, -size.cy);
}

void ThinkerRect::OffsetRect(int x, int y)
{
    ::OffsetRect(this, x, y);
}

void ThinkerRect::OffsetRect(POINT point)
{
    ::OffsetRect(this, point.x, point.y);
}

void ThinkerRect::OffsetRect(SIZE size)
{
    ::OffsetRect(this, size.cx, size.cy);
}

void ThinkerRect::MoveToY(int y)
{
    bottom = Height() + y;
    top = y;
}

void ThinkerRect::MoveToX(int x)
{
    right = Width() + x;
    left = x;
}

void ThinkerRect::MoveToXY(int x, int y)
{
    MoveToX(x);
    MoveToY(y);
}

void ThinkerRect::MoveToXY(POINT pt)
{
    MoveToX(pt.x);
    MoveToY(pt.y);
}

BOOL ThinkerRect::IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2)
{
    return ::IntersectRect(this, lpRect1, lpRect2);
}

BOOL ThinkerRect::UnionRect(LPCRECT lpRect1, LPCRECT lpRect2)
{
    return ::UnionRect(this, lpRect1, lpRect2);
}

void ThinkerRect::operator=(const RECT& srcRect)
{
    ::CopyRect(this, &srcRect);
}

BOOL ThinkerRect::operator==(const RECT& rect)
{
    return ::EqualRect(this, &rect);
}

BOOL ThinkerRect::operator!=(const RECT& rect)
{
    return !::EqualRect(this, &rect);
}

void ThinkerRect::operator+=(POINT point)
{
    ::OffsetRect(this, point.x, point.y);
}

void ThinkerRect::operator+=(SIZE size)
{
    ::OffsetRect(this, size.cx, size.cy);
}

void ThinkerRect::operator+=(LPCRECT lpRect)
{
    InflateRect(lpRect);
}

void ThinkerRect::operator-=(POINT point)
{
    ::OffsetRect(this, -point.x, -point.y);
}

void ThinkerRect::operator-=(SIZE size)
{
    ::OffsetRect(this, -size.cx, -size.cy);
}

void ThinkerRect::operator-=(LPCRECT lpRect)
{
    DeflateRect(lpRect);
}

void ThinkerRect::operator&=(const RECT& rect)
{
    ::IntersectRect(this, this, &rect);
}

void ThinkerRect::operator|=(const RECT& rect)
{
    ::UnionRect(this, this, &rect);
}

ThinkerRect ThinkerRect::operator+(POINT pt)
{
    ThinkerRect rect(*this);
    ::OffsetRect(&rect, pt.x, pt.y);
    return rect;
}

ThinkerRect ThinkerRect::operator-(POINT pt)
{
    ThinkerRect rect(*this);
    ::OffsetRect(&rect, -pt.x, -pt.y);
    return rect;
}

ThinkerRect ThinkerRect::operator+(SIZE size)
{
    ThinkerRect rect(*this);
    ::OffsetRect(&rect, size.cx, size.cy);
    return rect;
}

ThinkerRect ThinkerRect::operator-(SIZE size)
{
    ThinkerRect rect(*this);
    ::OffsetRect(&rect, -size.cx, -size.cy);
    return rect;
}

ThinkerRect ThinkerRect::operator+(LPCRECT lpRect)
{
    ThinkerRect rect(this);
    rect.InflateRect(lpRect);
    return rect;
}

ThinkerRect ThinkerRect::operator-(LPCRECT lpRect)
{
    ThinkerRect rect(this);
    rect.DeflateRect(lpRect);
    return rect;
}

ThinkerRect ThinkerRect::operator&(const RECT& rect2)
{
    ThinkerRect rect;
    ::IntersectRect(&rect, this, &rect2);
    return rect;
}

ThinkerRect ThinkerRect::operator|(const RECT& rect2)
{
    ThinkerRect rect;
    ::UnionRect(&rect, this, &rect2);
    return rect;
}

BOOL ThinkerRect::SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2)
{
    return ::SubtractRect(this, lpRectSrc1, lpRectSrc2);
}

void ThinkerRect::NormalizeRect()
{
    int nTemp;
    if (left > right)
    {
        nTemp = left;
        left = right;
        right = nTemp;
    }
    if (top > bottom)
    {
        nTemp = top;
        top = bottom;
        bottom = nTemp;
    }
}

void ThinkerRect::InflateRect(LPCRECT lpRect)
{
    left -= lpRect->left;
    top -= lpRect->top;
    right += lpRect->right;
    bottom += lpRect->bottom;
}

void ThinkerRect::InflateRect(int l, int t, int r, int b)
{
    left -= l;
    top -= t;
    right += r;
    bottom += b;
}

void ThinkerRect::DeflateRect(LPCRECT lpRect)
{
    left += lpRect->left;
    top += lpRect->top;
    right -= lpRect->right;
    bottom -= lpRect->bottom;
}

void ThinkerRect::DeflateRect(int l, int t, int r, int b)
{
    left += l;
    top += t;
    right -= r;
    bottom -= b;
}

ThinkerRect ThinkerRect::MulDiv(int nMultiplier, int nDivisor)
{
    return ThinkerRect(::MulDiv(left, nMultiplier, nDivisor),
                       ::MulDiv(top, nMultiplier, nDivisor),
                       ::MulDiv(right, nMultiplier, nDivisor),
                       ::MulDiv(bottom, nMultiplier, nDivisor));
}