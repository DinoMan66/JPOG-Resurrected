// Toshi::TGUIFormattedText (TGuiInterface.dll): a string already split into lines/segments by TGUIFont::BreakString,
// ready for TGUIDisplayContext::DrawFormattedText. Only the accessors are written so far.
#ifndef TGUIFORMATTEDTEXT_H
#define TGUIFORMATTEDTEXT_H
#include "TGUIAPI.h"
#include "TNodeList.h"

namespace Toshi {

class TGUI_API TGUIFormattedText
{
public:
    class Segment : public TNodeList<Segment>::TNode
    {
    };

    TGUIFormattedText(bool temporary);
    void SetTemporaryString(bool temporary);
    bool IsTemporaryString() const;
    TNodeList<Segment>& GetSegments();

private:
    TNodeList<Segment> m_oSegments;     // +0x00
    bool m_bTemporaryString;            // +0x10
};

} // namespace Toshi
#endif
