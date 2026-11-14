// TGUIComponentCache accessor. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TGUIComponentCache.h"

namespace Toshi {

const TGUIRectangle& TGUIComponentCache::GetBBox() const
{
    return m_oBBox;
}

} // namespace Toshi
