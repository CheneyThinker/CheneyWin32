#include "CheneyCriticalSection.h"

SPECIAL_HANDLER(CheneyCriticalSection, {
	InitializeCriticalSection(&m_cs);
}, {
	DeleteCriticalSection(&m_cs);
})

void CheneyCriticalSection::Lock()
{
	EnterCriticalSection(&m_cs);
}

void CheneyCriticalSection::UnLock()
{
	LeaveCriticalSection(&m_cs);
}