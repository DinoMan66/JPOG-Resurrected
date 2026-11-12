// Toshi::TGUIElement - one drawable piece of a GUI component: a texture section, or a font with a label
// (TGuiInterface.dll). The element is an array item of 0x24 bytes inside its component. The setters
// return the element so they can be chained.
// ElementType: the names are our own, taken from what ChangeType does with each value.
// Fill: the real enumerators are not recovered yet.
#ifndef TGUIELEMENT_H
#define TGUIELEMENT_H
#include "TGUIAPI.h"
#include "TPString.h"
#include "TLString.h"
#include "TGUIAlignment.h"
#include "TGUIColour.h"

class PProperties;
class PPropertyValue;

namespace Toshi {

class TGUIFont;
class TGUIFormattedText;
class TGUIInterface;
class TGUITextureSection;

class TGUI_API TGUIElement
{
public:
    enum ElementType
    {
        ELEMENT_NONE = 0,
        ELEMENT_TEXTURE = 1,    // m_pTextureSection is valid
        ELEMENT_TEXT = 2        // m_pFont and the label are valid
    };

    enum Fill
    {
        FILL_VALUE_0 = 0,       // placeholder names
        FILL_VALUE_1 = 1        // the default
    };

    TGUIElement();
    ~TGUIElement();
    TGUIElement& operator=(const TGUIElement& other);

    static const TPCString& GetElementTypeName(ElementType type);
    static int GetElementTypeCount();
    static void DeinitialiseStatic();

    TGUIElement& Reset();
    void ChangeType(ElementType type);
    bool IsDefined() const;
    void GetPreferredSize(PPropertyValue* value, int& width, int& height) const;
    void FormatText(PPropertyValue* value, int& width, int& height, int maxWidth, int maxHeight,
                    TGUIFormattedText* text) const;
    bool DeserialiseSolid(TGUIInterface* gui, const PProperties* properties);

    int GetParameterID() const;
    ElementType GetElementType() const;
    Fill GetFillX() const;
    Fill GetFillY() const;
    TGUIAlignment GetAlignX() const;
    TGUIAlignment GetAlignY() const;
    const TGUIColour& GetColour() const;
    const TGUIFont* GetFont() const;
    const TLString& GetLabel() const;
    const TGUITextureSection* GetTextureSection() const;

    TGUIElement& SetFillX(Fill fill);
    TGUIElement& SetFillY(Fill fill);
    TGUIElement& SetAlignX(TGUIAlignment align);
    TGUIElement& SetAlignY(TGUIAlignment align);
    TGUIElement& SetParameter(int id);
    TGUIElement& SetColour(const TGUIColour& colour);
    TGUIElement& SetFont(const TGUIFont* font);
    TGUIElement& SetTextureSection();
    TGUIElement& SetTextureSection(const TGUITextureSection* section);
    TGUIElement& SetLabel(const TLString& label);

protected:
    TLString& GetLabelInternal();
    void Assign(const TGUIElement& other);

private:
    TLString& Label() { return *reinterpret_cast<TLString*>(m_abLabel); }
    const TLString& Label() const { return *reinterpret_cast<const TLString*>(m_abLabel); }

    static TPCString* ms_saElementTypeName;
    static int ms_iElementTypeCount;

    ElementType m_eType;                // +0x00
    int m_iParameter;                   // +0x04 parameter id plus one; zero means none
    TGUIAlignment m_eAlignX;            // +0x08
    Fill m_eFillX;                      // +0x0C
    TGUIAlignment m_eAlignY;            // +0x10
    Fill m_eFillY;                      // +0x14
    TGUIColour m_oColour;               // +0x18
    union {
        const TGUITextureSection* m_pTextureSection;
        const TGUIFont* m_pFont;
    };                                  // +0x1C
    // +0x20: a TLString that only exists while the type is ELEMENT_TEXT. ChangeType constructs and destroys
    // it by hand, so it is raw storage here and not a member the constructor would initialise.
    unsigned char m_abLabel[sizeof(TLString)];
};

} // namespace Toshi
#endif
