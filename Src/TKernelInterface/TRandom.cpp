// Z:\Toshi\Source\TKernel\TRandom.cpp - ISAAC random number generator.
#include "TKernelMisc.h"

namespace Toshi {

// ISAAC (Bob Jenkins) with a 16-word state; the step and mix are his reference implementation.
static inline unsigned int IsaacIndex(unsigned int* mm, unsigned int x)
{
    return *(unsigned int*)((unsigned char*)mm + (x & (15 << 2)));
}

static inline void IsaacStep(unsigned int mix, unsigned int& a, unsigned int& b, unsigned int* mm,
                             unsigned int*& m, unsigned int*& m2, unsigned int*& r)
{
    unsigned int x = *m;
    unsigned int y;

    a = (a ^ mix) + *(m2++);
    *(m++) = y = IsaacIndex(mm, x) + a + b;
    *(r++) = b = IsaacIndex(mm, y >> 4) + x;
}

void TRandom::Isaac()
{
    unsigned int* mm = m_aMemory;
    unsigned int* r = m_aResult;
    unsigned int a = m_uAccumulator;
    unsigned int b = m_uLastResult + (++m_uCounter);
    unsigned int* m;
    unsigned int* m2;
    unsigned int* mend;

    mend = m2 = mm + 8;
    for (m = mm; m < mend;) {
        IsaacStep(a << 13, a, b, mm, m, m2, r);
        IsaacStep(a >> 6, a, b, mm, m, m2, r);
        IsaacStep(a << 2, a, b, mm, m, m2, r);
        IsaacStep(a >> 16, a, b, mm, m, m2, r);
    }
    for (m2 = mm; m2 < mend;) {
        IsaacStep(a << 13, a, b, mm, m, m2, r);
        IsaacStep(a >> 6, a, b, mm, m, m2, r);
        IsaacStep(a << 2, a, b, mm, m, m2, r);
        IsaacStep(a >> 16, a, b, mm, m, m2, r);
    }
    m_uAccumulator = a;
    m_uLastResult = b;
}

void TRandom::RandInit()
{
    unsigned int a, b, c, d, e, f, g, h;
    int i;

    m_uAccumulator = m_uLastResult = m_uCounter = 0;
    a = b = c = d = e = f = g = h = 0x9e3779b9 + m_uSeed;
    for (i = 0; i < 4; i++) {
        a ^= b << 11;
        d += a;
        b += c;
        b ^= c >> 2;
        e += b;
        c += d;
        c ^= d << 8;
        f += c;
        d += e;
        d ^= e >> 16;
        g += d;
        e += f;
        e ^= f << 10;
        h += e;
        f += g;
        f ^= g >> 4;
        a += f;
        g += h;
        g ^= h << 8;
        b += g;
        h += a;
        h ^= a >> 9;
        c += h;
        a += b;
    }
    for (i = 0; i < 16; i += 8) {
        a ^= b << 11;
        d += a;
        b += c;
        b ^= c >> 2;
        e += b;
        c += d;
        c ^= d << 8;
        f += c;
        d += e;
        d ^= e >> 16;
        g += d;
        e += f;
        e ^= f << 10;
        h += e;
        f += g;
        f ^= g >> 4;
        a += f;
        g += h;
        g ^= h << 8;
        b += g;
        h += a;
        h ^= a >> 9;
        c += h;
        a += b;
        m_aMemory[i] = a;
        m_aMemory[i + 1] = b;
        m_aMemory[i + 2] = c;
        m_aMemory[i + 3] = d;
        m_aMemory[i + 4] = e;
        m_aMemory[i + 5] = f;
        m_aMemory[i + 6] = g;
        m_aMemory[i + 7] = h;
    }
    Isaac();
    m_iCount = 16;
}

unsigned int TRandom::RandRaw()
{
    int index = m_iCount;
    m_iCount = index - 1;
    if (index == 0) {
        Isaac();
        m_iCount = 15;
        return m_aResult[15];
    }
    return m_aResult[index - 1];
}

int TRandom::GetInt()
{
    return RandRaw();
}

unsigned int TRandom::GetSeed()
{
    return m_uSeed;
}

void TRandom::SetSeed(unsigned int seed)
{
    m_uSeed = seed;
    RandInit();
}


int TRandom::GetInt(int range)
{
    unsigned int raw = RandRaw();
    unsigned __int64 product = (unsigned __int64)(unsigned int)range * raw;
    unsigned int high = (unsigned int)(product >> 32);
    return high;
}

int TRandom::GetInt(int minimum, int maximum)
{
    unsigned int span = maximum - minimum;
    unsigned int raw = RandRaw();
    unsigned __int64 product = (unsigned __int64)span * raw;
    unsigned int high = (unsigned int)(product >> 32);
    return minimum + high;
}

float TRandom::GetFloat()
{
    return (float)(RandRaw() >> 1) * (1.0f / 2147483648.0f);
}

float TRandom::GetFloat2()
{
    return (float)(RandRaw() >> 1) * (1.0f / 1073741824.0f) + -1.0f;
}

float TRandom::GetFloatMinMax(float minimum, float maximum)
{
    return (float)(RandRaw() >> 1) * (1.0f / 2147483648.0f) * (maximum - minimum) + minimum;
}

float TRandom::GetFloatMinRange(float minimum, float range)
{
    return (float)(RandRaw() >> 1) * (1.0f / 2147483648.0f) * range + minimum;
}

TRandom::~TRandom()
{
}

} // namespace Toshi
