// Z:\Toshi\Source\TKernel\TMinterm.cpp - TSumOfMinterms (sum of products over a bit mask of inputs).
// Not written: the TCString overload of MakeFunctionString and ParseFunctionString.
#define TOSHI_API __declspec(dllexport)
#define SETCAP 6    // TArray::SetCapacity with new[]/delete[] (see include\TArray.h)
#include "TNewDelete.h"
#include "TKernelMisc.h"
#include "TKernelLogic.h"

namespace Toshi {

TSumOfMinterms::TSumOfMinterms()
    : m_aTerms(4, 1)
{
}

TSumOfMinterms::TSumOfMinterms(int capacity)
    : m_aTerms(4, capacity)
{
}

TSumOfMinterms::TSumOfMinterms(const TMinterm& term)
    : m_aTerms(4, 1)
{
    m_aTerms.AddEmpty() = term;
}

TSumOfMinterms::TSumOfMinterms(const TSumOfMinterms& other)
    : m_aTerms(other.m_aTerms)
{
}

TSumOfMinterms::~TSumOfMinterms()
{
}

TSumOfMinterms& TSumOfMinterms::operator=(const TSumOfMinterms& other)
{
    m_aTerms = other.m_aTerms;
    return *this;
}

TSumOfMinterms& TSumOfMinterms::operator+(const TMinterm& term)
{
    m_aTerms.AddEmpty() = term;
    return *this;
}

bool TSumOfMinterms::GetTruth(unsigned int input)
{
    if (m_aTerms.Count() == 0) {
        return true;
    }
    for (int i = 0; i < m_aTerms.Count(); i++) {
        if (m_aTerms[i].GetTruth(input) == true) {
            return true;
        }
    }
    return false;
}

TPCString TSumOfMinterms::MakeFunctionString(const char** const symbols, const TArray<TPCString>& variableNames) const
{
    TCString text;
    MakeFunctionString(text, symbols, variableNames);
    return TSystem::GetCStringPool()->Get(text);
}

} // namespace Toshi
