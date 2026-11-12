// Z:\Toshi\Source\TKernel\TPile.cpp
#define TOSHI_API __declspec(dllexport)
#include "TMemory.h"
#include "TKernelPile.h"

namespace Toshi {

TPile::TPile(int blockSize, int maxSize, unsigned int flags)
{
    m_iBlockSize = blockSize;
    m_iMaxBlocks = maxSize / blockSize;
    m_uFlags = flags;
    m_iNumBlocks = 0;
    m_iBlockIndex = 0;
    m_pCursor = 0;
    m_pEnd = 0;
    m_pFirstBlock = 0;
    m_pCurrentBlock = 0;
    m_iNumAllocs = 0;
    m_iWastedSpace = 0;
}

// Note: the original scales the block size by sizeof(int) here (pointer arithmetic on int*),
// which looks unintended; kept as is.
bool TPile::RawIsInside(void* address)
{
    for (Block* block = m_pFirstBlock; block != 0; block = block->m_pNext)
    {
        if (address > block && address < (int*)block + m_iBlockSize)
        {
            return true;
        }
    }
    return false;
}

void TPile::Free()
{
    while (m_pFirstBlock != 0)
    {
        Block* next = m_pFirstBlock->m_pNext;
        tfree(m_pFirstBlock);
        m_pFirstBlock = next;
    }
    m_iNumBlocks = 0;
    Reset();
}

void TPile::Reset()
{
    if (m_pFirstBlock != 0)
    {
        m_pCursor = (char*)m_pFirstBlock + sizeof(Block);
        m_pEnd = (char*)m_pFirstBlock + sizeof(Block) + m_iBlockSize;
        m_iBlockIndex = 1;
    }
    else
    {
        m_pCursor = 0;
        m_pEnd = 0;
        m_iBlockIndex = 0;
    }
    m_pCurrentBlock = m_pFirstBlock;
    m_iNumAllocs = 0;
    m_iWastedSpace = 0;
}

void* TPile::RawAlloc(int size, int alignment)
{
    m_iNumAllocs++;
    char* aligned = (char*)(((int)m_pCursor + alignment - 1) & ~(alignment - 1));
    m_pCursor = aligned + size;
    if (m_pCursor > m_pEnd)
    {
        int index;
        Block* block;
        if (m_iBlockIndex < m_iNumBlocks)
        {
            // reuse a block left over from before the last Reset
            block = m_pCurrentBlock->m_pNext;
            m_pCurrentBlock = block;
            index = m_iBlockIndex;
        }
        else
        {
            if (m_iMaxBlocks != 0 && m_iNumBlocks >= m_iMaxBlocks)
            {
                return 0;
            }
            if ((m_uFlags & 1) != 0)
            {
                block = (Block*)tmemalign(32, (m_iBlockSize + 0x23) & ~0x1f);
            }
            else
            {
                block = (Block*)tmalloc(m_iBlockSize + sizeof(Block), 0, -1);
            }
            block->m_pNext = 0;
            if (m_pCurrentBlock != 0)
            {
                m_pCurrentBlock->m_pNext = block;
            }
            else
            {
                m_pFirstBlock = block;
            }
            m_pCurrentBlock = block;
            index = m_iBlockIndex;
            m_iNumBlocks++;
        }
        m_pEnd = (char*)block + m_iBlockSize + sizeof(Block);
        aligned = (char*)(((int)block + alignment + 3) & ~(alignment - 1));
        m_iBlockIndex = index + 1;
        m_pCursor = aligned + size;
    }
    return aligned;
}

int TPile::GetWastedSpace() const
{
    return m_iWastedSpace;
}

int TPile::GetNumAllocs() const
{
    return m_iNumAllocs;
}

int TPile::GetNumBlocks() const
{
    return m_iNumBlocks;
}

} // namespace Toshi
