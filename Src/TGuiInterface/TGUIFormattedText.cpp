// TGUIFormattedText accessors. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TGUIFormattedText.h"

namespace Toshi {

TGUIFormattedText::TGUIFormattedText(bool temporary)
{
    m_bTemporaryString = temporary;
}

void TGUIFormattedText::SetTemporaryString(bool temporary)
{
    m_bTemporaryString = temporary;
}

bool TGUIFormattedText::IsTemporaryString() const
{
    return m_bTemporaryString;
}

TNodeList<TGUIFormattedText::Segment>& TGUIFormattedText::GetSegments()
{
    return m_oSegments;
}

} // namespace Toshi
