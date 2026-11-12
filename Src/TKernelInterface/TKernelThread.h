// TThread and TThreadManager - kernel-internal declarations (Win32 threads and the list that tracks them).
// Reconstructed from TKernelInterface.dll. Layout: TThread = vtable, list node (+4), thread handle (+0xC),
// thread id (+0x10); TThreadManager = critical section (+0), list root (+0x18).
#ifndef TKERNELTHREAD_H
#define TKERNELTHREAD_H
#include <windows.h>
#ifdef Yield
#undef Yield    // winbase.h defines Yield() as nothing; TThread::Yield is a real function
#endif
#include "TGenericLists.h"

namespace Toshi {

class TThreadManager;

class __declspec(dllexport) TThread : public TGenericDList::TNode
{
public:
    // The binary only shows that these values are passed straight to CreateThread/SetThreadPriority;
    // the enumerator names are invented.
    enum STACKSIZE { STACKSIZE_DEFAULT = 0 };
    enum PRIORITY { PRIORITY_IDLE = -15, PRIORITY_NORMAL = 0, PRIORITY_TIME_CRITICAL = 15 };

    TThread();
    virtual void Main() = 0;
    bool Create(STACKSIZE stackSize, PRIORITY priority, unsigned int flags);   // flags bit 0: leave suspended
    bool Destroy();
    bool GetPriority(PRIORITY& priority);
    bool SetPriority(PRIORITY priority);
    bool Resume();
    bool Suspend();

    static bool __stdcall GetCurrentPriority(PRIORITY& priority);
    static bool __stdcall SetCurrentPriority(PRIORITY priority);
    static bool __stdcall Yield();
    static void __stdcall Exit();

private:
    friend class TThreadManager;

    static bool __stdcall GetPriority(void* thread, PRIORITY& priority);
    static bool __stdcall SetPriority(void* thread, PRIORITY priority);
    static unsigned int __stdcall Entry(void* thread);
    static void __stdcall Exit(TThread* thread);

    HANDLE m_hThread;                   // +0x0C
    unsigned int m_uThreadID;           // +0x10
};

class __declspec(dllexport) TThreadManager
{
public:
    TThreadManager() { Create(); }
    ~TThreadManager();
    static TThreadManager* __stdcall GetThreadManager();
    void Create();
    void Destroy();
    void InsertThread(TThread* thread);
    TThread* FindThread(unsigned int threadID);
    void RemoveThread(TThread* thread);

private:
    friend class TThread;

    CRITICAL_SECTION m_oSection;        // +0x00
    TGenericDList m_oThreads;           // +0x18
    static TThreadManager* s_pThreadManager;
};

} // namespace Toshi
#endif
