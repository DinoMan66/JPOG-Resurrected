// Toshi::TFreeList - fixed-size block allocator (stub; lives in TKernelInterface.dll).
//   ??0TFreeList@Toshi@@QAE@HHHPAD@Z   TFreeList(int blockSize, int, int, char* name)
//   ??1TFreeList@Toshi@@QAE@XZ
//   ?New@TFreeList@Toshi@@QAEPAXI@Z    void* New(unsigned int size)
//   ?Delete@TFreeList@Toshi@@QAEXPAX@Z void  Delete(void* p)
// Classes that use one declare a private static ms_oFreelist plus inline class-level
// operator new/delete (see TOSHI_FREELIST_DECLARE).
#ifndef TFREELIST_H
#define TFREELIST_H
#include <stddef.h>
#include "TMemory.h"

namespace Toshi {

class TFreeList
{
public:
    TOSHI_API TFreeList(int blockSize, int initial, int grow, char* name);
    TOSHI_API ~TFreeList();
    TOSHI_API void* New(unsigned int size);
    TOSHI_API void  Delete(void* p);
    TOSHI_API int GetCapacity() const;
    TOSHI_API int GetGrowSize() const;
    TOSHI_API void SetGrowSize(int grow);
    TOSHI_API void SetCapacity(int capacity);
    struct Node
    {
        Node* m_pNext;
    };
protected:
    TOSHI_API Node* Allocate(int count, unsigned int blockSize);
private:
    int   m_iCapacity;      // +0x00
    int   m_iBlockSize;     // +0x04
    Node* m_pFree;          // +0x08
    void* m_pBlocks;        // +0x0C
    int   m_iGrowSize;      // +0x10
    unsigned char m_rest[0x0C];     // +0x14: name etc.
};

} // namespace Toshi

// Declared in this order, ICC emits them in reverse (new(file,line), new, placement new,
// delete, GetFreeList is how they appear in the binary).
#define TOSHI_FREELIST_DECLARE()                                                             \
public:                                                                                      \
    static Toshi::TFreeList& GetFreeList() { return ms_oFreelist; }                          \
    static void operator delete(void* p) { ms_oFreelist.Delete(p); }                         \
    static void* operator new(size_t, void* p) { return p; }                                 \
    static void* operator new(size_t size) { return ms_oFreelist.New(size); }               \
    static void* operator new(size_t size, char*, int) { return ms_oFreelist.New(size); }   \
private:                                                                                     \
    static Toshi::TFreeList ms_oFreelist;                                                    \
public:

#endif
