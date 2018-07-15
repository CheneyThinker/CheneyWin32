#include "CheneyThread.h"

SPECIAL_HANDLER(CheneyThread, {
	m_hThread = NULL;
	m_bExit = FALSE;
	m_dwMilliseconds = INFINITE;
}, {})

void CheneyThread::Start()
{
	DWORD dwThreadID = 0;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, this, 0, &dwThreadID);
	assert(hThread);
	m_hThread = hThread;
}

DWORD CheneyThread::ThreadProc(LPVOID lParam)
{
	CheneyThread* pThread = (CheneyThread*)lParam;
	assert(pThread);
	while(!pThread->m_bExit)
	{
		pThread->run();
	}
	return 1;
}

void CheneyThread::run()
{
	Sleep(100);
	return;
}

void CheneyThread::Stop()
{
	if(m_hThread)
	{
		m_bExit = TRUE;
		WaitForSingleObject(m_hThread, m_dwMilliseconds);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

void CheneyThread::SetThreadData(DWORD dwParam)
{
	if(m_dwParam != dwParam)
	{
		m_dwParam = dwParam;
	}
}

DWORD CheneyThread::GetThreadData()
{
	return m_dwParam;
}