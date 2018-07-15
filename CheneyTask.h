#ifndef CHENEYTASK_H_INCLUDE
#define CHENEYTASK_H_INCLUDE
#pragma once

#include "CheneyApp.h"
#include "CheneyNumberClock.h"

void HandlerOne(HWND);
void HandlerTwo(HWND);
void HandlerThree(HWND);
void HandlerFour(HWND, CheneyNumberClock);
BOOL CheckFileRelation(const TCHAR*, const TCHAR*);
void RegisterFileRelation(TCHAR*, TCHAR*, TCHAR*);

#endif