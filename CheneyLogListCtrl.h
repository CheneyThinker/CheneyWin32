#ifndef CHENEYLOGLISTCTRL_H_INCLUDE
#define CHENEYLOGLISTCTRL_H_INCLUDE
#pragma once

#include "CheneyListCtrl.h"
#include "CheneyString.h"
#include "CheneyUtils.h"

class CheneyLogListCtrl : public CheneyListCtrl
{
public:
	SPECIAL(CheneyLogListCtrl)
	CheneyCriticalSection m_cs;
	vector<CString> m_vecLog;
	HINSTANCE hMathDLL;
	void AddLog(CString);
	MESSAGE_MAP(Create)
	MESSAGE_MAP(Size)
	MESSAGE_MAP(CheneyThinker)
	DLLLIBRARY(Add)
	DLLLIBRARY(Sub)
};

#endif