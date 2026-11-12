// Z:\Toshi\Source\TKernel\TDLL.cpp
#define TOSHI_API __declspec(dllexport)
#include "TKernelDLL.h"

namespace Toshi {

TDLL::TDLL()
{
    m_hModule = 0;
}

TDLL::TDLL(const TDLL& other)
    : m_oFilename(other.m_oFilename)
{
    m_hModule = other.m_hModule;
}

TDLL::~TDLL()
{
    Unload();
}

TDLL& TDLL::operator=(TDLL& other)
{
    m_oFilename = other.m_oFilename;
    m_hModule = other.m_hModule;
    return *this;
}

bool TDLL::Load(const TCString& filename)
{
    Unload();
    m_oFilename = (const char*)filename;
    m_hModule = LoadLibraryA(filename.GetString(0));
    if (m_hModule != 0)
    {
        return true;
    }
    return false;
}

void TDLL::Unload()
{
    if (m_hModule != 0)
    {
        FreeLibrary(m_hModule);
        m_oFilename = "";
        m_hModule = 0;
    }
}

const TCString& TDLL::GetFilename()
{
    return m_oFilename;
}

void* TDLL::GetAddress(const TCString& name)
{
    return GetProcAddress((HMODULE)GetDLL(), (const char*)name);
}

} // namespace Toshi
