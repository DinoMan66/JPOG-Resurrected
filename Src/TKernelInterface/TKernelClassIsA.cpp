// Z:\Toshi\Source\TKernel\TClass.cpp - TClass::IsA, kept in a file of its own: the original calls IsExactly
// out of line here, and our compiler build would inline it from the same file (MATCHING_NOTES #23).
#define TOSHI_API __declspec(dllexport)
#include "TKernelClass.h"
#include "TKernelObject.h"
#include "TKernelMisc.h"

namespace Toshi {

bool TClass::IsA(const TClass& other) const
{
    for (const TClass* cls = this; cls != 0; cls = cls->m_pParent)
    {
        if (cls->IsExactly(other) == true)
        {
            return true;
        }
    }
    return false;
}

} // namespace Toshi
