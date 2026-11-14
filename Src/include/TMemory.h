// Toshi memory + import helpers (reconstructed).
// TKernelInterface.dll exports these; every other Toshi DLL imports them.
//   ?tmalloc@@YGPAXHPADH@Z   void* __stdcall tmalloc(int size, char* file, int line)
//   ?tcalloc@@YGPAXHH@Z      void* __stdcall tcalloc(int count, int size)
//   ?tfree@@YGXPAX@Z         void  __stdcall tfree(void* p)
// The "YG" in the decorated names means __stdcall, which is the default here because
// every Toshi DLL is compiled with -Gz.
#ifndef TMEMORY_H
#define TMEMORY_H

#ifndef TOSHI_API
#define TOSHI_API __declspec(dllimport)     // calls go through the import table: call [__imp_...]
#endif

TOSHI_API void* tmalloc(int size, char* file, int line);
TOSHI_API void* tcalloc(int count, int size);
TOSHI_API void  tfree(void* p);

namespace Toshi {

class TMemory
{
public:
    // Video memory counters of the Direct3D device (0x54 bytes). Only the field at +0x28 is read so far.
    struct HALMemInfo
    {
        int m_unk00[10];
        int m_iUnk28;
        int m_unk2C[10];
    };

    TOSHI_API static void __stdcall GetHALMemInfo(HALMemInfo& info);
};

}

#endif
