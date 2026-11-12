// Z:\Toshi\Source\TKernel\TRandom.cpp - TRandom construction.
// Kept in a second translation unit: the original calls SetSeed out of line from the constructor,
// while the same-file definition in TRandom.cpp would be expanded inline by the compiler.
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TKernelThreads.h"

namespace Toshi {

// Seeds the generator from the high-resolution timer.
TRandom::TRandom()
{
    THPTimer timer;
    SetSeed(timer.GetRaw32());
}

} // namespace Toshi
