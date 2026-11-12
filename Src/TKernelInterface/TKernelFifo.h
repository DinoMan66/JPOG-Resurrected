// TGenericFifo - fixed item size ring buffer guarded by a critical section and two semaphores.
// Kernel-internal declaration. Layout reconstructed from Create/Push/Pop.
#ifndef TKERNELFIFO_H
#define TKERNELFIFO_H
#include <windows.h>

namespace Toshi {

class __declspec(dllexport) TGenericFifo
{
public:
    bool Create(void* buffer, int count, int itemSize);
    bool Destroy();
    bool Push(const void* item, unsigned int flags);    // flags bit 0: do not wait when the fifo is full
    bool Pop(void* item, unsigned int flags);           // flags bit 0: do not wait when the fifo is empty

private:
    CRITICAL_SECTION m_oSection;        // +0x00
    HANDLE m_hFreeSlots;                // +0x18 (counts the free items)
    HANDLE m_hUsedSlots;                // +0x1C (counts the queued items)
    int m_iItemSize;                    // +0x20
    int m_iItemCount;                   // +0x24
    unsigned char* m_pBuffer;           // +0x28
    unsigned char* m_pBufferEnd;        // +0x2C
    unsigned char* m_pReadPos;          // +0x30
    unsigned char* m_pWritePos;         // +0x34
};

} // namespace Toshi
#endif
