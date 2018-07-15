#include "ThinkerApp.h"
#include "CheneyGlobal.h"

SPECIAL_HANDLER(ThinkerApp, {
	m_pMainWnd = NULL;
	g_ThinkerApp = this;
}, {})

BOOL ThinkerApp::InitInstance()
{
	return TRUE;
}

void ThinkerApp::StartUp()
{
	MSG messages;
	while(GetMessage(&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
}

BOOL ThinkerApp::ExitInstance()
{
	return TRUE;
}