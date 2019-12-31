#pragma once

#include "types.h"

namespace nn { namespace util {

s32 SNPrintf(char* s, size_t n, const char* format, ...);
s32 VSNPrintf(char* s, size_t n, const char* format, va_list arg);

} }
