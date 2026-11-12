// Z:\Toshi\Source\TKernel\TFifo.cpp - thread safe ring buffer.
#define TOSHI_API __declspec(dllexport)
#include "TKernelFifo.h"

namespace Toshi {

bool TGenericFifo::Create(void* buffer, int count, int itemSize)
{
    m_iItemSize = itemSize;
    m_iItemCount = count;
    m_pBuffer = (unsigned char*)buffer;
    m_pBufferEnd = (unsigned char*)buffer + itemSize * count;
    m_pReadPos = (unsigned char*)buffer;
    m_pWritePos = (unsigned char*)buffer;
    m_hFreeSlots = CreateSemaphoreA(0, count, count, 0);
    m_hUsedSlots = CreateSemaphoreA(0, 0, m_iItemCount, 0);
    InitializeCriticalSection(&m_oSection);
    return true;
}

bool TGenericFifo::Destroy()
{
    DeleteCriticalSection(&m_oSection);
    CloseHandle(m_hUsedSlots);
    m_hUsedSlots = 0;
    CloseHandle(m_hFreeSlots);
    m_hFreeSlots = 0;
    return true;
}

bool TGenericFifo::Push(const void* item, unsigned int flags)
{
    bool signalled;
    if ((flags & 1) != 0) {
        signalled = WaitForSingleObject(m_hFreeSlots, 0) == WAIT_OBJECT_0;
    } else {
        signalled = WaitForSingleObject(m_hFreeSlots, INFINITE) == WAIT_OBJECT_0;
    }
    if (!signalled) {
        return false;
    }
    EnterCriticalSection(&m_oSection);
    const unsigned char* source = (const unsigned char*)item;
    unsigned char* destination = m_pWritePos;
    for (int remaining = m_iItemSize; remaining != 0; remaining--) {
        *destination++ = *source++;
    }
    if (m_pWritePos + m_iItemSize == m_pBufferEnd) {
        m_pWritePos = m_pBuffer;
    } else {
        m_pWritePos = m_pWritePos + m_iItemSize;
    }
    LeaveCriticalSection(&m_oSection);
    ReleaseSemaphore(m_hUsedSlots, 1, 0);
    return true;
}

bool TGenericFifo::Pop(void* item, unsigned int flags)
{
    bool signalled;
    if ((flags & 1) != 0) {
        signalled = WaitForSingleObject(m_hUsedSlots, 0) == WAIT_OBJECT_0;
    } else {
        signalled = WaitForSingleObject(m_hUsedSlots, INFINITE) == WAIT_OBJECT_0;
    }
    if (!signalled) {
        return false;
    }
    EnterCriticalSection(&m_oSection);
    const unsigned char* source = m_pReadPos;
    unsigned char* destination = (unsigned char*)item;
    for (int remaining = m_iItemSize; remaining != 0; remaining--) {
        *destination++ = *source++;
    }
    if (m_pReadPos + m_iItemSize == m_pBufferEnd) {
        m_pReadPos = m_pBuffer;
    } else {
        m_pReadPos = m_pReadPos + m_iItemSize;
    }
    LeaveCriticalSection(&m_oSection);
    ReleaseSemaphore(m_hFreeSlots, 1, 0);
    return true;
}

} // namespace Toshi
