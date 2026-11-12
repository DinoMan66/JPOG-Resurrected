// Z:\Toshi\Source\TKernel\TPool.cpp - TGenericPool.
#define TOSHI_API __declspec(dllexport)
#include "TKernelContainers.h"
#include "TMemory.h"

namespace Toshi {

TGenericPool::TNode& TGenericPool::TNode::operator=(const TNode& o)
{
    m_pNext = o.m_pNext;
    return *this;
}

TGenericPool::TBlock& TGenericPool::TBlock::operator=(const TBlock& o)
{
    m_pNext = o.m_pNext;
    return *this;
}

void TGenericPool::Free(void* p)
{
    if (p) {
        ((TNode*)p)->m_pNext = m_pFree;
        m_pFree = (TNode*)p;
    }
}

void* TGenericPool::Alloc()
{
    TNode* node = m_pFree;
    if (node == 0) {
        if (!AllocBlock()) {
            return 0;
        }
        node = m_pFree;
    }
    m_pFree = node->m_pNext;
    return node;
}

void TGenericPool::Reinit()
{
    TBlock* block = m_pBlocks;
    while (block != 0) {
        TBlock* next = block->m_pNext;
        tfree(block);
        block = next;
    }
    m_iTotalSize = 0;
    m_pBlocks = 0;
    m_pFree = 0;
}

void TGenericPool::Reset()
{
    m_pFree = 0;
    for (TBlock* block = m_pBlocks; block != 0; block = block->m_pNext) {
        ResetBlock(block);
    }
}

bool TGenericPool::AllocBlock()
{
    int total = m_iBlockSize + m_iTotalSize;
    if (m_iMaxSize == 0 || total <= m_iMaxSize) {
        TBlock* block = (TBlock*)tmalloc(m_iAlignment + m_iBlockSize, 0, -1);
        if (block != 0) {
            block->m_pNext = m_pBlocks;
            m_pBlocks = block;
            m_iTotalSize = total;
            ResetBlock(block);
            return true;
        }
    }
    return false;
}

void TGenericPool::ResetBlock(TBlock* block)
{
    // The units start after the block header, rounded up to the pool's alignment, and are chained into the
    // free list in address order.
    char* first = (char*)(((unsigned int)block + sizeof(TBlock) + m_iAlignment - 1) & ~(m_iAlignment - 1));
    char* last = first + (m_iBlockSize - m_iUnitSize);
    char* unit = first;
    while (unit != last) {
        char* next = unit + m_iUnitSize;
        ((TNode*)unit)->m_pNext = (TNode*)next;
        unit = next;
    }
    ((TNode*)last)->m_pNext = m_pFree;
    m_pFree = (TNode*)first;
}

} // namespace Toshi
