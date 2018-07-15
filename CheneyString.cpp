#include "CheneyString.h"

unsigned int CheneyString::refCount = 0;

SPECIAL_HANDLER(CheneyString,{
	buffer = new char[1];
    *buffer = '\0';
    length = 0;
    refCount++;
},{
	delete[] buffer;
	buffer = NULL;
	length = 0;
    refCount--;
})

size_t CheneyString::strlcpy(char *dst, const char *src, size_t siz)
{
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;
	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}
	if (n == 0) {
		if (siz != 0)
			*d = '\0';
		while (*s++)
			;
	}
	return(s - src - 1);
}

size_t CheneyString::strlcat(char *dst, const char *src, size_t siz)
{
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;
	size_t dlen;
	while (*d != '\0' && n-- != 0)
		d++;
	dlen = d - dst;
	n = siz - dlen;
	if (n == 0)
		return(dlen + strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return(dlen + (s - src));
}

CheneyString::CheneyString(const char* str)
{
    if(NULL == str)
    {
        buffer = new char[1];
        *buffer = '\0';
        length = 0;
    }
    else
    {
        length = strlen(str);
        buffer = new char[length + 1];
        strlcpy(buffer, str, length + 1);
    }
    refCount++;
}

CheneyString::CheneyString(const CheneyString &str)
{
    length = str.length;
    buffer = new char[length + 1];
	strcpy_s(buffer, sizeof(buffer), str.buffer);
    refCount++;
}

CheneyString &CheneyString::operator=(const CheneyString &str)
{
    if(this != &str)
    {
        if(length > str.length)
        {
            length = str.length;
            strcpy_s(buffer, sizeof(buffer), str.buffer);
        }
        else
        {
            delete[] buffer;
            length = str.length;
            buffer = new char[length + 1];
            strcpy_s(buffer, sizeof(buffer), str.buffer);
        }
    }
    return *this;
}

CheneyString &CheneyString::operator=(const char* str)
{
    if(NULL != str)
    {
        unsigned int len = strlen(str);
        if(length > len)
        {
            length = len;
            strcpy_s(buffer, sizeof(buffer), str);
        }
        else
        {
            delete[] buffer;
            length = len;
            buffer = new char[length + 1];
            strcpy_s(buffer, sizeof(buffer), str);
        }
    }
    return *this;
}

CheneyString &CheneyString::operator+=(const CheneyString &str)
{
    char* temp = buffer;
    int len = length;
    length += str.length;
    buffer = new char[length + 1];
    strcpy_s(buffer, sizeof(buffer), temp);
    if(this != &str)
    {
        strcpy_s(buffer + len, sizeof(buffer), str.buffer);
    }
    else
    {
        strcpy_s(buffer + len, sizeof(buffer), temp);
    }
    delete[] temp;
    temp = NULL;
    return *this;
}

CheneyString &CheneyString::operator+=(const char* str)
{
    if(NULL != str)
    {
        char* temp = buffer;
        int len = length;
        length += strlen(str);
        buffer = new char[length + 1];
        strcpy_s(buffer, sizeof(buffer), temp);
        strcpy_s(buffer + len, sizeof(buffer), str);
        delete[] temp;
        temp = NULL;
    }
    return *this;
}

CheneyString &CheneyString::operator+=(const char ch)
{
    char* temp = buffer;
    int len = length;
    length += 1;
    buffer = new char[length + 1];
    strcpy_s(buffer, sizeof(buffer), temp);
    *(buffer + len) = ch;
    *(buffer + length) = '\0';
    delete[] temp;
    temp = NULL;
    return *this;
}

bool operator==(const CheneyString &str, const CheneyString &str1)
{
    return strcmp(str.buffer, str1.buffer) == 0;
}

bool operator!=(const CheneyString &str, const CheneyString &str1)
{
    return strcmp(str.buffer, str1.buffer) != 0;
}

CheneyString operator + (const CheneyString &str, const CheneyString &str1)
{
    CheneyString temp;
    delete[] temp.buffer;
    temp.length = str.length + str1.length;
    temp.buffer = new char[temp.length + 1];
    strcpy_s(temp.buffer, sizeof(temp.buffer), str.buffer);
    strcpy_s(temp.buffer + str.length, sizeof(temp.buffer), str1.buffer);
    return temp;
}

CheneyString operator + (const CheneyString &str, const char* str1)
{
    CheneyString temp;
    delete[] temp.buffer;
    if(NULL == str1)
    {
        temp.length = str.length;
        temp.buffer = new char[temp.length + 1];
		strcpy_s(temp.buffer, sizeof(temp.buffer), str.buffer);
    }
    else
    {
        temp.length = str.length + strlen(str1);
        temp.buffer = new char[temp.length + 1];
        strcpy_s(temp.buffer, sizeof(temp.buffer), str.buffer);
        strcpy_s(temp.buffer + str.length, sizeof(temp.buffer), str1);
    }
    return temp;
}

char CheneyString::operator[](unsigned int index) const
{
    return (((index >= 0) && (index < length)) ? *(buffer + index) : '\0');
}

void CheneyString::Format(const char* format, ...)
{
	va_list args;
	buffer = (char*) malloc(sizeof(char) * MAX_LEN);
	va_start(args, format);
	_vsnprintf_s(buffer, sizeof(buffer), MAX_LEN, format, args);
	va_end(args);
}