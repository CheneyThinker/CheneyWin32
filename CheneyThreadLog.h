#ifndef CHENEYTHREADLOG_H_INCLUDE
#define CHENEYTHREADLOG_H_INCLUDE
#pragma once

#include "CheneyThread.h"

class CheneyThreadLog : public CheneyThread
{
public:
	SPECIAL(CheneyThreadLog)
	virtual void run();
};

#endif