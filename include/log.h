#pragma once

#include "nn.h"

void socket_log(const char* str);

inline void LOG(const char* fmt, ...)
{
    va_list args;
	va_start(args, fmt);

    char buf[0x1000];
    if (nn::util::VSNPrintf(buf, 0x1000, fmt, args) > 0)
        socket_log(buf);

    va_end(args);
}
