// TGUIFont accessors. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TGUIFont.h"
#include "TGUITextureSection.h"

namespace Toshi {

TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* TGUIFont::ms_oPropertySetOrdered;
TArray<TGUIPropertySpec*>* TGUIFont::ms_oPropertySet;

const TArray<TGUIPropertySpec*>* TGUIFont::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* TGUIFont::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

void TGUIFont::SetInterface(TGUIInterface* gui)
{
    m_pInterface = gui;
}

TGUIInterface* TGUIFont::GetInterface() const
{
    return m_pInterface;
}

TArray<short>& TGUIFont::GetTextureList()
{
    return m_oTextures;
}

TNodeList<TGUITextureSection>& TGUIFont::GetGlyphList()
{
    return m_oGlyphs;
}

void TGUIFont::SetSpacing(int spacing)
{
    m_iSpacing = spacing;
}

int TGUIFont::GetSpacing() const
{
    return m_iSpacing;
}

void TGUIFont::SetFontHeight(int height)
{
    m_iFontHeight = height;
}

int TGUIFont::GetFontHeight() const
{
    return m_iFontHeight;
}

const TPCString& TGUIFont::GetName() const
{
    return m_oName;
}

void TGUIFont::SetFontID(int id)
{
    m_iFontID = id;
}

int TGUIFont::GetFontID() const
{
    return m_iFontID;
}

void TGUIFont::SetName(const TPCString& name)
{
    m_oName = name;
}

bool TGUIFont::Create(const TPCString& name, int height, int spacing)
{
    m_oName = name;
    m_iFontHeight = height;
    m_iSpacing = spacing;
    return true;
}

float TGUIFont::ms_fScaleY = 1.0f;
float TGUIFont::ms_fScaleX = 1.0f;

void TGUIFont::SetScale(float scaleX, float scaleY)
{
    ms_fScaleX = scaleX;
    ms_fScaleY = scaleY;
}

} // namespace Toshi
