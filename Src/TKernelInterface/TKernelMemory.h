// TMemory - the kernel's memory manager. Kernel-internal declaration; only the small, self-contained members
// are written so far (node flag helpers, the system allocation wrappers and the empty debug hooks).
// Layout evidence: Initialise() builds the manager; MemBlockSlot is the 16 byte element of the slot table at +0x20.
#ifndef TKERNELMEMORY_H
#define TKERNELMEMORY_H
#include "TNodeList.h"

namespace Toshi {

class TFile;

class __declspec(dllexport) TMemory
{
public:
    // Small bookkeeping header in front of every allocation. Only the flag word at +4 is read so far:
    // bit 0 = process (allocated) node, bits 2..26 = node size, upper bits = slot index of the owning block.
    class MemNode
    {
    public:
        unsigned int m_uUnknown00;      // +0x00 (not read by any member written so far)
        unsigned int m_uFlags;          // +0x04
    };

    // Table entry owned by the manager: a list node with the memory block it belongs to.
    class __declspec(dllexport) MemBlockSlot : public TNodeList<MemBlockSlot>::TNode
    {
    public:
        MemBlockSlot() {}
        ~MemBlockSlot() {}
        // operator= is the implicit member-wise copy (exported through the class).

        class MemBlock* m_pBlock;       // +0x0C
    };

    // Memory block header, found right behind its MemNode; carries the "#MB_uID" signature at +0x38.
    class MemBlock
    {
    public:
        MemBlockSlot* m_pSlot;          // +0x00
        unsigned char m_aPad04[0x34];   // +0x04
        char m_szId[8];                 // +0x38
    };

    struct MemInfo;
    struct HALMemInfo
    {
        unsigned int m_aFields[21];     // 0x54 bytes, cleared by GetHALMemInfo
    };

    static bool __stdcall IsDebug();
    static bool __stdcall IsInitialised();
    static void __stdcall SetHoleSize(MemNode* node, unsigned int size);
    static bool __stdcall IsProcess(MemNode* node);
    static void __stdcall ExtendNodeSize(MemNode* node, unsigned int size);
    static unsigned int __stdcall GetNodeSize(MemNode* node);
    static void __stdcall ConvertProcessToHole(MemNode* node);
    static MemNode* __stdcall GetMemNodeFromAddress(void* address);
    static MemBlock* __stdcall IsMemNodeMB(MemNode* node);
    static MemNode* __stdcall IsAllocMB(void* address);
    static unsigned int __stdcall MapSizeToFreeList(unsigned int size);
    static void __stdcall SetProcess(MemBlock* block, MemNode* node, unsigned int size);
    static void* __stdcall SysAlloc(unsigned int size);
    static void __stdcall SysFree(void* address);
    static TMemory& __stdcall GetMemManager();
    static MemBlock* __stdcall GetGlobalBlock();
    static unsigned int __stdcall GetMarkedHALPhysical();
    static void __stdcall MarkHALPhysical();
    static void __stdcall GetHALMemInfo(HALMemInfo& info);
    static void __stdcall DebugPrintHALMemInfoToFile(HALMemInfo& info, TFile* file, const char* title);
    static void __stdcall DebugPrintHALMemInfo(const char* title);
    static void __stdcall DebugPrintFreeMemoryAt(const char* title);
    static void __stdcall DumpAllocationsToFile(TFile* file, MemBlock* block, int flags);
    static void __stdcall DumpAllocations(MemBlock* block, int flags);
    static void __stdcall MemRecurse(void (__stdcall* nodeFunc)(MemNode*),
                                     void (__stdcall* blockFunc)(MemBlock*, MemInfo*, unsigned int),
                                     MemBlock* block);

    TMemory();
    ~TMemory();

    void* Alloc(unsigned int size, unsigned int alignment, MemBlock* block, char* file, int line);
    void* Calloc(unsigned int size, unsigned int alignment, MemBlock* block, char* file, int line);
    bool Free(void* address);
    unsigned int GetSlotIndex(MemBlockSlot& slot);
    void* Realloc(void* address, unsigned int size, MemBlock* block);
    void* Recalloc(void* address, unsigned int size, MemBlock* block);

protected:
    static bool __stdcall Initialise();
    static void __stdcall DumpSKUMemoryInfo();
    static unsigned int __stdcall GetFreePhysicalMemory();
    unsigned int GetGlobalFlags();
    void Deinitialise();
    bool FreeMem(MemBlock* block);

private:
    static void __stdcall MemRecurseR(void (__stdcall* nodeFunc)(MemNode*),
                                      void (__stdcall* blockFunc)(MemBlock*, MemInfo*, unsigned int),
                                      MemBlock* block,
                                      unsigned int depth);

    static bool m_bIsDebug;
    static bool m_bInitialised;

    TNodeList<MemBlockSlot> m_oUsedSlots;   // +0x00
    TNodeList<MemBlockSlot> m_oFreeSlots;   // +0x10
    MemBlockSlot m_aSlots[32];          // +0x20 (0x200 bytes: the constructor queues 32 slots)
    void* m_pUnknown220;                // +0x220 (released with free() on shutdown)
    MemBlock* m_pGlobalBlock;           // +0x224
    unsigned int m_uGlobalFlags;        // +0x228
    unsigned int m_uMarkedHALPhysical;  // +0x22C
};

} // namespace Toshi
#endif
