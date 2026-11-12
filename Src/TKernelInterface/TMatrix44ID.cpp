// Z:\Toshi\Source\TKernel\TMatrix44ID.cpp - matrix with an ID.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TKernelMatrixID.h"

namespace Toshi {

TMatrix44ID::TMatrix44ID()
{
}

unsigned int TMatrix44ID::GetID()
{
    return m_uID;
}

void TMatrix44ID::SetID(unsigned int id)
{
    m_uID = id;
}

} // namespace Toshi
