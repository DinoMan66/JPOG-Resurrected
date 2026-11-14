// Z:\Toshi\Source\TKernel\TScheduler.cpp - task destruction entry points and class registration of TScheduler.
#define TOSHI_API __declspec(dllexport)
#include "TKernelSystem.h"
#include "TKernelTask.h"
#include "TKernelThreads.h"

namespace Toshi {

TClass TScheduler::m_sClass("TScheduler", &TObject::m_sClass, TScheduler::CreateObject, TScheduler::CreateObjectInPlace,
                            TScheduler::InitialiseStatic, TScheduler::DeinitialiseStatic, 0x10000);

TScheduler::TScheduler(TKernelInterface* kernelInterface)
    : m_refCount(0),
      m_pKernelInterface(kernelInterface),
      m_unk0C(0),
      m_unk10(&m_refCount),
      m_unk14(&m_refCount),
      m_unk18(0),
      m_pRootTask(0),
      m_unk20(0),
      m_fTimeDelta(0.0f),
      m_fTotalTime(0.0f),
      m_fDebugSlowTime(1.0f),
      m_iFrameCount(0)
{
}

void TScheduler::Update()
{
    float delta = m_pKernelInterface->GetSystemTimer()->GetDelta();
    m_fTotalTime += delta;
    m_iFrameCount++;
    // the step is clamped to [0, m_fDebugSlowTime] so a stalled frame does not make the game jump
    if (delta < 0.0f) {
        m_fTimeDelta = 0.0f;
    } else if (delta > m_fDebugSlowTime) {
        m_fTimeDelta = m_fDebugSlowTime;
    } else {
        m_fTimeDelta = delta;
    }
    DestroyDyingTasks(m_pRootTask);
    UpdateActiveTasks(m_pRootTask);
}

void TScheduler::DestroyTask(TTask& task)
{
    if (!(task.m_uFlags & 4)) {
        task.m_uFlags |= 4;
        DestroyTaskRecurse(task.m_unk18);
    }
}

void TScheduler::DestroyAllTasks()
{
    if (m_pRootTask) {
        DestroyTask(*m_pRootTask);
        DestroyDyingTasks(m_pRootTask);
    }
}

void TScheduler::DeleteTask(TTask* task)
{
    DeleteTaskRecurse(task->m_unk18);
    DeleteTaskAtomic(task);
}

void TScheduler::Debug_PrintTaskTree() const
{
}

void TScheduler::SetDebugSlowTime(bool slow)
{
    m_fDebugSlowTime = slow ? 0.01f : 1.0f;
}

void TScheduler::UpdateKernelPaused()
{
    UpdateActiveTasksKernelPaused(m_pRootTask);
}

void __stdcall TScheduler::DeinitialiseStatic()
{
}

void __stdcall TScheduler::InitialiseStatic()
{
}

TObject* __stdcall TScheduler::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TScheduler::CreateObject()
{
    return 0;
}

} // namespace Toshi
