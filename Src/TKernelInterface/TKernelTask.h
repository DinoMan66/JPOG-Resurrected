// TTask - kernel-internal declaration: a unit of work owned by a TScheduler.
// vtable: [0] GetClass  [1] Delete  [2] destructor  [3] Create  [4] CreateFailed  [5] OnCreate  [6] OnUpdate
//         [7] OnUpdateKernelPaused  [8] OnDestroy  [9] OnChildDying  [10] OnChildDied  [11] OnActivate  [12] OnDeactivate
#ifndef TKERNELTASK_H
#define TKERNELTASK_H
#include "TKernelObject.h"
#include "TRef.h"

namespace Toshi {

class TScheduler;

class __declspec(dllexport) TTask : public TObject
{
public:
    TTask();
    virtual ~TTask();
    virtual TClass& GetClass() const;
    virtual bool Create();
    virtual bool CreateFailed();

    void Activate(bool activate);
    void DestroyTask();
    unsigned int GetFlags() const;
    bool IsDying() const;
    bool IsActive() const;
    bool IsCreated() const;
    TScheduler* GetScheduler();

    static TClass m_sClass;

protected:
    virtual bool OnCreate();
    virtual bool OnUpdate(float deltaTime);
    virtual bool OnUpdateKernelPaused();
    virtual void OnDestroy();
    virtual bool OnChildDying(const TTask* child);
    virtual void OnChildDied(const TClass& childClass, const TTask* child);
    virtual void OnActivate();
    virtual void OnDeactivate();

private:
    friend class TScheduler;

    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    int m_unk04;                            // +0x04
    int m_unk08;                            // +0x08
    TTask* m_unk0C;                         // +0x0C (list links point at the task itself while it is alone)
    TTask* m_unk10;                         // +0x10
    int m_unk14;                            // +0x14
    int m_unk18;                            // +0x18
    unsigned int m_uFlags;                  // +0x1C (1 created, 2 active, 4 dying)
    TRef<TScheduler> m_pScheduler;          // +0x20 (counted reference: the scheduler's count is at +0x04)
};

} // namespace Toshi
#endif
