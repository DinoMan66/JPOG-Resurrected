// Toshi::TGUIWidgetAction (TGuiInterface.dll): a command a widget can trigger (a button press, a menu entry).
// It carries the command and doodad ids, a label and an enabled flag, and throws an event to its listeners
// when the widget fires it. Only the accessors are written so far.
#ifndef TGUIWIDGETACTION_H
#define TGUIWIDGETACTION_H
#include "TGUIAPI.h"


namespace Toshi {

class TGUIWidget;
class TLString;

class TGUI_API TGUIWidgetAction
{
public:
    bool IsEnabled() const;
    void SetEnabled(bool enabled);
    int GetCommandID() const;
    int GetDoodadID() const;

private:
    unsigned char m_unk00[8];                           // +0x00
    unsigned char m_unk08[0xC];                         // +0x08 (a TGenericEmitter, not declared here yet)
    int m_iDoodadID;                                    // +0x14
    TLString* m_pLabel;                                 // +0x18
    int m_iCommandID;                                   // +0x1C
    bool m_bEnabled;                                    // +0x20
};

} // namespace Toshi
#endif
