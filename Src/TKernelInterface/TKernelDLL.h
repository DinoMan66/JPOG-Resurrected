// TDLL - kernel-internal declaration: a dynamically loaded library (filename + module handle).
#ifndef TKERNELDLL_H
#define TKERNELDLL_H
#include <windows.h>
// windows.h renames CreateFile to CreateFileA; the Toshi file system methods are recorded (exported) as CreateFile.
#undef CreateFile
#include "TCString.h"

namespace Toshi {

class __declspec(dllexport) TDLL
{
public:
    TDLL();
    TDLL(const TDLL& other);
    virtual ~TDLL();
    TDLL& operator=(TDLL& other);

    bool Load(const TCString& filename);
    void Unload();
    const void* GetDLL();
    const TCString& GetFilename();
    void* GetAddress(const TCString& name);

private:
    TCString m_oFilename;               // +0x04
    HMODULE m_hModule;                  // +0x0C
};

} // namespace Toshi
#endif
