// TPile - kernel-internal declaration: a bump allocator that grows in fixed-size blocks.
// Each block starts with a link to the next block; the usable memory follows it.
#ifndef TKERNELPILE_H
#define TKERNELPILE_H

__declspec(dllexport) void* __stdcall tmemalign(int alignment, int size);
__declspec(dllexport) void* __stdcall trealloc(void* p, int size);

namespace Toshi {

class __declspec(dllexport) TPile
{
public:
    TPile(int blockSize, int maxSize, unsigned int flags);
    ~TPile() {}

    void* RawAlloc(int size, int alignment);
    bool RawIsInside(void* address);
    void Free();
    void Reset();
    int GetWastedSpace() const;
    int GetNumAllocs() const;
    int GetNumBlocks() const;

private:
    struct Block
    {
        Block* m_pNext;
    };

    int m_iBlockSize;           // +0x00
    int m_iMaxBlocks;           // +0x04  0 = unlimited
    unsigned int m_uFlags;      // +0x08  bit 0: allocate blocks 32-byte aligned
    int m_iNumBlocks;           // +0x0C
    int m_iBlockIndex;          // +0x10  1 + index of the block being filled
    char* m_pCursor;            // +0x14
    char* m_pEnd;               // +0x18
    Block* m_pFirstBlock;       // +0x1C
    Block* m_pCurrentBlock;     // +0x20
    int m_iNumAllocs;           // +0x24
    int m_iWastedSpace;         // +0x28
};

} // namespace Toshi
#endif
