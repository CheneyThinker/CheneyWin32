#ifndef STDAFX_H_INCLUDE
#define STDAFX_H_INCLUDE
#pragma once

#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#define _WIN32_WINNT	0x0500
#define WINVER			0X0500

#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <atlstr.h>
#include <atlimage.h>
#include <vector>
using namespace std;
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
#include <sapi.h>
#pragma comment(lib, "sapi.lib")
#include <sphelper.h>
#pragma comment(lib, "ole32.lib")

#define MAX_LOADSTRING			100
#define DRAW_MODE_SPREAD		0
#define DRAW_MODE_CENTENT		1
#define DRAW_MODE_ELONGGATE		2
#define MAX_LEN					1024
#define WM_CHENEYTHINKER		WM_USER + 1

#endif