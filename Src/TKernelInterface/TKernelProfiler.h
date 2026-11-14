// TProfiler - hierarchical performance-counter profiler (kernel-internal declaration, partial).
#ifndef TKERNELPROFILER_H
#define TKERNELPROFILER_H

namespace Toshi {

struct COUNTER_STRUCT
{
    __int64 m_i64Value[3];
};

class __declspec(dllexport) TProfiler
{
public:
    TProfiler(char* name, char* parentName, int id);
    ~TProfiler();

    void Start();
    void Stop();
    bool IsRunning();
    static void __stdcall RestartPC();
    static TProfiler* __stdcall GetProfiler(int id);
    static TProfiler* __stdcall GetProfilerWithParentID(int id);
    static void __stdcall GetHardwareCounterValues(COUNTER_STRUCT& counter);

protected:
    void Reset();

private:
    friend class TProfilerStarter;

    double ElapsedInMS();
    void AddCounterStructs(COUNTER_STRUCT& first, COUNTER_STRUCT& second);
    void Add(__int64& elapsed, __int64& other);

    /* 0x00 */ char m_szName[0x50];
    /* 0x50 */ int m_iID;
    /* 0x54 */ char m_unk54;
    /* 0x58 */ __int64 m_i64Elapsed;
    /* 0x60 */ __int64 m_unk60;
    /* 0x68 */ COUNTER_STRUCT m_oStart;
    /* 0x80 */ char m_unk80[8];
    /* 0x88 */ __int64 m_i64DeltaB;
    /* 0x90 */ __int64 m_i64DeltaC;
    /* 0x98 */ char m_unk98[8];
    /* 0xA0 */ __int64 m_i64DeltaB2;
    /* 0xA8 */ __int64 m_i64DeltaC2;
    /* 0xB0 */ __int64 m_unkB0;
    /* 0xB8 */ int m_unkB8;
    /* 0xBC */ int m_unkBC;
    /* 0xC0 */ __int64 m_i64CallCount;
    /* 0xC8 */ int m_unkC8;
    /* 0xCC */ TProfiler* m_pNext;
    /* 0xD0 */ int m_unkD0;
    /* 0xD4 */ TProfiler* m_pParent;
    /* 0xD8 */ char m_unkD8;
    /* 0xD9 */ char m_unkD9[0xF];

    static bool ms_bPaused;
    static TProfiler* ms_pFirst;
    static __int64 ms_i64Frequency;
};

// Times one scope: the starters of nested scopes form a chain through m_pParent while they run.
class __declspec(dllexport) TProfilerStarter
{
public:
    TProfilerStarter(TProfiler* profiler);
    ~TProfilerStarter();

private:
    TProfilerStarter* RecursiveCallFrom();

    /* 0x00 */ TProfiler* m_pProfiler;
    /* 0x04 */ TProfilerStarter* m_pParent;
    /* 0x08 */ __int64 m_i64Start;
    /* 0x10 */ char m_unk10[0x10];
    /* 0x20 */ int m_unk20;
    /* 0x24 */ int m_unk24;
    /* 0x28 */ char m_unk28[0x18];

    static TProfilerStarter* ms_pCurrent;
};

} // namespace Toshi
#endif
