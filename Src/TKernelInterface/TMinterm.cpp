// Z:\Toshi\Source\TKernel\TMinterm.cpp - TMinterm (single product term).
// TMinterm(), the copy constructor, operator= and GetTruth() are inline in TKernelLogic.h (TSumOfMinterms has them expanded).
// Not written: the string conversion into a TCString (MakeFunctionString).
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TKernelLogic.h"

namespace Toshi {

TMinterm::TMinterm(bool truth)
{
    if (truth == true) {
        m_uMask = 0;
        m_uValue = 0;
    } else {
        m_uMask = 0xffffffff;
        m_uValue = 0;
    }
}

TMinterm::TMinterm(unsigned int mask, unsigned int value)
{
    m_uMask = mask;
    m_uValue = value;
}

bool TMinterm::operator==(const TMinterm& other)
{
    if (m_uMask == other.m_uMask && m_uValue == other.m_uValue) {
        return true;
    }
    return false;
}

TPCString TMinterm::MakeFunctionString(const char** const symbols, const TArray<TPCString>& variableNames) const
{
    TCString text;
    MakeFunctionString(text, symbols, variableNames);
    return TSystem::GetCStringPool()->Get(text);
}

} // namespace Toshi
