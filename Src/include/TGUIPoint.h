// Toshi::TGUIPoint - integer screen position (TGuiInterface.dll). operator= is the compiler-generated one.
#ifndef TGUIPOINT_H
#define TGUIPOINT_H
#include "TGUIAPI.h"

namespace Toshi {

class TGUI_API TGUIPoint
{
public:
    TGUIPoint();
    TGUIPoint(int x, int y);

    int GetX() const;
    int GetY() const;
    void SetX(int x);
    void SetY(int y);
    void Set(int x, int y);

    TGUIPoint& operator+=(const TGUIPoint& other);
    TGUIPoint& operator-=(const TGUIPoint& other);

private:
    int m_iX;   // +0x00
    int m_iY;   // +0x04
};

} // namespace Toshi
#endif
