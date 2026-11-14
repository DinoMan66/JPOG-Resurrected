// Z:\Toshi\Source\TKernel\TTask.cpp - the trivial virtual hooks, flag accessors and class registration of TTask.
#define TOSHI_API __declspec(dllexport)
#include "TKernelTask.h"
#include "TKernelSystem.h"

namespace Toshi {

TClass TTask::m_sClass("TTask", &TObject::m_sClass, TTask::CreateObject, TTask::CreateObjectInPlace,
                       TTask::InitialiseStatic, TTask::DeinitialiseStatic, 0x10000);

void TTask::OnDeactivate()
{
}

void TTask::OnActivate()
{
}

void TTask::OnChildDied(const TClass& childClass, const TTask* child)
{
}

bool TTask::OnChildDying(const TTask* child)
{
    return true;
}

void TTask::OnDestroy()
{
}

bool TTask::OnUpdateKernelPaused()
{
    return true;
}

bool TTask::OnUpdate(float deltaTime)
{
    return true;
}

bool TTask::OnCreate()
{
    return true;
}

TTask::~TTask()
{
}

void TTask::DestroyTask()
{
    m_pScheduler->DestroyTask(*this);
}

unsigned int TTask::GetFlags() const
{
    return m_uFlags;
}

bool TTask::IsDying() const
{
    if (m_uFlags & 4) {
        return true;
    }
    return false;
}

bool TTask::IsActive() const
{
    if (m_uFlags & 2) {
        return true;
    }
    return false;
}

bool TTask::IsCreated() const
{
    if (m_uFlags & 1) {
        return true;
    }
    return false;
}

void TTask::Activate(bool activate)
{
    unsigned int oldFlags = m_uFlags;
    unsigned int newFlags = oldFlags & ~2;
    newFlags |= (activate == true ? 2 : 0);
    m_uFlags = newFlags;
    if (oldFlags != newFlags) {
        if (activate == true) {
            OnActivate();
        } else {
            OnDeactivate();
        }
    }
}

TScheduler* TTask::GetScheduler()
{
    return m_pScheduler;
}

void __stdcall TTask::DeinitialiseStatic()
{
}

void __stdcall TTask::InitialiseStatic()
{
}

TObject* __stdcall TTask::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TTask::CreateObject()
{
    return 0;
}

TClass& TTask::GetClass() const
{
    return m_sClass;
}

} // namespace Toshi
