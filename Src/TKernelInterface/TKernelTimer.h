// TTimer - kernel-internal declaration: a TTask that counts time and fires an event.
#ifndef TKERNELTIMER_H
#define TKERNELTIMER_H
#include "TKernelTask.h"
#include "TKernelEmitter.h"

namespace Toshi {

class __declspec(dllexport) TTimer : public TTask
{
public:
    class __declspec(dllexport) TriggerEvent
    {
    public:
        TriggerEvent(int a, int b, float c, float d)
        {
            m_unk00 = a;
            m_unk04 = b;
            m_unk08 = c;
            m_unk0C = d;
        }
        TriggerEvent& operator=(const TriggerEvent& other);

    private:
        int m_unk00;                        // +0x00
        int m_unk04;                        // +0x04
        float m_unk08;                      // +0x08
        float m_unk0C;                      // +0x0C
    };

    TTimer();
    virtual ~TTimer();
    virtual TClass& GetClass() const;

    void SetModeStopped();
    void SetModeContinuous();
    void SetModeWaitFor(float seconds);
    void SetModeLoop(int count);
    void SetModeOnce();

    static TClass m_sClass;

protected:
    virtual bool OnUpdate(float deltaTime);
    virtual void OnDestroy();

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    TEmitter<TTimer, TriggerEvent> m_oEmitter;  // +0x24 (receives the trigger events)
    int m_iMode;                            // +0x30 (0 stopped, 1 once, 2 loop, 3 wait for, 4 continuous)
    int m_iLoopCount;                       // +0x34
    int m_unk38;                            // +0x38
    float m_fWaitTime;                      // +0x3C
    float m_unk40;                          // +0x40
};

} // namespace Toshi
#endif
