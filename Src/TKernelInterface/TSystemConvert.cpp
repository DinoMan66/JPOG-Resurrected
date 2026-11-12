// Z:\Toshi\Source\TKernel\TSystem.cpp - StringUnicodeToChar, kept in a file of its own: the original calls
// StringLength out of line here, and our compiler build would inline it from the same file (MATCHING_NOTES #23).
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <time.h>
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TCString.h"

namespace Toshi {

const char* __stdcall TSystem::StringUnicodeToChar(char* dst, const TSysWChar* src, int count)
{
    int length = StringLength(src);
    if (count > length || count == -1) {
        count = length;
    }
    int i;
    for (i = 0; i < count; i++) {
        dst[i] = (char)src[i];
    }
    dst[i] = 0;
    return dst;
}

} // namespace Toshi
