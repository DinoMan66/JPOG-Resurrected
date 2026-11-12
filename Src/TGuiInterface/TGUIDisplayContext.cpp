// Z:\Toshi\Source\TGUI - TGUIDisplayContext. The original file name is not in the binary's strings.
// DrawFormattedText is still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIDisplayContext.h"

namespace Toshi {

TGUIDisplayContext::TGUIDisplayContext()
    : m_iClipDepth(0)
    , m_fBaseTime(0.0f)
    , m_fCurrentTime(0.0f)
{
}

TGUIDisplayContext::~TGUIDisplayContext()
{
}

// The clip stack has no overflow check on the last entry: pushing a 32nd clip writes past m_aClip (original bug).
void TGUIDisplayContext::PushClip(int x, int y, int width, int height)
{
    m_iClipDepth++;
    if (m_iClipDepth < MAX_CLIPS) {
        m_aClip[m_iClipDepth] = m_aClip[m_iClipDepth - 1];
    }
    m_aClip[m_iClipDepth].m_iX += x;
    m_aClip[m_iClipDepth].m_iY += y;
    m_aClip[m_iClipDepth].m_iWidth = width;
    m_aClip[m_iClipDepth].m_iHeight = height;
}

void TGUIDisplayContext::PopClip()
{
    int depth = m_iClipDepth - 1;
    if (depth >= 0) {
        m_iClipDepth = depth;
    } else {
        m_iClipDepth = 0;
    }
}

// Rotates around the centre of the current clip rectangle
void TGUIDisplayContext::PushRotation(float angle)
{
    PushRotation(angle, m_aClip[m_iClipDepth].m_iWidth / 2, m_aClip[m_iClipDepth].m_iHeight / 2);
}

void TGUIDisplayContext::DrawOutlineRectangle(const TGUIRectangle& rect, const TGUIColour& colour)
{
    Imp_DrawOutlineRectangle(rect.GetX(), rect.GetY(), rect.GetRight(), rect.GetBottom(), colour);
}

void TGUIDisplayContext::DrawOutlineRectangle(int x, int y, int width, int height, const TGUIColour& colour)
{
    Imp_DrawOutlineRectangle(x, y, width, height, colour);
}

void TGUIDisplayContext::DrawFilledRectangle(const TGUIRectangle& rect, const TGUIColour& colour)
{
    Imp_DrawFilledRectangle(rect.GetX(), rect.GetY(), rect.GetRight(), rect.GetBottom(), colour);
}

void TGUIDisplayContext::DrawFilledRectangle(int x, int y, int width, int height, const TGUIColour& colour)
{
    Imp_DrawFilledRectangle(x, y, width, height, colour);
}

void TGUIDisplayContext::DrawTextureSection(const TGUITextureSection* section, const TGUIColour& colour,
                                            const TGUIRectangle* rect, TGUIAlignment horizontal,
                                            TGUIAlignment vertical)
{
    Imp_DrawTextureSection(section, colour, rect->GetX(), rect->GetY(), rect->GetWidth(), rect->GetHeight(),
                           horizontal, vertical);
}

void TGUIDisplayContext::DrawTextureSection(const TGUITextureSection* section, const TGUIColour& colour,
                                            int x, int y, int width, int height,
                                            TGUIAlignment horizontal, TGUIAlignment vertical)
{
    Imp_DrawTextureSection(section, colour, x, y, width, height, horizontal, vertical);
}

float TGUIDisplayContext::GetCurrentTime() const
{
    return m_fCurrentTime;
}

void TGUIDisplayContext::SetCurrentTime(float time)
{
    m_fBaseTime = time;
}

void TGUIDisplayContext::SetTimeOffset(float offset)
{
    m_fCurrentTime = m_fBaseTime + offset;
}

TClass TGUIDisplayContext::m_sClass("TGUIDisplayContext", &TObject::m_sClass, TGUIDisplayContext::CreateObject,
                                    TGUIDisplayContext::CreateObjectInPlace, TGUIDisplayContext::InitialiseStatic,
                                    TGUIDisplayContext::DeinitialiseStatic, 0x10000);

TClass& TGUIDisplayContext::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIDisplayContext::DeinitialiseStatic()
{
}

void __stdcall TGUIDisplayContext::InitialiseStatic()
{
}

// The class is abstract, so the factory functions create nothing
TObject* __stdcall TGUIDisplayContext::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIDisplayContext::CreateObject()
{
    return 0;
}

} // namespace Toshi
