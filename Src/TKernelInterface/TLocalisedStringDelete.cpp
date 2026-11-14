// Z:\Toshi\Source\TKernel\TLocale.cpp (part) - TLocalisedString::Delete.
// Kept in its own translation unit: the destructor must stay an out-of-line call here (the original
// does not inline it into Delete).
#define TOSHI_API __declspec(dllexport)
#include "TKernelLString.h"

namespace Toshi {

void TLocalisedString::Delete()
{
    delete this;
}

} // namespace Toshi
