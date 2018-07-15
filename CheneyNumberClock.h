#ifndef CHENEYNUMBERCLOCK_H_INCLUDE
#define CHENEYNUMBERCLOCK_H_INCLUDE
#pragma once

#include "CheneyThinker.h"

class CheneyNumberClock
{
public:
	SPECIAL(CheneyNumberClock)
	void DisplayDigit(HDC, int);
	void DisplayTwoDigits(HDC, int, BOOL);
	void DisplayColon(HDC);
	void DisplayTime(HDC, BOOL, BOOL);
	BOOL f24Hour;
	BOOL fSuppress;
	int cxClient;
	int cyClient;
	TCHAR szBuffer[2];
};

#endif