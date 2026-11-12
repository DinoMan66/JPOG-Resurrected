// Z:\Toshi\Source\TKernel\TEmitter.cpp - untyped event emitter and listener.
#define TOSHI_API __declspec(dllexport)
#include "TKernelEmitter.h"

namespace Toshi {

// ---- TGenericListener
TGenericListener::TGenericListener()
{
    m_pUserData = 0;
    m_pCallback = 0;
}

TGenericListener::TGenericListener(TGenericEmitter* emitter, void* userData, TGenericListenerCallback callback, int priority)
{
    Connect(emitter, userData, callback, priority);
}

TGenericListener::~TGenericListener()
{
    Disconnect();
}

void TGenericListener::Disconnect()
{
    m_pPrev->m_pNext = m_pNext;
    m_pNext->m_pPrev = m_pPrev;
    m_pNext = this;
    m_pPrev = this;
    m_pUserData = 0;
    m_pCallback = 0;
}

void TGenericListener::Connect(TGenericEmitter* emitter, void* userData, TGenericListenerCallback callback, int priority)
{
    m_pUserData = userData;
    m_pCallback = callback;
    m_iPriority = priority;
    ((TGenericPriList*)emitter)->Insert(this);
}

// ---- TGenericEmitter
TGenericEmitter::TGenericEmitter(void* owner)
{
    Create(owner);
}

TGenericEmitter::~TGenericEmitter()
{
    Destroy();
}

void TGenericEmitter::Create(void* owner)
{
    m_pOwner = owner;
}

void TGenericEmitter::Destroy()
{
    TGenericListener* listener = (TGenericListener*)m_oRoot.m_pNext;
    while (listener != (TGenericListener*)this) {
        listener->Disconnect();
        listener = (TGenericListener*)m_oRoot.m_pNext;
    }
    m_pOwner = 0;
}

void TGenericEmitter::Throw(void* data)
{
    TGenericListener* listener = (TGenericListener*)m_oRoot.m_pNext;
    while (listener != (TGenericListener*)this) {
        TGenericListener* next = (TGenericListener*)listener->m_pNext;
        // a listener returning false stops the broadcast
        if (!listener->m_pCallback(listener->m_pUserData, m_pOwner, data)) {
            break;
        }
        listener = next;
    }
}

} // namespace Toshi
