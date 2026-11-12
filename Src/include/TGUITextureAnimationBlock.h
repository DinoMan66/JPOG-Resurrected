// Toshi::TGUITextureAnimationBlock (TGuiInterface.dll): reads and writes the texture animation block of a GUI
// property file. Size 0x14: the PPropertyBlock base (0x10 bytes) and the GUI interface the block loads into.
#ifndef TGUITEXTUREANIMATIONBLOCK_H
#define TGUITEXTUREANIMATIONBLOCK_H
#include "TGUIAPI.h"
#include "PPropertyBlock.h"

namespace Toshi {

class TGUIInterface;

class TGUI_API TGUITextureAnimationBlock : public PPropertyBlock
{
public:
    explicit TGUITextureAnimationBlock(TGUIInterface* gui);
    virtual ~TGUITextureAnimationBlock();

    virtual TClass& GetClass() const;
    virtual bool Load(PPropertyReader* reader);
    virtual bool Save(PPropertyWriter* writer);

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    TGUIInterface* m_pInterface;    // +0x10
};

} // namespace Toshi
#endif
