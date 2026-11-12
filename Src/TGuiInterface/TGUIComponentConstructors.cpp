// Z:\Toshi\Source\TGUI - the default constructors of the TGUI components.
// They sit in a file of their own: next to CreateObject/CreateObjectInPlace the compiler would expand
// them inline, while the original calls them.
#define TGUIINTERFACE_EXPORTS
#include "TGUIFrameComponent.h"
#include "TGUITextComponent.h"
#include "TGUIHorizontalTripletComponent.h"
#include "TGUIVerticalTripletComponent.h"
#include "TGUIIconComponent.h"

namespace Toshi {

TGUIFrameComponent::TGUIFrameComponent()
{
}

TGUITextComponent::TGUITextComponent()
{
}

TGUIHorizontalTripletComponent::TGUIHorizontalTripletComponent()
{
}

TGUIVerticalTripletComponent::TGUIVerticalTripletComponent()
{
}

TGUIIconComponent::TGUIIconComponent()
{
}

} // namespace Toshi
