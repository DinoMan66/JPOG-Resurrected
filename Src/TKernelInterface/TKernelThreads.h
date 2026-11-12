// TMutex, TMutexLock, TSemaphore, THPTimer - kernel-internal declarations (Win32 synchronisation wrappers).
#ifndef TKERNELTHREADS_H
#define TKERNELTHREADS_H
#include <windows.h>

namespace Toshi {

class __declspec(dllexport) TMutex
{
public:
    bool Create();
    bool Destroy();
    bool Lock(unsigned int flags);      // bit 0 set: poll instead of waiting forever
    bool Unlock();

private:
    HANDLE m_hMutex;                    // +0x00
};

// Scoped lock: locks in the constructor, unlocks in the destructor.
class __declspec(dllexport) TMutexLock
{
public:
    TMutexLock() : m_pMutex(0) {}
    TMutexLock(TMutex* mutex) { Create(mutex); }
    ~TMutexLock() { Destroy(); }

    void Create(TMutex* mutex);
    void Destroy();

private:
    TMutex* m_pMutex;                   // +0x00
};

class __declspec(dllexport) TSemaphore
{
public:
    bool Create(int initialCount, int maxCount);
    bool Destroy();
    bool Poll();
    bool Wait();
    bool Signal();

private:
    HANDLE m_hSemaphore;                // +0x00
};

// High-resolution timer on QueryPerformanceCounter.
class __declspec(dllexport) THPTimer
{
public:
    THPTimer();
    ~THPTimer();

    void Update();
    void Reset();
    float GetDelta();
    float GetCurrent();
    unsigned int GetRaw32();
    unsigned __int64 GetRaw64();

private:
    LARGE_INTEGER m_liFrequency;        // +0x00
    float m_fCurrent;                   // +0x08  seconds since the counter's origin
    int m_iPad0C;                       // +0x0C
    LARGE_INTEGER m_liLast;             // +0x10  counter at the previous Update
    LARGE_INTEGER m_liNow;              // +0x18  counter at the last Update
    float m_fDelta;                     // +0x20  seconds between the last two Updates
};

} // namespace Toshi
#endif
