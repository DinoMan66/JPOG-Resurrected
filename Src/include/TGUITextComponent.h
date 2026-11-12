// Toshi::TGUITextComponent (TGuiInterface.dll): a GUI component that draws text with a single element.
// Size 0x40: the TGUIComponent base (0x1C bytes) and one element at +0x1C.
#ifndef TGUITEXTCOMPONENT_H
#define TGUITEXTCOMPONENT_H
#include "TGUIAPI.h"
#include "TGUIComponent.h"
#include "TGUIElement.h"

namespace Toshi {

class TGUI_API TGUITextComponent : public TGUIComponent
{
public:
    TGUITextComponent();
    virtual ~TGUITextComponent();

    virtual TClass& GetClass() const;
    virtual TGUIComponent* Clone() const;
    virtual bool GetPreferredSize(PPropertyValue* value, int& width, int& height,
                                  short maxWidth, short maxHeight) const;
    virtual TGUIElement* GetElements();

    static TClass m_sClass;

protected:
    TGUITextComponent(const TGUITextComponent& other);

    virtual const TGUIComponentInfo* GetComponentInfo() const;
    virtual void Paint(TGUIDisplayContext* context, PPropertyValue* value, const TGUIRectangle& rect,
                       TGUIComponentCache* cache) const;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    static TGUIComponentInfo ms_component_info;

    TGUIElement m_oText;    // +0x1C
};

} // namespace Toshi
#endif
