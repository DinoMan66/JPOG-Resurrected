// Z:\Toshi\Source\TKernel\TBitArray.cpp - bit set stored as 32-bit words.
// Not written: FindFirstSetBit, FindFirstClearBit.
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TMemory.h"

namespace Toshi {

TBitArray::TBitArray(int size, int initialValue)
{
    Create(size, initialValue);
}

TBitArray::TBitArray()
{
    m_pBuffer = 0;
    m_iSize = 0;
    m_uFill = 0;
}

TBitArray::~TBitArray()
{
    Destroy();
}

bool TBitArray::Create(int size, int initialValue)
{
    m_iSize = size;
    m_uFill = (initialValue != 0) ? 0xffffffff : 0;
    m_pBuffer = (unsigned int*)tmalloc(((size + 31) >> 5) * 4, 0, -1);
    Reset();
    return true;
}

void TBitArray::Reset()
{
    int wordCount = (m_iSize + 31) >> 5;
    for (int i = 0; i < wordCount; i++) {
        m_pBuffer[i] = m_uFill;
    }
}

void TBitArray::SetBit(int index, int value)
{
    unsigned int* buffer = m_pBuffer;
    int word = index >> 5;
    if (value == 0) {
        buffer[word] &= ~(1 << (index & 31));
    } else {
        buffer[word] |= 1 << (index & 31);
    }
}

void TBitArray::Destroy()
{
    tfree(m_pBuffer);
    m_pBuffer = 0;
}

void TBitArray::ToggleBit(int index)
{
    m_pBuffer[index >> 5] ^= 1 << index;
}

void TBitArray::ClearBit(int index)
{
    m_pBuffer[index >> 5] &= ~(1 << index);
}

void TBitArray::SetBit(int index)
{
    m_pBuffer[index >> 5] |= 1 << index;
}

int TBitArray::GetBit(int index)
{
    return (m_pBuffer[index >> 5] >> index) & 1;
}

} // namespace Toshi
