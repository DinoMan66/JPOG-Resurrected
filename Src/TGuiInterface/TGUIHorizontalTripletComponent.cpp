// Z:\Toshi\Source\TGUI - TGUIHorizontalTripletComponent. The original file name is not in the binary's strings.
// CalculateDimensions, Paint and InitialiseStatic (which fills in ms_component_info) are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIHorizontalTripletComponent.h"
#include "TGUIComponentInfo.h"

namespace Toshi {

TGUIComponentInfo TGUIHorizontalTripletComponent::ms_component_info;

TGUIHorizontalTripletComponent::TGUIHorizontalTripletComponent(const TGUIHorizontalTripletComponent& other)
    : TGUIComponent(other)
{
    CopyElements(m_aElements, other.m_aElements, ELEMENT_COUNT);
}

TGUIHorizontalTripletComponent::~TGUIHorizontalTripletComponent()
{
}

TGUIComponent* TGUIHorizontalTripletComponent::Clone() const
{
    return new TGUIHorizontalTripletComponent(*this);
}

bool TGUIHorizontalTripletComponent::GetPreferredSize(PPropertyValue* value, int& width, int& height,
                                                      short maxWidth, short maxHeight) const
{
    int contentHeight = 0;
    int leftWidth = 0;
    int middleWidth = 0;
    int rightWidth = 0;
    CalculateDimensions(value, contentHeight, leftWidth, middleWidth, rightWidth);
    int totalWidth = leftWidth + middleWidth + rightWidth + GetMarginLeft() + GetMarginRight();
    int totalHeight = contentHeight + GetMarginTop() + GetMarginBottom();
    width = totalWidth;
    height = totalHeight;
    return true;
}

TGUIElement* TGUIHorizontalTripletComponent::GetElements()
{
    return m_aElements;
}

const TGUIComponentInfo* TGUIHorizontalTripletComponent::GetComponentInfo() const
{
    return &ms_component_info;
}

TClass TGUIHorizontalTripletComponent::m_sClass("TGUIHorizontalTripletComponent", &TGUIComponent::m_sClass,
                                                TGUIHorizontalTripletComponent::CreateObject,
                                                TGUIHorizontalTripletComponent::CreateObjectInPlace,
                                                TGUIHorizontalTripletComponent::InitialiseStatic,
                                                TGUIHorizontalTripletComponent::DeinitialiseStatic, 0x10000);

TClass& TGUIHorizontalTripletComponent::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIHorizontalTripletComponent::DeinitialiseStatic()
{
}

TObject* __stdcall TGUIHorizontalTripletComponent::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUIHorizontalTripletComponent;
}

TObject* __stdcall TGUIHorizontalTripletComponent::CreateObject()
{
    return new TGUIHorizontalTripletComponent;
}

} // namespace Toshi
