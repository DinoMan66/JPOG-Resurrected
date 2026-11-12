// Z:\Toshi\Source\TGUI - TGUIElement. The original file name is not in the binary's strings.
// Deserialise, Serialise, Paint, GetPreferredSize, FormatText and InitialiseStatic are still to do.
#define TGUIINTERFACE_EXPORTS
#include <new>
#include "TGUIElement.h"

namespace Toshi {

static const unsigned char COLOUR_FULL = 255;

TPCString* TGUIElement::ms_saElementTypeName = 0;
int TGUIElement::ms_iElementTypeCount = 0;

const TPCString& TGUIElement::GetElementTypeName(ElementType type)
{
    return ms_saElementTypeName[type];
}

int TGUIElement::GetElementTypeCount()
{
    return ms_iElementTypeCount;
}

void TGUIElement::DeinitialiseStatic()
{
    if (ms_saElementTypeName != 0) {
        delete[] ms_saElementTypeName;
    }
}

TGUIElement::TGUIElement()
    : m_eType(ELEMENT_NONE)
    , m_iParameter(0)
    , m_eAlignX(TGUIAlignment_Unknown0)
    , m_eFillX(FILL_VALUE_1)
    , m_eAlignY(TGUIAlignment_Unknown0)
    , m_eFillY(FILL_VALUE_1)
    , m_oColour(COLOUR_FULL, COLOUR_FULL, COLOUR_FULL, COLOUR_FULL)
{
}

TGUIElement::~TGUIElement()
{
    ChangeType(ELEMENT_NONE);
}

TGUIElement& TGUIElement::operator=(const TGUIElement& other)
{
    Assign(other);
    return *this;
}

TGUIElement& TGUIElement::Reset()
{
    ChangeType(ELEMENT_NONE);
    m_iParameter = 0;
    m_oColour = TGUIColour(COLOUR_FULL, COLOUR_FULL, COLOUR_FULL, COLOUR_FULL);
    m_eAlignX = TGUIAlignment_Unknown0;
    m_eAlignY = TGUIAlignment_Unknown0;
    m_eFillX = FILL_VALUE_1;
    m_eFillY = FILL_VALUE_1;
    return *this;
}

// Switches what the shared slots at +0x1C and +0x20 hold, clearing the old contents
void TGUIElement::ChangeType(ElementType type)
{
    if (type == m_eType) {
        return;
    }
    if (m_eType == ELEMENT_TEXT) {
        Label().~TLString();
    }
    if (type == ELEMENT_TEXTURE) {
        m_pTextureSection = 0;
    } else if (type == ELEMENT_TEXT) {
        m_pFont = 0;
        new (&Label()) TLString;
    }
    m_eType = type;
}

bool TGUIElement::IsDefined() const
{
    if (m_eType == ELEMENT_TEXTURE) {
        return m_iParameter > 0 || m_pTextureSection != 0;
    }
    if (m_eType == ELEMENT_TEXT) {
        return m_iParameter > 0 || m_pFont != 0;
    }
    return false;
}

bool TGUIElement::DeserialiseSolid(TGUIInterface* gui, const PProperties* properties)
{
    return true;
}

void TGUIElement::Assign(const TGUIElement& other)
{
    ChangeType(other.m_eType);
    m_iParameter = other.m_iParameter;
    m_oColour = other.m_oColour;
    m_eAlignX = other.m_eAlignX;
    m_eAlignY = other.m_eAlignY;
    m_eFillX = other.m_eFillX;
    m_eFillY = other.m_eFillY;
    if (m_eType == ELEMENT_TEXTURE) {
        m_pTextureSection = other.m_pTextureSection;
    } else if (m_eType == ELEMENT_TEXT) {
        SetLabel(other.Label());
        m_pFont = other.m_pFont;
    }
}

TLString& TGUIElement::GetLabelInternal()
{
    return Label();
}

int TGUIElement::GetParameterID() const
{
    return m_iParameter - 1;
}

TGUIElement::ElementType TGUIElement::GetElementType() const
{
    return m_eType;
}

TGUIElement::Fill TGUIElement::GetFillX() const
{
    return m_eFillX;
}

TGUIElement::Fill TGUIElement::GetFillY() const
{
    return m_eFillY;
}

TGUIAlignment TGUIElement::GetAlignX() const
{
    return m_eAlignX;
}

TGUIAlignment TGUIElement::GetAlignY() const
{
    return m_eAlignY;
}

const TGUIColour& TGUIElement::GetColour() const
{
    return m_oColour;
}

const TGUIFont* TGUIElement::GetFont() const
{
    return m_pFont;
}

const TLString& TGUIElement::GetLabel() const
{
    return Label();
}

const TGUITextureSection* TGUIElement::GetTextureSection() const
{
    return m_pTextureSection;
}

TGUIElement& TGUIElement::SetFillX(Fill fill)
{
    m_eFillX = fill;
    return *this;
}

TGUIElement& TGUIElement::SetFillY(Fill fill)
{
    m_eFillY = fill;
    return *this;
}

TGUIElement& TGUIElement::SetAlignX(TGUIAlignment align)
{
    m_eAlignX = align;
    return *this;
}

TGUIElement& TGUIElement::SetAlignY(TGUIAlignment align)
{
    m_eAlignY = align;
    return *this;
}

TGUIElement& TGUIElement::SetParameter(int id)
{
    m_iParameter = id + 1;
    return *this;
}

TGUIElement& TGUIElement::SetColour(const TGUIColour& colour)
{
    m_oColour = colour;
    return *this;
}

TGUIElement& TGUIElement::SetFont(const TGUIFont* font)
{
    ChangeType(ELEMENT_TEXT);
    m_pFont = font;
    return *this;
}

TGUIElement& TGUIElement::SetTextureSection()
{
    ChangeType(ELEMENT_TEXTURE);
    return *this;
}

TGUIElement& TGUIElement::SetTextureSection(const TGUITextureSection* section)
{
    ChangeType(ELEMENT_TEXTURE);
    m_pTextureSection = section;
    return *this;
}

TGUIElement& TGUIElement::SetLabel(const TLString& label)
{
    ChangeType(ELEMENT_TEXT);
    Label() = label;
    return *this;
}

} // namespace Toshi
