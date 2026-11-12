// Z:\Toshi\Source\TKernel\TSemaphore.cpp
#define TOSHI_API __declspec(dllexport)
#include "TKernelThreads.h"

namespace Toshi {

bool TSemaphore::Create(int initialCount, int maxCount)
{
    m_hSemaphore = CreateSemaphoreA(0, initialCount, maxCount, 0);
    return true;
}

bool TSemaphore::Destroy()
{
    BOOL closed = CloseHandle(m_hSemaphore);
    m_hSemaphore = 0;
    return closed != 0;
}

bool TSemaphore::Poll()
{
    return WaitForSingleObject(m_hSemaphore, 0) == WAIT_OBJECT_0;
}

bool TSemaphore::Wait()
{
    return WaitForSingleObject(m_hSemaphore, INFINITE) == WAIT_OBJECT_0;
}

bool TSemaphore::Signal()
{
    return ReleaseSemaphore(m_hSemaphore, 1, 0) != 0;
}

} // namespace Toshi
