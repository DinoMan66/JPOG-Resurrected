// Z:\Toshi\Source\TGUI - TGUIVerticalTripletComponent. The original file name is not in the binary's strings.
// CalculateDimensions, Paint and InitialiseStatic (which fills in ms_component_info) are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIVerticalTripletComponent.h"
#include "TGUIComponentInfo.h"

namespace Toshi {

TGUIComponentInfo TGUIVerticalTripletComponent::ms_component_info;

TGUIVerticalTripletComponent::TGUIVerticalTripletComponent(const TGUIVerticalTripletComponent& other)
    : TGUIComponent(other)
{
    CopyElements(m_aElements, other.m_aElements, ELEMENT_COUNT);
}

TGUIVerticalTripletComponent::~TGUIVerticalTripletComponent()
{
}

TGUIComponent* TGUIVerticalTripletComponent::Clone() const
{
    return new TGUIVerticalTripletComponent(*this);
}

bool TGUIVerticalTripletComponent::GetPreferredSize(PPropertyValue* value, int& width, int& height,
                                                    short maxWidth, short maxHeight) const
{
    int contentWidth = 0;
    int topHeight = 0;
    int middleHeight = 0;
    int bottomHeight = 0;
    CalculateDimensions(value, contentWidth, topHeight, middleHeight, bottomHeight);
    width = contentWidth;
    height = topHeight + middleHeight + bottomHeight;
    return true;
}

TGUIElement* TGUIVerticalTripletComponent::GetElements()
{
    return m_aElements;
}

const TGUIComponentInfo* TGUIVerticalTripletComponent::GetComponentInfo() const
{
    return &ms_component_info;
}

TClass TGUIVerticalTripletComponent::m_sClass("TGUIVerticalTripletComponent", &TGUIComponent::m_sClass,
                                                TGUIVerticalTripletComponent::CreateObject,
                                                TGUIVerticalTripletComponent::CreateObjectInPlace,
                                                TGUIVerticalTripletComponent::InitialiseStatic,
                                                TGUIVerticalTripletComponent::DeinitialiseStatic, 0x10000);

TClass& TGUIVerticalTripletComponent::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIVerticalTripletComponent::DeinitialiseStatic()
{
}

TObject* __stdcall TGUIVerticalTripletComponent::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUIVerticalTripletComponent;
}

TObject* __stdcall TGUIVerticalTripletComponent::CreateObject()
{
    return new TGUIVerticalTripletComponent;
}

} // namespace Toshi
