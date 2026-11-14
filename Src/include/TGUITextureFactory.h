// Toshi::TGUITextureFactory (TGuiInterface.dll): abstract factory that creates the textures the GUI draws with.
// The 9 pure virtual slots (vtable slots 3-11) have no recovered name or signature yet;
// the renderer's implementation overrides them.
#ifndef TGUITEXTUREFACTORY_H
#define TGUITEXTUREFACTORY_H
#include "TGUIAPI.h"
#include "TObject.h"
#include "TPString.h"

namespace Toshi {

class TGUI_API TGUITextureFactory : public TObject
{
public:
    TGUITextureFactory();
    virtual ~TGUITextureFactory();

    virtual TClass& GetClass() const;
    virtual short vf3(const TPCString& name) = 0;   // looked up by TGUIInterface::FindTexture
    virtual void vf4() = 0;
    virtual void vf5() = 0;
    virtual void vf6() = 0;
    virtual void vf7() = 0;
    virtual void vf8() = 0;
    virtual void vf9() = 0;
    virtual void vf10() = 0;
    virtual void vf11() = 0;

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

} // namespace Toshi
#endif
