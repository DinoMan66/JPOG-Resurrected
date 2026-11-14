// Z:\Toshi\Source\TKernel\TProfiler.cpp - the small TProfiler members.
#define TOSHI_API __declspec(dllexport)
#include <windows.h>
#include "TKernelProfiler.h"

namespace Toshi {

bool TProfiler::ms_bPaused = true;
TProfiler* TProfiler::ms_pFirst;
__int64 TProfiler::ms_i64Frequency;

TProfilerStarter* TProfilerStarter::ms_pCurrent;

TProfiler::~TProfiler()
{
}

void __stdcall TProfiler::RestartPC()
{
}

bool TProfiler::IsRunning()
{
    return !ms_bPaused;
}

void TProfiler::Start()
{
    ms_bPaused = false;
    QueryPerformanceCounter((LARGE_INTEGER*)&m_oStart);
}

void __stdcall TProfiler::GetHardwareCounterValues(COUNTER_STRUCT& counter)
{
    QueryPerformanceCounter((LARGE_INTEGER*)&counter);
}

void TProfiler::Reset()
{
    m_i64Elapsed = 0;
    m_unk60 = 0;
    m_oStart.m_i64Value[0] = 0;
    m_oStart.m_i64Value[1] = 0;
    m_oStart.m_i64Value[2] = 0;
    m_unkB0 = 0;
    m_unkB8 = -1;
    m_unkBC = 0x7fffffff;
    m_i64CallCount = 0;
    m_unkD8 = 0;
}

void TProfiler::Stop()
{
    COUNTER_STRUCT now;

    ms_bPaused = true;
    m_i64CallCount++;
    QueryPerformanceCounter((LARGE_INTEGER*)&now);
    m_i64Elapsed = m_i64Elapsed + now.m_i64Value[0] - m_oStart.m_i64Value[0];
    m_i64DeltaB = now.m_i64Value[1] - m_oStart.m_i64Value[1];
    m_i64DeltaC = now.m_i64Value[2] - m_oStart.m_i64Value[2];
}

double TProfiler::ElapsedInMS()
{
    return (double)m_i64Elapsed / ((double)ms_i64Frequency * 0.001);
}

void TProfiler::AddCounterStructs(COUNTER_STRUCT& first, COUNTER_STRUCT& second)
{
    m_i64DeltaB += first.m_i64Value[1];
    m_i64DeltaC += first.m_i64Value[2];
    m_i64DeltaB2 += second.m_i64Value[1];
    m_i64DeltaC2 += second.m_i64Value[2];
}

void TProfiler::Add(__int64& elapsed, __int64& other)
{
    m_i64Elapsed += elapsed;
    m_unk60 += other;
    m_i64CallCount++;
}

TProfiler* __stdcall TProfiler::GetProfilerWithParentID(int id)
{
    TProfiler* profiler = ms_pFirst;
    while (profiler != 0) {
        if (profiler->m_pParent != 0 && profiler->m_pParent->m_iID == id) {
            return profiler;
        }
        profiler = profiler->m_pNext;
    }
    return 0;
}

TProfiler* __stdcall TProfiler::GetProfiler(int id)
{
    TProfiler* profiler = ms_pFirst;
    while (profiler != 0) {
        if (profiler->m_iID == id) {
            return profiler;
        }
        profiler = profiler->m_pNext;
    }
    return 0;
}

TProfilerStarter::TProfilerStarter(TProfiler* profiler)
{
    m_pProfiler = profiler;
    if (!TProfiler::ms_bPaused) {
        QueryPerformanceCounter((LARGE_INTEGER*)&m_i64Start);
        m_pParent = ms_pCurrent;
        ms_pCurrent = this;
        m_unk20 = 0;
        m_unk24 = 0;
        m_pProfiler->m_unkD0++;
    }
}

// The innermost running starter of the same profiler, if the scope is being entered recursively.
TProfilerStarter* TProfilerStarter::RecursiveCallFrom()
{
    for (TProfilerStarter* starter = m_pParent; starter; starter = starter->m_pParent) {
        if (m_pProfiler == starter->m_pProfiler) {
            return starter;
        }
    }
    return 0;
}

} // namespace Toshi
