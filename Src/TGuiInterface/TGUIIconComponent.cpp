// Z:\Toshi\Source\TGUI - TGUIIconComponent. The original file name is not in the binary's strings.
// Paint and InitialiseStatic (which fills in ms_component_info) are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIIconComponent.h"
#include "TGUIComponentInfo.h"

namespace Toshi {

TGUIComponentInfo TGUIIconComponent::ms_component_info;

TGUIIconComponent::TGUIIconComponent(const TGUIIconComponent& other)
    : TGUIComponent(other)
{
    CopyElements(&m_oIcon, &other.m_oIcon, 1);
}

TGUIIconComponent::~TGUIIconComponent()
{
}

TGUIIconComponent* TGUIIconComponent::Clone() const
{
    return new TGUIIconComponent(*this);
}

bool TGUIIconComponent::GetPreferredSize(PPropertyValue* value, int& width, int& height,
                                         short maxWidth, short maxHeight) const
{
    m_oIcon.GetPreferredSize(value, width, height);
    width += GetMarginLeft() + GetMarginRight();
    height += GetMarginTop() + GetMarginBottom();
    return true;
}

TGUIElement* TGUIIconComponent::GetElements()
{
    return &m_oIcon;
}

const TGUIComponentInfo* TGUIIconComponent::GetComponentInfo() const
{
    return &ms_component_info;
}

TClass TGUIIconComponent::m_sClass("TGUIIconComponent", &TGUIComponent::m_sClass, TGUIIconComponent::CreateObject,
                                   TGUIIconComponent::CreateObjectInPlace, TGUIIconComponent::InitialiseStatic,
                                   TGUIIconComponent::DeinitialiseStatic, 0x10000);

TClass& TGUIIconComponent::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIIconComponent::DeinitialiseStatic()
{
}

TObject* __stdcall TGUIIconComponent::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUIIconComponent;
}

TObject* __stdcall TGUIIconComponent::CreateObject()
{
    return new TGUIIconComponent;
}

} // namespace Toshi
