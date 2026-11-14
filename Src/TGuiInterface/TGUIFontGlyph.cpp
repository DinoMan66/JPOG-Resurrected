// Z:\Toshi\Source\TGUI - TGUIFontGlyph. The original file name is not in the binary's strings.
// Deserialise and Serialise are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIFontGlyph.h"
#include "TNewDelete.h"

namespace Toshi {

TGUIFontGlyph* TGUIFontGlyph::Clone() const
{
    return new TGUIFontGlyph(*this);
}

TGUIFontGlyph::TGUIFontGlyph()
    : m_usCharacter(0), m_sBaseline(0), m_sKerningLeft(0), m_sKerningRight(0)
{
}

TGUIFontGlyph::TGUIFontGlyph(unsigned short character)
    : m_usCharacter(character), m_sBaseline(0), m_sKerningLeft(0), m_sKerningRight(0)
{
}

TGUIFontGlyph::TGUIFontGlyph(const TGUIFontGlyph& other)
    : TGUITextureSection(other), m_usCharacter(other.m_usCharacter), m_sBaseline(other.m_sBaseline),
      m_sKerningLeft(other.m_sKerningLeft), m_sKerningRight(other.m_sKerningRight)
{
}

TGUIFontGlyph::~TGUIFontGlyph()
{
}

} // namespace Toshi
