// Z:\Toshi\Source\TKernel\TThread.cpp - Win32 thread wrapper and the manager that tracks live threads.
// Not written: the constructors/destructor of TThread and TThreadManager and the global manager instance
// (their node/list initialisation is inlined from header code that is out-of-line here).
#define TOSHI_API __declspec(dllexport)
#include <process.h>
#include "TKernelThread.h"

namespace Toshi {

TThreadManager* TThreadManager::s_pThreadManager;

// ---- TThreadManager
TThreadManager* __stdcall TThreadManager::GetThreadManager()
{
    return s_pThreadManager;
}

TThreadManager::~TThreadManager()
{
    Destroy();
}

void TThreadManager::Create()
{
    s_pThreadManager = this;
    InitializeCriticalSection(&m_oSection);
}

void TThreadManager::Destroy()
{
    s_pThreadManager = 0;
    DeleteCriticalSection(&m_oSection);
}

void TThreadManager::InsertThread(TThread* thread)
{
    EnterCriticalSection(&m_oSection);
    TGenericDList::TNode* node = thread;
    node->m_pPrev = &m_oThreads.m_oRoot;
    node->m_pNext = m_oThreads.m_oRoot.m_pNext;
    m_oThreads.m_oRoot.m_pNext = node;
    node->m_pNext->m_pPrev = node;
    LeaveCriticalSection(&m_oSection);
}

TThread* TThreadManager::FindThread(unsigned int threadID)
{
    TThread* found = 0;
    EnterCriticalSection(&m_oSection);
    const TGenericDList::TNode* end = &m_oThreads.m_oRoot;
    for (TThread* thread = (TThread*)m_oThreads.m_oRoot.m_pNext; (TGenericDList::TNode*)thread != end;
         thread = (TThread*)((TGenericDList::TNode*)thread)->m_pNext) {
        if (thread->m_uThreadID == threadID) {
            found = thread;
            break;
        }
    }
    LeaveCriticalSection(&m_oSection);
    return found;
}

void TThreadManager::RemoveThread(TThread* thread)
{
    EnterCriticalSection(&m_oSection);
    TGenericDList::TNode& node = *thread;
    node.m_pPrev->m_pNext = node.m_pNext;
    node.m_pNext->m_pPrev = node.m_pPrev;
    node.m_pNext = &node;
    node.m_pPrev = &node;
    LeaveCriticalSection(&m_oSection);
}

// ---- TThread
bool TThread::Create(STACKSIZE stackSize, PRIORITY priority, unsigned int flags)
{
    m_hThread = 0;
    m_uThreadID = (unsigned int)-1;
    m_hThread = (HANDLE)_beginthreadex(0, stackSize, Entry, this, CREATE_SUSPENDED, &m_uThreadID);
    SetThreadPriority(m_hThread, priority);
    TThreadManager::s_pThreadManager->InsertThread(this);
    if ((flags & 1) == 0) {
        ResumeThread(m_hThread);
    }
    return true;
}

bool TThread::Destroy()
{
    if (m_hThread == 0) {
        return false;
    }
    TerminateThread(m_hThread, 0);
    CloseHandle(m_hThread);
    TThreadManager::s_pThreadManager->RemoveThread(this);
    m_hThread = 0;
    m_uThreadID = (unsigned int)-1;
    return true;
}

void __stdcall TThread::Exit(TThread* thread)
{
    CloseHandle(thread->m_hThread);
    TThreadManager::s_pThreadManager->RemoveThread(thread);
    thread->m_hThread = 0;
    thread->m_uThreadID = (unsigned int)-1;
    _endthreadex(0);
}

bool __stdcall TThread::GetPriority(void* thread, PRIORITY& priority)
{
    priority = (PRIORITY)GetThreadPriority(thread);
    return true;
}

bool __stdcall TThread::SetPriority(void* thread, PRIORITY priority)
{
    SetThreadPriority(thread, priority);
    return true;
}

unsigned int __stdcall TThread::Entry(void* thread)
{
    ((TThread*)thread)->Main();
    Exit((TThread*)thread);
    return 0;
}

bool __stdcall TThread::GetCurrentPriority(PRIORITY& priority)
{
    return GetPriority(GetCurrentThread(), priority);
}

bool __stdcall TThread::SetCurrentPriority(PRIORITY priority)
{
    return SetPriority(GetCurrentThread(), priority);
}

bool __stdcall TThread::Yield()
{
    Sleep(0);
    return true;
}

void __stdcall TThread::Exit()
{
    TThreadManager* manager = TThreadManager::s_pThreadManager;
    Exit(manager->FindThread(GetCurrentThreadId()));
}

bool TThread::GetPriority(PRIORITY& priority)
{
    return GetPriority(m_hThread, priority);
}

bool TThread::SetPriority(PRIORITY priority)
{
    return SetPriority(m_hThread, priority);
}

bool TThread::Resume()
{
    return ResumeThread(m_hThread) != (DWORD)-1;
}

bool TThread::Suspend()
{
    return SuspendThread(m_hThread) != (DWORD)-1;
}

} // namespace Toshi
