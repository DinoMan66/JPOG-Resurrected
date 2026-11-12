// Toshi::TGUIAudioContext (TGuiInterface.dll): abstract interface the GUI uses to play sounds.
// Slot 4 is pure virtual and has no exported name, so it stays an unnamed placeholder.
#ifndef TGUIAUDIOCONTEXT_H
#define TGUIAUDIOCONTEXT_H
#include "TGUIAPI.h"
#include "TObject.h"

namespace Toshi {

class TGUI_API TGUIAudioContext : public TObject
{
public:
    TGUIAudioContext();
    virtual ~TGUIAudioContext();

    virtual TClass& GetClass() const;
    virtual void vf4() = 0;

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

} // namespace Toshi
#endif
