// Z:\Toshi\Source\TKernel\TCStringPool.cpp - pool of reference-counted C strings (only the volatile lookup so far).
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TPString.h"

namespace Toshi {

// A volatile string is not registered in the pool (its pooled string has no pool to leave again).
TPCString TCStringPool::GetVolatile(const char* s)
{
    return TPCString(new TPooledCString(s, 0));
}

} // namespace Toshi
