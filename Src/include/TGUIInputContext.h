// Toshi::TGUIInputContext (TGuiInterface.dll): maps input events to GUI actions for one screen. Only SetScreen is written so far.
#ifndef TGUIINPUTCONTEXT_H
#define TGUIINPUTCONTEXT_H
#include "TGUIAPI.h"
#include "TObject.h"

namespace Toshi {

class TGUIScreen;

class TGUI_API TGUIInputContext : public TObject
{
public:
    void SetScreen(TGUIScreen* screen);

private:
    TGUIScreen* m_pScreen;      // +0x04
};

} // namespace Toshi
#endif
