// Z:\Toshi\Source\TKernel\TMutex.cpp
#define TOSHI_API __declspec(dllexport)
#include "TKernelThreads.h"

namespace Toshi {

bool TMutex::Create()
{
    m_hMutex = CreateMutexA(0, 0, 0);
    return true;
}

bool TMutex::Destroy()
{
    BOOL closed = CloseHandle(m_hMutex);
    m_hMutex = 0;
    return closed != 0;
}

bool TMutex::Lock(unsigned int flags)
{
    DWORD result;
    if ((flags & 1) != 0)
    {
        result = WaitForSingleObject(m_hMutex, 0);
    }
    else
    {
        result = WaitForSingleObject(m_hMutex, INFINITE);
    }
    return result == WAIT_OBJECT_0;
}

bool TMutex::Unlock()
{
    return ReleaseMutex(m_hMutex) != 0;
}

} // namespace Toshi
