#ifndef THINKERAPP_H_INCLUDE
#define THINKERAPP_H_INCLUDE
#pragma once
	
#include "StdAfx.h"
#include "CheneyThinkerDef.h"

class ThinkerApp
{
public:
	SPECIAL(ThinkerApp)
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	virtual void StartUp();
	LPVOID m_pMainWnd;
};

#endif