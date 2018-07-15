#include "CheneyLogListCtrl.h"

void CheneyLogListCtrl::AddLog(CString strLog)
{
	if(m_hWnd == NULL)
		return;
	m_cs.Lock();
	m_vecLog.push_back(strLog);
	m_cs.UnLock();
	PostMessage(m_hWnd, WM_CHENEYTHINKER, 0, 0);
}

SPECIAL_HANDLER(CheneyLogListCtrl, {
	hMathDLL = LoadLibrary("Math");
	GETFUN(Math, Add)
	GETFUN(Math, Sub)
}, {
	FreeLibrary(hMathDLL);
})

MESSAGE_MAP_HANDLER(CheneyLogListCtrl, Create, {
	ThinkerRect rcClient;
	GetClientRect(rcClient);
	InsertColumn(0, _T("运行日志"), rcClient.Width());
	SetTextColor(RGB(255, 0, 0));
	return TRUE;
})

MESSAGE_MAP_HANDLER(CheneyLogListCtrl, Size, {
	ThinkerRect rcClient;
	GetClientRect(rcClient);
	SetColumnWidth(0, rcClient.Width());
	return TRUE;
})

MESSAGE_MAP_HANDLER(CheneyLogListCtrl, CheneyThinker, {
	assert(m_hWnd);
	int nItemCount = GetItemCount();
	if(nItemCount > 10)
	{
		DeleteAllItems();
		nItemCount = 0;
	}
	m_cs.Lock();
	if(m_vecLog.size() > 0)
	{
		CString strLog = m_vecLog.at(0);
		m_vecLog.erase(m_vecLog.begin());
		SYSTEMTIME st;
		GetLocalTime(&st);
		CString strTime;
		strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		CheneyString m_str;
		m_str.Format(_T("%d %s %s add=%d,sub=%d"), nItemCount + 1, strTime, strLog, Add(2, 3), Sub(30, 2));
		InsertItem(nItemCount, m_str.GetBuffer());
		CheneyUtils utils;
		utils.TraceLog(_T("%s"), m_str.GetBuffer());
	}
	m_cs.UnLock();
	return TRUE;
})