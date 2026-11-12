// Z:\Toshi\Source\TGUI - TGUIFrameComponent. The original file name is not in the binary's strings.
// GetPreferredSize, CalculateDimensions, Paint and InitialiseStatic are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIFrameComponent.h"
#include "TGUIComponentInfo.h"
#include "TMemory.h"

namespace Toshi {

TGUIComponentInfo TGUIFrameComponent::ms_component_info;

TGUIFrameComponent::TGUIFrameComponent(const TGUIFrameComponent& other)
    : TGUIComponent(other)
{
    CopyElements(m_aElements, other.m_aElements, ELEMENT_COUNT);
}

TGUIFrameComponent::~TGUIFrameComponent()
{
}

TGUIComponent* TGUIFrameComponent::Clone() const
{
    return new TGUIFrameComponent(*this);
}

TGUIElement* TGUIFrameComponent::GetElements()
{
    return m_aElements;
}

const TGUIComponentInfo* TGUIFrameComponent::GetComponentInfo() const
{
    return &ms_component_info;
}

// The cache was allocated with tmalloc by Paint
void TGUIFrameComponent::DestroyCache(void* cache) const
{
    tfree(cache);
}

TClass TGUIFrameComponent::m_sClass("TGUIFrameComponent", &TGUIComponent::m_sClass, TGUIFrameComponent::CreateObject,
                                    TGUIFrameComponent::CreateObjectInPlace, TGUIFrameComponent::InitialiseStatic,
                                    TGUIFrameComponent::DeinitialiseStatic, 0x10000);

TClass& TGUIFrameComponent::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIFrameComponent::DeinitialiseStatic()
{
}

TObject* __stdcall TGUIFrameComponent::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUIFrameComponent;
}

TObject* __stdcall TGUIFrameComponent::CreateObject()
{
    return new TGUIFrameComponent;
}

} // namespace Toshi
