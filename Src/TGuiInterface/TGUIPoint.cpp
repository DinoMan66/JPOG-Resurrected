// Z:\Toshi\Source\TGUI\TGUIPoint - TGUIPoint (the original has no file of its own for it in the strings).
#define TGUIINTERFACE_EXPORTS
#include "TGUIPoint.h"

namespace Toshi {

TGUIPoint::TGUIPoint()
{
}

TGUIPoint::TGUIPoint(int x, int y)
{
    m_iX = x;
    m_iY = y;
}

int TGUIPoint::GetX() const
{
    return m_iX;
}

int TGUIPoint::GetY() const
{
    return m_iY;
}

void TGUIPoint::SetX(int x)
{
    m_iX = x;
}

void TGUIPoint::SetY(int y)
{
    m_iY = y;
}

void TGUIPoint::Set(int x, int y)
{
    m_iX = x;
    m_iY = y;
}

TGUIPoint& TGUIPoint::operator+=(const TGUIPoint& other)
{
    m_iX += other.m_iX;
    m_iY += other.m_iY;
    return *this;
}

TGUIPoint& TGUIPoint::operator-=(const TGUIPoint& other)
{
    m_iX -= other.m_iX;
    m_iY -= other.m_iY;
    return *this;
}

} // namespace Toshi
