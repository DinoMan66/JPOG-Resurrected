// Z:\Toshi\Source\TKernel\TTimer.cpp - mode setters, the trigger event record and the class registration of TTimer.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TKernelTimer.h"
#include "TNewDelete.h"

namespace Toshi {

TClass TTimer::m_sClass("TTimer", &TTask::m_sClass, TTimer::CreateObject, TTimer::CreateObjectInPlace,
                        TTimer::InitialiseStatic, TTimer::DeinitialiseStatic, 0x10000);

TTimer::TTimer() : m_oEmitter(this)
{
    m_iMode = 0;
    m_iLoopCount = 0;
    m_unk38 = 0;
    m_fWaitTime = 0.0f;
    m_unk40 = 0.0f;
    SetModeStopped();
}

void TTimer::OnDestroy()
{
}

void TTimer::SetModeStopped()
{
    m_iMode = 0;
    m_unk40 = 0.0f;
}

void TTimer::SetModeContinuous()
{
    m_iMode = 4;
    m_unk40 = 0.0f;
}

void TTimer::SetModeWaitFor(float seconds)
{
    m_iMode = 3;
    m_unk40 = 0.0f;
    m_fWaitTime = seconds;
}

void TTimer::SetModeLoop(int count)
{
    m_iMode = 2;
    m_unk40 = 0.0f;
    m_unk38 = 0;
    m_iLoopCount = count;
}

void TTimer::SetModeOnce()
{
    m_iMode = 1;
    m_unk40 = 0.0f;
}

TTimer::~TTimer()
{
}

void __stdcall TTimer::DeinitialiseStatic()
{
}

void __stdcall TTimer::InitialiseStatic()
{
}

TTimer::TriggerEvent& TTimer::TriggerEvent::operator=(const TriggerEvent& other)
{
    m_unk00 = other.m_unk00;
    m_unk04 = other.m_unk04;
    m_unk08 = other.m_unk08;
    m_unk0C = other.m_unk0C;
    return *this;
}

bool TTimer::OnUpdate(float deltaTime)
{
    float elapsed = m_unk40 + deltaTime;
    m_unk40 = elapsed;
    if (m_iMode == 1) {
        TriggerEvent event(1, 0, 0.0f, elapsed);
        m_oEmitter.Throw(event);
    } else if (m_iMode == 2) {
        m_unk38++;
        if (m_unk38 > m_iLoopCount) {
            TriggerEvent event(2, m_iLoopCount, 0.0f, elapsed);
            m_oEmitter.Throw(event);
        }
    } else if (m_iMode == 3) {
        if (elapsed >= m_fWaitTime) {
            TriggerEvent event(3, 0, m_fWaitTime, elapsed);
            m_oEmitter.Throw(event);
        }
    } else if (m_iMode == 4) {
        TriggerEvent event(4, 0, 0.0f, elapsed);
        m_oEmitter.Throw(event);
    }
    return true;
}

TObject* __stdcall TTimer::CreateObjectInPlace(void* memory)
{
    return new (memory) TTimer;
}

TObject* __stdcall TTimer::CreateObject()
{
    return new TTimer;
}

TClass& TTimer::GetClass() const
{
    return m_sClass;
}

} // namespace Toshi
