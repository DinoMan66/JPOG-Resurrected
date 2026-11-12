// Z:\Toshi\Source\TKernel\THPTimer.cpp
#define TOSHI_API __declspec(dllexport)
#include "TKernelThreads.h"

namespace Toshi {

THPTimer::THPTimer()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    Reset();
}

THPTimer::~THPTimer()
{
}

void THPTimer::Update()
{
    m_liLast = m_liNow;
    QueryPerformanceCounter(&m_liNow);

    double secondsPerTick = 1.0 / (double)m_liFrequency.QuadPart;
    __int64 elapsed = m_liNow.QuadPart - m_liLast.QuadPart;
    m_fDelta = (float)((double)elapsed * secondsPerTick);
    m_fCurrent = (float)((double)m_liNow.QuadPart * secondsPerTick);
}

unsigned __int64 THPTimer::GetRaw64()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.QuadPart;
}

unsigned int THPTimer::GetRaw32()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.LowPart;
}

float THPTimer::GetDelta()
{
    return m_fDelta;
}

float THPTimer::GetCurrent()
{
    return m_fCurrent;
}

void THPTimer::Reset()
{
    QueryPerformanceCounter(&m_liNow);
    QueryPerformanceFrequency(&m_liFrequency);
    m_liLast = m_liNow;
    m_fDelta = 0.0f;
}

} // namespace Toshi
