// Toshi::TGUIFontGlyph (TGuiInterface.dll): the picture of one character of a GUI font: a texture section
// plus the character code, the baseline and the kerning (extra space before and after the character).
// It has no TClass of its own and shares its base class's.
// Size 0x30.
#ifndef TGUIFONTGLYPH_H
#define TGUIFONTGLYPH_H
#include "TGUIAPI.h"
#include "TGUITextureSection.h"

namespace Toshi {

class TGUI_API TGUIFontGlyph : public TGUITextureSection
{
public:
    TGUIFontGlyph();
    explicit TGUIFontGlyph(unsigned short character);
    virtual ~TGUIFontGlyph();

    virtual TGUIFontGlyph* Clone() const;

    void SetKerningRight(short kerning) { m_sKerningRight = kerning; }
    void SetKerningLeft(short kerning) { m_sKerningLeft = kerning; }
    void SetBaseline(short baseline) { m_sBaseline = baseline; }
    void SetCharacter(unsigned short character) { m_usCharacter = character; }
    short GetKerningRight() const { return m_sKerningRight; }
    short GetKerningLeft() const { return m_sKerningLeft; }
    short GetBaseline() const { return m_sBaseline; }
    unsigned short GetCharacter() const { return m_usCharacter; }

protected:
    TGUIFontGlyph(const TGUIFontGlyph& other);

private:
    unsigned short m_usCharacter;   // +0x28
    short m_sBaseline;              // +0x2A
    short m_sKerningLeft;           // +0x2C
    short m_sKerningRight;          // +0x2E
};

} // namespace Toshi
#endif
