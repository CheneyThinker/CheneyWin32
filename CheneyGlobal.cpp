#include "CheneyGlobal.h"

ThinkerApp* g_ThinkerApp = NULL;
ThinkerApp* getGlobalThinkerApp()
{
	return g_ThinkerApp;
}