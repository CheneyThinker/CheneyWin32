#include "CheneyNumberClock.h"

SPECIAL_HANDLER(CheneyNumberClock, {}, {})
void CheneyNumberClock::DisplayDigit(HDC hdc, int iNumber)
{
	static BOOL fSevenSegment[10][7] = {
		1, 1, 1, 0, 1, 1, 1,//0
		0, 0, 1, 0, 0, 1, 0,//1
		1, 0, 1, 1, 1, 0, 1,//2
		1, 0, 1, 1, 0, 1, 1,//3
		0, 1, 1, 1, 0, 1, 0,//4
		1, 1, 0, 1, 0, 1, 1,//5
		1, 1, 0, 1, 1, 1, 1,//6
		1, 0, 1, 0, 0, 1, 0,//7
		1, 1, 1, 1, 1, 1, 1,//8
		1, 1, 1, 1, 0, 1, 1 //9
	};
	static POINT ptSegment[7][6] = {
		 7,  6, 11,  2, 31,  2, 35,  6, 31, 10, 11, 10,//A
		 6,  7, 10, 11, 10, 31,  6, 35,  2, 31,  2, 11,//B
		36,  7, 40, 11, 40, 31, 36, 35, 32, 31, 32, 11,//C
		 7, 36, 11, 32, 31, 32, 35, 36, 31, 40, 11, 40,//D
		 6, 37, 10, 41, 10, 61,  6, 65,  2, 61,  2, 41,//E
		36, 37, 40, 41, 40, 61, 36, 65, 32, 61, 32, 41,//F
		 7, 66, 11, 62, 31, 62, 35, 66, 31, 70, 11, 70 //G
	};
	int iSeg;
	for(iSeg = 0; iSeg < 7; iSeg++)
	{
		if(fSevenSegment[iNumber][iSeg])
		{
			Polygon(hdc, ptSegment[iSeg], 6);
		}
	}
}

void CheneyNumberClock::DisplayTwoDigits(HDC hdc, int iNumber, BOOL fSuppress)
{
	if(!fSuppress || (iNumber / 10 != 0))
	{
		DisplayDigit(hdc, iNumber / 10);
	}
	OffsetWindowOrgEx(hdc, -42, 0, NULL);
	DisplayDigit(hdc, iNumber % 10);
	OffsetWindowOrgEx(hdc, -42, 0, NULL);
}

void CheneyNumberClock::DisplayColon(HDC hdc)
{
	POINT ptColon[2][4] = {
		2, 21, 6, 17, 10, 21, 6, 25,
		2, 51, 6, 47, 10, 51, 6, 55
	};
	Polygon(hdc, ptColon[0], 4);
	Polygon(hdc, ptColon[1], 4);
	OffsetWindowOrgEx(hdc, -12, 0, NULL);
}

void CheneyNumberClock::DisplayTime(HDC hdc, BOOL f24Hour, BOOL fSuppress)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	if(f24Hour)
	{
		DisplayTwoDigits(hdc, st.wHour, fSuppress);
	}
	else
	{
		DisplayTwoDigits(hdc, (st.wHour %= 12) ? st.wHour : 12, fSuppress);
	}
	DisplayColon(hdc);
	DisplayTwoDigits(hdc, st.wMinute, FALSE);
	DisplayColon(hdc);
	DisplayTwoDigits(hdc, st.wSecond, FALSE);
}