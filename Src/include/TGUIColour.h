// Toshi::TGUIColour - 32-bit colour, four bytes in the order alpha, red, green, blue (TGuiInterface.dll).
// The copy constructor is the compiler-generated one.
#ifndef TGUICOLOUR_H
#define TGUICOLOUR_H
#include "TGUIAPI.h"

namespace Toshi {

class TGUI_API TGUIColour
{
public:
    // tag types that select how a packed 32-bit value is laid out
    enum FormatARGB { FORMAT_ARGB };
    enum FormatABGR { FORMAT_ABGR };

    TGUIColour();                                                           // opaque white
    TGUIColour(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
    {
        m_ucAlpha = alpha;
        m_ucRed = red;
        m_ucGreen = green;
        m_ucBlue = blue;
    }
    TGUIColour(float red, float green, float blue, float alpha);            // components in 0..1
    TGUIColour(unsigned int argb, FormatARGB format);
    TGUIColour(unsigned int abgr, FormatABGR format);

    TGUIColour& operator=(const TGUIColour& other)
    {
        m_ucRed = other.m_ucRed;
        m_ucGreen = other.m_ucGreen;
        m_ucBlue = other.m_ucBlue;
        m_ucAlpha = other.m_ucAlpha;
        return *this;
    }
    bool operator==(const TGUIColour& other);
    bool operator!=(const TGUIColour& other);
    TGUIColour& operator*=(const TGUIColour& other);                        // channel-wise modulate

    void SetAlpha(float alpha);
    unsigned int GetARGB() const;
    unsigned int GetABGR() const;
    unsigned int GetPlatformColour() const;
    void Get(float& alpha, float& red, float& green, float& blue) const;    // components in 0..1

private:
    unsigned char m_ucAlpha;    // +0x00
    unsigned char m_ucRed;      // +0x01
    unsigned char m_ucGreen;    // +0x02
    unsigned char m_ucBlue;     // +0x03
};

} // namespace Toshi
#endif
