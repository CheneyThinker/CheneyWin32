#include "CheneyThreadLog.h"
#include "CheneyGlobal.h"
#include "CheneyMainFrame.h"

SPECIAL_HANDLER(CheneyThreadLog, {}, {})

void CheneyThreadLog::run()
{
	CheneyMainFrame* pMain = (CheneyMainFrame*)getGlobalThinkerApp()->m_pMainWnd;
	if(pMain)
	{
		/*CheneyLogListCtrl& listCtrl = pMain->m_hCheneyLogListCtrl;
		if(listCtrl.m_hWnd)
		{
			static int i = 0;
			CString str;
			str.Format(_T("Log %d"), i++);
			listCtrl.AddLog(str);
		}*/
	}
	Sleep(1000);
}