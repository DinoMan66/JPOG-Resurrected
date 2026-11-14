// Z:\Toshi\Source\TKernel\TMemory.cpp - the global allocation entry points.
// Own translation unit: the original calls TMemory::GetMemManager / GetGlobalBlock out of line from here.
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TKernelMemory.h"
#include "TMemory.h"
#include "TKernelPile.h"

using namespace Toshi;

void* tmalloc(int size, char* file, int line)
{
    TMemory& memory = TMemory::GetMemManager();
    return memory.Alloc(size, 16, TMemory::GetMemManager().GetGlobalBlock(), file, line);
}

void* tcalloc(int count, int size)
{
    TMemory& memory = TMemory::GetMemManager();
    return memory.Calloc(count * size, 16, TMemory::GetMemManager().GetGlobalBlock(), 0, -1);
}

void tfree(void* p)
{
    TMemory::GetMemManager().Free(p);
}

void* tmemalign(int alignment, int size)
{
    TMemory& memory = TMemory::GetMemManager();
    return memory.Alloc(size, alignment, TMemory::GetMemManager().GetGlobalBlock(), 0, -1);
}

void* trealloc(void* p, int size)
{
    TMemory& memory = TMemory::GetMemManager();
    return memory.Realloc(p, size, TMemory::GetMemManager().GetGlobalBlock());
}
