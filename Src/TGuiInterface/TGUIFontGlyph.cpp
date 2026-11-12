// Z:\Toshi\Source\TGUI - TGUIFontGlyph. The original file name is not in the binary's strings.
// The constructors, the destructor, Deserialise and Serialise are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIFontGlyph.h"
#include "TNewDelete.h"

namespace Toshi {

TGUITextureSection* TGUIFontGlyph::Clone() const
{
    return new TGUIFontGlyph(*this);
}

} // namespace Toshi
