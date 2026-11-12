// Z:\Toshi\Source\TKernel\TFreeList.cpp - fixed-size block allocator (simple members only).
#define TOSHI_API __declspec(dllexport)
#include "TFreeList.h"

namespace Toshi {

TFreeList::TFreeList(int blockSize, int initial, int grow, char* name)
{
    m_iCapacity = 0;
    m_iBlockSize = blockSize;
    m_pFree = 0;
    m_pBlocks = 0;
    if (grow < 1) {
        grow = 8;
    }
    m_iGrowSize = grow;
    SetCapacity(initial);
}

TFreeList::~TFreeList()
{
    void* block = m_pBlocks;
    while (block != 0) {
        m_pBlocks = *(void**)block;
        tfree(block);
        block = m_pBlocks;
    }
}

int TFreeList::GetCapacity() const
{
    return m_iCapacity;
}

// Carves a new block of 'count' units: all but the last go onto the free list, the last is returned.
TFreeList::Node* TFreeList::Allocate(int count, unsigned int blockSize)
{
    m_iCapacity += count;
    void** block = (void**)tmalloc(blockSize * count + 4, 0, -1);
    *block = m_pBlocks;
    m_pBlocks = block;
    char* unit = (char*)(block + 1);
    Node* previous = 0;
    for (int i = 0; i < count - 1; i++) {
        ((Node*)unit)->m_pNext = previous;
        previous = (Node*)unit;
        unit += blockSize;
    }
    m_pFree = previous;
    return (Node*)unit;
}

int TFreeList::GetGrowSize() const
{
    return m_iGrowSize;
}

void TFreeList::SetGrowSize(int grow)
{
    m_iGrowSize = (grow > 0) ? grow : 8;
}

void* TFreeList::New(unsigned int size)
{
    if (size != m_iBlockSize) {
        return tmalloc(size, 0, -1);
    }
    Node* node = m_pFree;
    if (node == 0) {
        return Allocate(m_iGrowSize, size);
    }
    m_pFree = node->m_pNext;
    return node;
}

void TFreeList::SetCapacity(int capacity)
{
    if (m_iCapacity >= capacity) {
        return;
    }
    Node* node = Allocate(capacity - m_iCapacity, m_iBlockSize);
    node->m_pNext = m_pFree;
    m_pFree = node;
}

void TFreeList::Delete(void* p)
{
    Node* node = (Node*)p;
    if (m_pFree) {
        node->m_pNext = m_pFree;
        m_pFree = node;
    } else {
        m_pFree = node;
        node->m_pNext = 0;
    }
}

} // namespace Toshi
