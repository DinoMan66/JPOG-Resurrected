// Z:\Toshi\Source\TGUI - TGUITextureAnimation: the constructors and the destructor.
// They live in their own file so that CreateObject and CreateObjectInPlace in TGUITextureAnimation.cpp call the
// constructor instead of containing a copy of it (MATCHING_NOTES "TU-split rule").
#define TGUIINTERFACE_EXPORTS
#include "TGUITextureAnimation.h"
#include "TNewDelete.h"

namespace Toshi {

TGUITextureAnimation::TGUITextureAnimation()
    : m_fFrequency(1.0f), m_oFrames(10)
{
}

TGUITextureAnimation::TGUITextureAnimation(const TGUITextureAnimation& other)
    : TGUITextureSection(other), m_fFrequency(other.m_fFrequency), m_oFrames(other.m_oFrames)
{
}

TGUITextureAnimation::~TGUITextureAnimation()
{
}

} // namespace Toshi
