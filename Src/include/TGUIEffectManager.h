// Toshi::TGUIEffectManager (TGuiInterface.dll): placeholder for the GUI effect manager. It has no data and no
// functions besides the class boilerplate in this build of the DLL.
#ifndef TGUIEFFECTMANAGER_H
#define TGUIEFFECTMANAGER_H
#include "TGUIAPI.h"
#include "TObject.h"

namespace Toshi {

class TGUI_API TGUIEffectManager : public TObject
{
public:
    TGUIEffectManager();
    virtual ~TGUIEffectManager();

    virtual TClass& GetClass() const;

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

} // namespace Toshi
#endif
