#include "CheneyGlobal.h"

int WINAPI _tWinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPTSTR lpCmdLine, IN int nShowCmd)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	ThinkerApp* pThinkerApp = getGlobalThinkerApp();
	assert(pThinkerApp);
	pThinkerApp->InitInstance();
	pThinkerApp->StartUp();
	pThinkerApp->ExitInstance();
	return TRUE;
}