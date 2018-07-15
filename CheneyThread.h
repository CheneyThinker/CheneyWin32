#ifndef CHENEYTHREAD_H_INCLUDE
#define CHENEYTHREAD_H_INCLUDE
#pragma once

#include "CheneyThinker.h"

class CheneyThread
{
public:
	SPECIAL(CheneyThread)
	void Start();
	virtual void run();
	void Stop();
	virtual void SetThreadData(DWORD);
	virtual DWORD GetThreadData();
	static DWORD ThreadProc(LPVOID);
	HANDLE m_hThread;
	BOOL m_bExit;
	DWORD m_dwMilliseconds;
	DWORD m_dwParam;
};

#endif