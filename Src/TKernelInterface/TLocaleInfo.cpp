// Z:\Toshi\Source\TKernel\TLocale.cpp - TLocaleInfo.
#define TOSHI_API __declspec(dllexport)
#include "TKernelLocale.h"

namespace Toshi {

TLocaleInfo::TLocaleInfo(int index, const TPCString& name, const TPCString& fileName)
    : m_iIndex(index), m_oName(name), m_oFileName(fileName)
{
    m_eWordBreakStyle = WORDBREAK_DEFAULT;
    if (name.GetCString().Compare("Japanese", -1) == 0) {
        m_eWordBreakStyle = WORDBREAK_JAPANESE;
    }
}

TLocaleInfo::TLocaleInfo(const TLocaleInfo& other)
    : m_iIndex(other.m_iIndex), m_oName(other.m_oName), m_oFileName(other.m_oFileName),
      m_eWordBreakStyle(other.m_eWordBreakStyle)
{
}

TLocaleInfo::~TLocaleInfo()
{
}

TLocaleInfo& TLocaleInfo::operator=(const TLocaleInfo& other)
{
    m_iIndex = other.m_iIndex;
    m_oName = other.m_oName;
    m_oFileName = other.m_oFileName;
    m_eWordBreakStyle = other.m_eWordBreakStyle;
    return *this;
}

TPCString TLocaleInfo::GetName() const
{
    return m_oName;
}

TPCString TLocaleInfo::GetFileName() const
{
    return m_oFileName;
}

int TLocaleInfo::GetIndex() const
{
    return m_iIndex;
}

TLocaleInfo::WordBreakStyle TLocaleInfo::GetWordBreakStyle() const
{
    return m_eWordBreakStyle;
}

TLocaleInfo* TLocale::GetCurrentLocaleInfo()
{
    return m_pCurrentLocaleInfo;
}

} // namespace Toshi
