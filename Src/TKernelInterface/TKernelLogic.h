// Toshi::TMinterm - kernel-internal declaration. One product term of a boolean function over a bit mask of inputs:
// it is true for an input when the masked input equals the stored value.
#ifndef TKERNELLOGIC_H
#define TKERNELLOGIC_H
#include "TArray.h"

namespace Toshi {

class __declspec(dllexport) TMinterm
{
public:
    TMinterm() { m_uMask = 0; m_uValue = 0; }
    TMinterm(bool truth);
    TMinterm(unsigned int mask, unsigned int value);
    TMinterm(const TMinterm& other)
    {
        m_uMask = other.m_uMask;
        m_uValue = other.m_uValue;
    }
    TMinterm& operator=(const TMinterm& other)
    {
        m_uMask = other.m_uMask;
        m_uValue = other.m_uValue;
        return *this;
    }
    bool operator==(const TMinterm& other);
    bool GetTruth(unsigned int input) { return (m_uMask & input) == m_uValue; }

private:
    unsigned int m_uMask;   // +0 inputs that matter
    unsigned int m_uValue;  // +4 required value of the masked inputs
};

// A boolean function as a sum (OR) of minterms. An empty sum is true.
// Not declared yet: MakeFunctionString (two overloads) and ParseFunctionString.
class __declspec(dllexport) TSumOfMinterms
{
public:
    TSumOfMinterms();
    TSumOfMinterms(int capacity);
    TSumOfMinterms(const TMinterm& term);
    TSumOfMinterms(const TSumOfMinterms& other);
    ~TSumOfMinterms();
    TSumOfMinterms& operator=(const TSumOfMinterms& other);
    TSumOfMinterms& operator+(const TMinterm& term);    // appends the term to this sum and returns it
    bool GetTruth(unsigned int input);

private:
    TArray<TMinterm> m_aTerms;  // +0x00 (grow, count, capacity, data)
};

} // namespace Toshi
#endif
