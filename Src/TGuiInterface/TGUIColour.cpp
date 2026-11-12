// Z:\Toshi\Source\TGUI\TGUIColour.cpp
#define TGUIINTERFACE_EXPORTS
#include "TGUIColour.h"

namespace Toshi {

TGUIColour::TGUIColour()
{
    m_ucAlpha = 255;
    m_ucRed = 255;
    m_ucGreen = 255;
    m_ucBlue = 255;
}

TGUIColour::TGUIColour(float red, float green, float blue, float alpha)
{
    m_ucAlpha = (unsigned char)(alpha * 255.0f);
    m_ucRed = (unsigned char)(red * 255.0f);
    m_ucGreen = (unsigned char)(green * 255.0f);
    m_ucBlue = (unsigned char)(blue * 255.0f);
}

TGUIColour::TGUIColour(unsigned int argb, FormatARGB format)
{
    m_ucAlpha = (unsigned char)(argb >> 24);
    m_ucRed = (unsigned char)(argb >> 16);
    m_ucGreen = (unsigned char)(argb >> 8);
    m_ucBlue = (unsigned char)argb;
}

TGUIColour::TGUIColour(unsigned int abgr, FormatABGR format)
{
    m_ucAlpha = (unsigned char)(abgr >> 24);
    m_ucRed = (unsigned char)abgr;
    m_ucGreen = (unsigned char)(abgr >> 8);
    m_ucBlue = (unsigned char)(abgr >> 16);
}

bool TGUIColour::operator==(const TGUIColour& other)
{
    // all four bytes at once
    return *(const unsigned int*)this == *(const unsigned int*)&other;
}

bool TGUIColour::operator!=(const TGUIColour& other)
{
    return *(const unsigned int*)this != *(const unsigned int*)&other;
}

TGUIColour& TGUIColour::operator*=(const TGUIColour& other)
{
    // fixed point: a channel of 255 times a channel of 255 gives 254
    m_ucAlpha = (other.m_ucAlpha * m_ucAlpha) >> 8;
    m_ucRed = (other.m_ucRed * m_ucRed) >> 8;
    m_ucGreen = (other.m_ucGreen * m_ucGreen) >> 8;
    m_ucBlue = (other.m_ucBlue * m_ucBlue) >> 8;
    return *this;
}

void TGUIColour::SetAlpha(float alpha)
{
    m_ucAlpha = (unsigned char)(alpha * 255.0f);
}

unsigned int TGUIColour::GetARGB() const
{
    return (m_ucAlpha << 24) | (m_ucRed << 16) | (m_ucGreen << 8) | m_ucBlue;
}

unsigned int TGUIColour::GetABGR() const
{
    return (m_ucAlpha << 24) | (m_ucBlue << 16) | (m_ucGreen << 8) | m_ucRed;
}

unsigned int TGUIColour::GetPlatformColour() const
{
    return (m_ucAlpha << 24) | (m_ucRed << 16) | (m_ucGreen << 8) | m_ucBlue;
}

void TGUIColour::Get(float& alpha, float& red, float& green, float& blue) const
{
    alpha = m_ucAlpha * (1.0f / 255.0f);
    red = m_ucRed * (1.0f / 255.0f);
    green = m_ucGreen * (1.0f / 255.0f);
    blue = m_ucBlue * (1.0f / 255.0f);
}

} // namespace Toshi
