#ifndef CHENEYUTILS_H_INCLUDE
#define CHENEYUTILS_H_INCLUDE
#pragma once

#include "CheneyThinker.h"

typedef struct WMCOMMAND
{
	WORD wNotifyCode;
	WORD wID;
	HWND hwndCtrl;
} WMCOMMAND;

class CheneyUtils
{
public:
	SPECIAL(CheneyUtils)
	MSGMAP(WMCOMMAND, GetWMCommand)
	BOOL TraceLog(TCHAR* lpszFormat, ...);
};

#endif