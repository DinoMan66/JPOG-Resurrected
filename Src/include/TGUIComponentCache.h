// Toshi::TGUIComponentCache (TGuiInterface.dll): per-component cache of laid-out geometry; its first member is
// the cached bounding box. Only the box accessor is written so far.
#ifndef TGUICOMPONENTCACHE_H
#define TGUICOMPONENTCACHE_H
#include "TGUIAPI.h"
#include "TGUIRectangle.h"

namespace Toshi {

class TGUI_API TGUIComponentCache
{
public:
    const TGUIRectangle& GetBBox() const;

private:
    TGUIRectangle m_oBBox;      // +0x00
};

} // namespace Toshi
#endif
