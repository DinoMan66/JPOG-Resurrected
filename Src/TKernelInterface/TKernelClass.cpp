// Z:\Toshi\Source\TKernel\TClass.cpp - run-time class description. Only the accessors are written; the constructor,
// Find and the class tree (CreateObject, DeleteChildren, AttachClassToParent ...) are not.
#define TOSHI_API __declspec(dllexport)
#include "TKernelClass.h"
#include "TKernelObject.h"
#include "TKernelMisc.h"

namespace Toshi {

TClass::TClass(const char* name, TClass* parent, CreateObjectFn create, CreateObjectInPlaceFn createInPlace,
               StaticFn initialise, StaticFn deinitialise, unsigned int version)
{
    m_pName = name;
    m_pCreate = create;
    m_pCreateInPlace = createInPlace;
    m_pInitialise = initialise;
    m_pDeinitialise = deinitialise;
    m_pParent = parent;
    m_uVersion = version;
    m_bStaticInitialised = false;
    AttachClassToParent();
}

TClass::~TClass()
{
    DetachClassFromParent();
    m_pParent = m_pNextSibling = m_pFirstChild = 0;
    if (m_bStaticInitialised == true)
    {
        DeinitialiseStatic();
    }
}

const char* TClass::GetName() const
{
    return m_pName;
}

const TClass* TClass::GetParent() const
{
    return m_pParent;
}

unsigned int TClass::GetVersion() const
{
    return m_uVersion;
}

unsigned short TClass::GetVersionMajor() const
{
    return m_oParts.m_uVersionMajor;
}

unsigned short TClass::GetVersionMinor() const
{
    return m_oParts.m_uVersionMinor;
}

bool TClass::IsExactly(const TClass& other) const
{
    if (this != &other) {
        return false;
    }
    return true;
}

bool TClass::IsStaticInitialised() const
{
    return m_bStaticInitialised;
}

bool TClass::DetachClassFromParent()
{
    return true;
}

void TClass::InitialiseStatic()
{
    if (m_pInitialise != 0) {
        m_pInitialise();
        m_bStaticInitialised = true;
    }
}

void TClass::DeinitialiseStatic()
{
    if (m_pDeinitialise != 0) {
        m_bStaticInitialised = false;
        m_pDeinitialise();
    }
}

TObject* TClass::CreateObjectInPlace(void* memory) const
{
    if (m_pCreateInPlace != 0) {
        return m_pCreateInPlace(memory);
    }
    return 0;
}

TObject* TClass::CreateObject() const
{
    if (m_pCreate != 0)
    {
        return m_pCreate();
    }
    return 0;
}

bool TClass::IsAttached() const
{
    if (m_pParent != 0 && m_pParent->m_pFirstChild != 0)
    {
        for (TClass* sibling = m_pParent->m_pFirstChild; sibling != 0; sibling = sibling->m_pNextSibling)
        {
            if (sibling == this)
            {
                return true;
            }
        }
    }
    return false;
}

// Links this class at the head of its parent's child list (unless it is already linked).
bool TClass::AttachClassToParent()
{
    if (m_pParent != 0 && IsAttached() == false)
    {
        m_pNextSibling = m_pParent->m_pFirstChild;
        m_pParent->m_pFirstChild = this;
        return true;
    }
    return false;
}

// Classes are identified by their name pointer.
bool TClass::operator==(const TClass& other) const
{
    return m_pName == other.m_pName;
}

const TClass* TClass::Find(const char* name, const TClass* parent)
{
    if (parent == 0)
    {
        parent = &TObject::m_sClass;
    }
    return FindRecurse(name, parent, false);
}

// Depth-first search of the class tree by name (case-insensitive). 'siblings' is false for the
// starting class so that only its subtree is searched.
const TClass* TClass::FindRecurse(const char* name, const TClass* cls, bool siblings)
{
    while (cls != 0)
    {
        const TClass* next = (siblings == true) ? cls->m_pNextSibling : 0;
        if (TSystem::StringCompareNoCase(cls->m_pName, name, -1) == 0)
        {
            return cls;
        }
        if (cls->m_pFirstChild != 0)
        {
            const TClass* found = FindRecurse(name, cls->m_pFirstChild, true);
            if (found != 0)
            {
                return found;
            }
        }
        cls = next;
    }
    return 0;
}

// Visits every descendant of this class: onVisit for each one, and onEnter / onLeave around the
// descendants of a class that has any.
void TClass::RecurseTree2(TreeFn onEnter, TreeFn onLeave, TreeFn onVisit, void* data)
{
    for (TClass* child = m_pFirstChild; child != 0; child = child->m_pNextSibling) {
        if (onVisit != 0) {
            onVisit(child, data);
        }
        if (child->m_pFirstChild != 0) {
            if (onEnter != 0) {
                onEnter(this, data);
            }
            child->RecurseTree2(onEnter, onLeave, onVisit, data);
            if (onLeave != 0) {
                onLeave(this, data);
            }
        }
    }
}

} // namespace Toshi
