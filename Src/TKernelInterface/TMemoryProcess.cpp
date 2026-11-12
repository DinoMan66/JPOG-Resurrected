// Z:\Toshi\Source\TKernel\TMemory.cpp - process node marking.
// Own translation unit: the original calls TMemory::GetMemManager out of line from here.
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TKernelMemory.h"

namespace Toshi {

// Marks 'node' as a process (allocated) node of 'size' bytes owned by 'block': the block's slot index goes into
// the top bits of the flag word.
void __stdcall TMemory::SetProcess(MemBlock* block, MemNode* node, unsigned int size)
{
    unsigned int slotBits = (block->m_pSlot - GetMemManager().m_aSlots) << 27;
    node->m_uFlags = slotBits | size | 1 | GetMemManager().m_uGlobalFlags;
}

} // namespace Toshi
