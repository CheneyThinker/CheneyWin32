#ifndef CHENEYSTRING_H_INCLUDE
#define CHENEYSTRING_H_INCLUDE
#pragma once

#include "CheneyThinker.h"

class CheneyString
{
public:
	SPECIAL(CheneyString)
    explicit CheneyString(const char*);
    CheneyString(const CheneyString& str);
	size_t strlcpy(char*, const char*, size_t);
	size_t strlcat(char*, const char*, size_t);
    inline unsigned int Length() const { return length; }
    CheneyString &operator = (const CheneyString&);
    CheneyString &operator = (const char*);
    CheneyString &operator += (const CheneyString&);
    CheneyString &operator += (const char*);
    CheneyString &operator += (const char);
    friend bool operator == (const CheneyString&, const CheneyString&);
    friend bool operator != (const CheneyString&, const CheneyString&);
    friend CheneyString operator + (const CheneyString&, const CheneyString&);
    friend CheneyString operator + (const CheneyString&, const char*);
    char operator [] (unsigned int) const;
    static unsigned int getRefCount() { return refCount; }
    char* GetBuffer() const { return buffer; }
	void Format(const char*, ...);
private:
    char* buffer;
    unsigned int length;
    static unsigned int refCount;
};

#endif