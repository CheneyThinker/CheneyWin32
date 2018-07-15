#include "CheneyApp.h"
#include "CheneyMainFrame.h"

SPECIAL_HANDLER(CheneyApp, {}, {})

CheneyApp theApp;
CheneyGraph g_hCheneyGraph;
CheneyThreadLog g_hCheneyThreadLog;

BOOL CheneyApp::InitInstance()
{
	InitCommonControls();
	/*INITCOMMONCONTROLSEX icce;
	icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icce.dwICC = ICC_WIN95_CLASSES;
	if(!::InitCommonControlsEx(&icce))
	{
		MessageBox(NULL, _T("Init Common Controls Failed!"), _T("Init Common Controls"), MB_OK);
		return FALSE;
	}
	/*BOOL bIsRegester = CheckFileRelation(_T(".thinker"), _T("thinkerfile"));
	if(!bIsRegester)
	{
		RegisterFileRelation(_T(".thinker"), _T("thinkerfile"), _T("C:\\Users\\DELL\\Documents\\Visual Studio 2010\\Projects\\NEW\\CheneyThinker\\Release\\CheneyThinker.exe"));
	}
	LPTSTR lpszCommandName = GetCommandLine();
	CString strCommandName = lpszCommandName;
	int nOrder = strCommandName.Find(_T("\" \""));  
	if(nOrder>=0)
	{
		int l1 = strCommandName.Find("\"", 0);
		int l2 = strCommandName.Find("\"", l1+1);
		int l3 = strCommandName.Find("\"", l2+1);
		int l4 = strCommandName.Find("\"", l3+1);
		CString strFileName = strCommandName.Mid(l3+1, l4-(l3+1));
		g_hCheneyGraph.GetCheneyGraphFromFile(strFileName.GetBuffer(0));
	}*/
	CheneyMainFrame* pMainWnd = new CheneyMainFrame();
	assert(pMainWnd);
	m_pMainWnd = pMainWnd;
	int width = (3 * GetSystemMetrics(SM_CXSCREEN)) >> 2;
	int height = (3 * GetSystemMetrics(SM_CYSCREEN)) >> 2;
	BOOL flag = pMainWnd->CreateEx(0, _T("CHENEYMAINFRAME"), _T("CheneyThinker"), WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL);
	if(flag == FALSE)
	{
		MessageBox(NULL, _T("Create Window Failed!"), _T("Create Window"), MB_OK);
		return FALSE;
	}
	pMainWnd->ShowWindow(SW_SHOW);
	pMainWnd->UpdateWindow();
	return TRUE;
}

BOOL CheneyApp::ExitInstance()
{
	CheneyWnd* temp = (CheneyWnd*) m_pMainWnd;
	FREEP(temp)
	return TRUE;
}