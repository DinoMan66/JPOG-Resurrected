// Z:\Toshi\Source\TGUI - TGUITextComponent. The original file name is not in the binary's strings.
// Paint and InitialiseStatic (which fills in ms_component_info) are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUITextComponent.h"
#include "TGUIComponentInfo.h"

namespace Toshi {

TGUIComponentInfo TGUITextComponent::ms_component_info;

TGUITextComponent::TGUITextComponent(const TGUITextComponent& other)
    : TGUIComponent(other)
{
    CopyElements(&m_oText, &other.m_oText, 1);
}

TGUITextComponent::~TGUITextComponent()
{
}

TGUITextComponent* TGUITextComponent::Clone() const
{
    return new TGUITextComponent(*this);
}

// A maximum width of -1 means there is no room for any text
bool TGUITextComponent::GetPreferredSize(PPropertyValue* value, int& width, int& height,
                                         short maxWidth, short maxHeight) const
{
    if (maxWidth == -1) {
        width = 0;
        height = 0;
        return false;
    }
    m_oText.FormatText(value, width, height, maxWidth, maxHeight, 0);
    return true;
}

TGUIElement* TGUITextComponent::GetElements()
{
    return &m_oText;
}

const TGUIComponentInfo* TGUITextComponent::GetComponentInfo() const
{
    return &ms_component_info;
}

TClass TGUITextComponent::m_sClass("TGUITextComponent", &TGUIComponent::m_sClass, TGUITextComponent::CreateObject,
                                   TGUITextComponent::CreateObjectInPlace, TGUITextComponent::InitialiseStatic,
                                   TGUITextComponent::DeinitialiseStatic, 0x10000);

TClass& TGUITextComponent::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUITextComponent::DeinitialiseStatic()
{
}

TObject* __stdcall TGUITextComponent::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUITextComponent;
}

TObject* __stdcall TGUITextComponent::CreateObject()
{
    return new TGUITextComponent;
}

} // namespace Toshi
