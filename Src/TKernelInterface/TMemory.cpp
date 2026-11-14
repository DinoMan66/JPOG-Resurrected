// Z:\Toshi\Source\TKernel\TMemory.cpp - memory manager.
// Written so far: node flag helpers, system allocation wrappers, accessors and the empty debug hooks.
// Not written: the allocator proper (Alloc, Free, AllocMem, FreeMem, Initialise, ...), SetProcess and
// GetProcessMemBlock, MapSizeToFreeList, MemRecurse and the integrity / info dumps.
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TKernelMemory.h"
#include "TKernelThreads.h"
#include <stdlib.h>
#include <windows.h>

namespace Toshi {

// Index of the size-class free list: log2 of the rounded size via the float exponent, two classes per
// doubling folded into one, clamped to 8 (0 means 'no free list').
unsigned int __stdcall TMemory::MapSizeToFreeList(unsigned int size)
{
    float rounded = (float)(int)(((size + 3) & ~3) - 1);
    int exponent = *(int*)&rounded >> 23;
    unsigned int index = exponent - 0x7f;
    if (index & 1) {
        index = exponent - 0x7e;
    }
    index >>= 1;
    if (index >= 1) {
        index--;
        if (index >= 9) {
            index = 8;
        }
    }
    return index;
}

bool TMemory::m_bIsDebug;
bool TMemory::m_bInitialised;
static TMutex* s_pMutex;          // 0x10043040
static TMemory* s_pMemManager;

void* TMemory::Calloc(unsigned int size, unsigned int alignment, MemBlock* block, char* file, int line)
{
    Initialise();
    TMutexLock lock(s_pMutex);
    void* memory = Alloc(size, alignment, block, 0, -1);
    if (memory != 0) {
        TSystem::MemSet(memory, 0, size);
    }
    return memory;
}

void TMemory::Deinitialise()
{
    if (m_bInitialised == true) {
        m_bInitialised = false;
        FreeMem(s_pMemManager->m_pGlobalBlock);
        s_pMutex->Destroy();
        free(s_pMutex);
        s_pMutex = 0;
        free(s_pMemManager->m_pUnknown220);
        free(s_pMemManager);
    }
}

bool __stdcall TMemory::IsDebug()
{
    return m_bIsDebug;
}

bool __stdcall TMemory::IsInitialised()
{
    return m_bInitialised;
}

TMemory::TMemory()
{
    for (unsigned int i = 0; i < 32; i++) {
        m_aSlots[i].m_pBlock = 0;
        m_oFreeSlots.InsertTail(&m_aSlots[i]);
    }
}

TMemory::~TMemory()
{
}

unsigned int TMemory::GetSlotIndex(MemBlockSlot& slot)
{
    return &slot - m_aSlots;
}

void __stdcall TMemory::SetHoleSize(MemNode* node, unsigned int size)
{
    node->m_uFlags = size;
}

bool __stdcall TMemory::IsProcess(MemNode* node)
{
    if ((node->m_uFlags & 1) != 0) {
        return true;
    }
    return false;
}

void __stdcall TMemory::ExtendNodeSize(MemNode* node, unsigned int size)
{
    node->m_uFlags = (node->m_uFlags & 0xF8000003) | size;
}

unsigned int __stdcall TMemory::GetNodeSize(MemNode* node)
{
    return node->m_uFlags & 0x7FFFFFC;
}

void __stdcall TMemory::ConvertProcessToHole(MemNode* node)
{
    node->m_uFlags = node->m_uFlags & 0x7FFFFFC;
}

unsigned int TMemory::GetGlobalFlags()
{
    return m_uGlobalFlags;
}

TMemory::MemNode* __stdcall TMemory::GetMemNodeFromAddress(void* address)
{
    if (((unsigned int)address & 3) == 0) {
        if (address != 0) {
            return (MemNode*)address - 1;
        }
    }
    return 0;
}

TMemory::MemBlock* __stdcall TMemory::IsMemNodeMB(MemNode* node)
{
    MemBlock* block = (MemBlock*)(node + 1);
    if (TSystem::StringCompare(block->m_szId, "#MB_uID", -1) == 0) {
        return block;
    }
    return 0;
}

TMemory::MemNode* __stdcall TMemory::IsAllocMB(void* address)
{
    MemBlock* block = (MemBlock*)address;
    if (TSystem::StringCompare(block->m_szId, "#MB_uID", -1) == 0) {
        return (MemNode*)address - 1;
    }
    return 0;
}

void* __stdcall TMemory::SysAlloc(unsigned int size)
{
    return GlobalAlloc(GPTR, size);
}

void __stdcall TMemory::SysFree(void* address)
{
    GlobalFree(address);
}

TMemory& __stdcall TMemory::GetMemManager()
{
    Initialise();
    return *s_pMemManager;
}

TMemory::MemBlock* __stdcall TMemory::GetGlobalBlock()
{
    Initialise();
    return s_pMemManager->m_pGlobalBlock;
}

unsigned int __stdcall TMemory::GetMarkedHALPhysical()
{
    Initialise();
    return s_pMemManager->m_uMarkedHALPhysical;
}

void __stdcall TMemory::MarkHALPhysical()
{
    Initialise();
}

void __stdcall TMemory::GetHALMemInfo(HALMemInfo& info)
{
    TSystem::MemSet(&info, 0, sizeof(HALMemInfo));
}

unsigned int __stdcall TMemory::GetFreePhysicalMemory()
{
    return 0x8000000;
}

void __stdcall TMemory::DumpSKUMemoryInfo()
{
}

void __stdcall TMemory::DebugPrintHALMemInfoToFile(HALMemInfo& info, TFile* file, const char* title)
{
}

void __stdcall TMemory::DebugPrintHALMemInfo(const char* title)
{
}

void __stdcall TMemory::DebugPrintFreeMemoryAt(const char* title)
{
}

void __stdcall TMemory::DumpAllocationsToFile(TFile* file, MemBlock* block, int flags)
{
}

void __stdcall TMemory::DumpAllocations(MemBlock* block, int flags)
{
}

void* TMemory::Realloc(void* address, unsigned int size, MemBlock* block)
{
    return 0;
}

void* TMemory::Recalloc(void* address, unsigned int size, MemBlock* block)
{
    return 0;
}

// Walks every memory block with the process mutex held.
void __stdcall TMemory::MemRecurse(void (__stdcall* nodeFunc)(MemNode*),
                                   void (__stdcall* blockFunc)(MemBlock*, MemInfo*, unsigned int),
                                   MemBlock* block)
{
    TMutexLock lock(s_pMutex);
    MemRecurseR(nodeFunc, blockFunc, block, 0);
}

} // namespace Toshi
