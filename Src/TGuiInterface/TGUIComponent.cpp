// Z:\Toshi\Source\TGUI - TGUIComponent. The original file name is not in the binary's strings.
// Deserialise, Serialise, InitialiseStatic and the cache are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIComponent.h"
#include "TGUIElement.h"
#include "TGUIComponentInfo.h"

namespace Toshi {

TGUIComponent::TGUIComponent()
    : m_cMarginLeft(0)
    , m_cMarginRight(0)
    , m_cMarginTop(0)
    , m_cMarginBottom(0)
{
    m_apChildren[0] = 0;
    m_apChildren[1] = 0;
}

TGUIComponent::TGUIComponent(const TGUIComponent& other)
    : m_cMarginLeft(other.m_cMarginLeft)
    , m_cMarginRight(other.m_cMarginRight)
    , m_cMarginTop(other.m_cMarginTop)
    , m_cMarginBottom(other.m_cMarginBottom)
{
    for (int i = 0; i < 2; i++) {
        if (other.m_apChildren[i]) {
            m_apChildren[i] = other.m_apChildren[i]->Clone();
        } else {
            m_apChildren[i] = 0;
        }
    }
}

TGUIComponent::~TGUIComponent()
{
    for (int i = 0; i < 2; i++) {
        if (m_apChildren[i]) {
            delete m_apChildren[i];
        }
    }
}

void TGUIComponent::NotifyElementsChanged()
{
}

void TGUIComponent::DestroyCache(void* cache) const
{
}

void TGUIComponent::CopyElements(TGUIElement* destination, const TGUIElement* source, int count)
{
    for (int i = 0; i < count; i++) {
        destination[i] = source[i];
    }
}

TGUIElement& TGUIComponent::GetElement(const TPCString& name)
{
    return GetElement(FindElementName(name));
}

TGUIElement& TGUIComponent::GetElement(int index)
{
    return GetElements()[index];
}

// The element names come from the component's info; the result is the index or -1
int TGUIComponent::FindElementName(const TPCString& name) const
{
    for (int i = 0; i < GetComponentInfo()->GetElementCount(); i++) {
        if (GetComponentInfo()->GetElementName(i) == name) {
            return i;
        }
    }
    return -1;
}

void TGUIComponent::GetMargins(int& left, int& right, int& top, int& bottom)
{
    left = m_cMarginLeft;
    right = m_cMarginRight;
    top = m_cMarginTop;
    bottom = m_cMarginBottom;
}

void TGUIComponent::SetMargins(int left, int right, int top, int bottom)
{
    m_cMarginLeft = left;
    m_cMarginRight = right;
    m_cMarginTop = top;
    m_cMarginBottom = bottom;
}

void TGUIComponent::SetMarginLeft(int margin)
{
    m_cMarginLeft = margin;
}

void TGUIComponent::SetMarginRight(int margin)
{
    m_cMarginRight = margin;
}

void TGUIComponent::SetMarginTop(int margin)
{
    m_cMarginTop = margin;
}

void TGUIComponent::SetMarginBottom(int margin)
{
    m_cMarginBottom = margin;
}

TClass TGUIComponent::m_sClass("TGUIComponent", &TObject::m_sClass, TGUIComponent::CreateObject,
                               TGUIComponent::CreateObjectInPlace, TGUIComponent::InitialiseStatic,
                               TGUIComponent::DeinitialiseStatic, 0x10000);

TClass& TGUIComponent::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIComponent::DeinitialiseStatic()
{
}

// The class is abstract, so the factory functions create nothing
TObject* __stdcall TGUIComponent::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIComponent::CreateObject()
{
    return 0;
}

} // namespace Toshi
