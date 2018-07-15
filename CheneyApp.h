#ifndef CHENEYAPP_H_INCLUDE
#define CHENEYAPP_H_INCLUDE	
#pragma once
	
#include "ThinkerApp.h"
#include "CheneyGraph.h"
#include "CheneyThreadLog.h"

class CheneyApp : public ThinkerApp
{
public:
	SPECIAL(CheneyApp)
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
};

extern CheneyApp theApp;
extern CheneyGraph g_hCheneyGraph;
extern CheneyThreadLog g_hCheneyThreadLog;

#endif