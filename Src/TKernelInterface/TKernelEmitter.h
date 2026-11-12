// TGenericEmitter / TGenericListener - the untyped event emitter behind TEmitter<>/TListener<>.
// Kernel-internal header. Layouts reconstructed from the constructors and Throw/Connect.
#ifndef TKERNELEMITTER_H
#define TKERNELEMITTER_H
#include "TGenericLists.h"

namespace Toshi {

// Receives (listener user data, emitter owner, event data); returning false stops the dispatch.
typedef bool (__stdcall *TGenericListenerCallback)(void* userData, void* owner, void* data);

// A node of the emitter's list: link pair and priority from the priority-list node, then user data + callback.
class __declspec(dllexport) TGenericListener : public TGenericPriList::TNode
{
protected:
    TGenericListener();
    TGenericListener(TGenericEmitter* emitter, void* userData, TGenericListenerCallback callback, int priority);
    ~TGenericListener();

    void Connect(TGenericEmitter* emitter, void* userData, TGenericListenerCallback callback, int priority);
    void Disconnect();

private:
    friend class TGenericEmitter;
    void* m_pUserData;                      // +0x0C
    TGenericListenerCallback m_pCallback;   // +0x10
};

// The emitter is the list root (next/prev, as a TGenericDList) followed by the owner pointer.
class __declspec(dllexport) TGenericEmitter : public TGenericDList
{
public:
    TGenericEmitter(void* owner = 0);

protected:
    ~TGenericEmitter();

    void Create(void* owner);
    void Destroy();
    void Throw(void* data);

private:
    friend class TGenericListener;
    void* m_pOwner;                         // +0x08
};

} // namespace Toshi
#endif
