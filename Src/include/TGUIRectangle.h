// Toshi::TGUIRectangle - integer screen rectangle (left, top, width, height) used throughout the GUI.
// TGuiInterface.dll exports no functions for it, so the accessors are inline and their names are our own.
#ifndef TGUIRECTANGLE_H
#define TGUIRECTANGLE_H

namespace Toshi {

class TGUIRectangle
{
public:
    TGUIRectangle()
        : m_iX(0)
        , m_iY(0)
        , m_iWidth(0)
        , m_iHeight(0)
    {
    }

    TGUIRectangle(int x, int y, int width, int height)
        : m_iX(x)
        , m_iY(y)
        , m_iWidth(width)
        , m_iHeight(height)
    {
    }

    int GetX() const { return m_iX; }
    int GetY() const { return m_iY; }
    int GetWidth() const { return m_iWidth; }
    int GetHeight() const { return m_iHeight; }
    int GetRight() const { return m_iWidth + m_iX; }
    int GetBottom() const { return m_iHeight + m_iY; }

    int m_iX;       // +0x00
    int m_iY;       // +0x04
    int m_iWidth;   // +0x08
    int m_iHeight;  // +0x0C
};

} // namespace Toshi
#endif
