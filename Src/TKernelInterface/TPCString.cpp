// Z:\Toshi\Source\TKernel\TPCString.cpp - the reference-counted handle to a pooled C string.
// The class is exported as a whole (TOSHI_EXPORT_PSTRING), so the inline members of TPString.h are emitted here.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#define TOSHI_EXPORT_PSTRING
#define TOSHI_STRING_ASSIGN_NOT_INLINED
#include "TPString.h"

namespace Toshi {

void TPooledCString::Delete()
{
    delete this;
}

// Pooled strings are unique, so equal handles are equal strings; a missing handle sorts before any string.
int TPCString::Compare(const TPCString& other) const
{
    TPooledCString* mine = m_pPooled;
    TPooledCString* theirs = other.m_pPooled;
    if (mine == 0) {
        if (theirs == 0) {
            return 0;
        }
        return -1;
    }
    if (theirs == 0) {
        return 1;
    }
    if (mine == theirs) {
        return 0;
    }
    return mine->m_oString.Compare(theirs->m_oString.GetString(0), -1);
}

TCString __stdcall operator+(const TCString& a, const TPCString& b)
{
    TCString result(a);
    result += b.GetCString();
    return result;
}

} // namespace Toshi
