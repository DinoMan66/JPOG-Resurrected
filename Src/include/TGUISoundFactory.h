// Toshi::TGUISoundFactory (TGuiInterface.dll): abstract factory that creates the sounds the GUI plays.
// The 3 pure virtual slots (vtable slots 3-5) have no recovered name or signature yet;
// the renderer's implementation overrides them.
#ifndef TGUISOUNDFACTORY_H
#define TGUISOUNDFACTORY_H
#include "TGUIAPI.h"
#include "TObject.h"

namespace Toshi {

class TGUI_API TGUISoundFactory : public TObject
{
public:
    TGUISoundFactory();
    virtual ~TGUISoundFactory();

    virtual TClass& GetClass() const;
    virtual void vf3() = 0;
    virtual void vf4() = 0;
    virtual void vf5() = 0;

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

} // namespace Toshi
#endif
