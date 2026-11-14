// Z:\Toshi\Source\TKernel\TWStringPool.cpp - pool of reference-counted wide strings (only the volatile lookup so far).
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TPString.h"

namespace Toshi {

// A volatile string is not registered in the pool (its pooled string has no pool to leave again).
TPWString TWStringPool::GetVolatile(const TWChar* s)
{
    return TPWString(new TPooledWString(s, 0));
}

} // namespace Toshi
