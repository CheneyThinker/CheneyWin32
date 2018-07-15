#ifndef CHENEYCRITICALSECTION_H_INCLUDE
#define CHENEYCRITICALSECTION_H_INCLUDE
#pragma once

#include "StdAfx.h"
#include "CheneyThinkerDef.h"

class CheneyCriticalSection
{
public:
	SPECIAL(CheneyCriticalSection)
	void Lock();
	void UnLock();
	CRITICAL_SECTION m_cs;
};

#endif