// Z:\Toshi\Source\TGUI - TGUITextureAnimation. The original file name is not in the binary's strings.
// The constructors, the destructor and the other bounding box function are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUITextureAnimation.h"
#include "TNewDelete.h"

namespace Toshi {

TClass TGUITextureAnimation::m_sClass("TGUITextureAnimation", &TGUITextureSection::m_sClass,
                                      TGUITextureAnimation::CreateObject, TGUITextureAnimation::CreateObjectInPlace,
                                      TGUITextureAnimation::InitialiseStatic, TGUITextureAnimation::DeinitialiseStatic,
                                      0x10000);

TClass& TGUITextureAnimation::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUITextureAnimation::DeinitialiseStatic()
{
}

void __stdcall TGUITextureAnimation::InitialiseStatic()
{
}

TObject* __stdcall TGUITextureAnimation::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUITextureAnimation;
}

TObject* __stdcall TGUITextureAnimation::CreateObject()
{
    return new TGUITextureAnimation;
}

// Frame 0 is the section's own bounding box, the others are the box of each frame
void TGUITextureAnimation::GetBBox(unsigned short& x, unsigned short& y, unsigned short& width,
                                   unsigned short& height, int frame) const
{
    if (frame == 0) {
        TGUITextureSection::GetBBox(x, y, width, height, frame);
    } else {
        const Frame& entry = m_oFrames[frame - 1];
        x = entry.m_usX;
        y = entry.m_usY;
        width = entry.m_usWidth;
        height = entry.m_usHeight;
    }
}

void TGUITextureAnimation::SetBBox(unsigned short x, unsigned short y, unsigned short width, unsigned short height,
                                   int frame)
{
    if (frame == 0) {
        TGUITextureSection::SetBBox(x, y, width, height, frame);
    } else {
        Frame& entry = m_oFrames[frame - 1];
        entry.m_usX = x;
        entry.m_usY = y;
        entry.m_usWidth = width;
        entry.m_usHeight = height;
    }
}

void TGUITextureAnimation::RemoveFrame(int number)
{
    m_oFrames.Remove(number - 1);
}

void TGUITextureAnimation::InsertFrame(int number, Frame& frame)
{
    m_oFrames.InsertAt(number - 1, 1);
    m_oFrames[number - 1] = frame;
}

TGUITextureAnimation* TGUITextureAnimation::Clone() const
{
    return new TGUITextureAnimation(*this);
}

} // namespace Toshi
