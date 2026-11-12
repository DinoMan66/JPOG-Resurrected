// Z:\Toshi\Source\TKernel\TMutexLock.cpp
#define TOSHI_API __declspec(dllexport)
#include "TKernelThreads.h"

namespace Toshi {

void TMutexLock::Create(TMutex* mutex)
{
    m_pMutex = mutex;
    mutex->Lock(0);
}

void TMutexLock::Destroy()
{
    if (m_pMutex != 0)
    {
        m_pMutex->Unlock();
        m_pMutex = 0;
    }
}

} // namespace Toshi
