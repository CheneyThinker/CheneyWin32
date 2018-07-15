#ifndef CHENEYDIALOG_H_INCLUDE
#define CHENEYDIALOG_H_INCLUDE
#pragma once

#include "CheneyThinker.h"

DECLARE_WNDPROC(BOOL, DlgProc)

class CheneyDialog
{
public:
	SPECIAL(CheneyDialog)
	virtual int CreateCheneyDialog(HWND);
};

#endif