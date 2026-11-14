// Toshi::TGUIFrameComponent (TGuiInterface.dll): a GUI component that draws a frame around its contents out of
// nine elements (corners, edges and centre). Size 0x160: the TGUIComponent base (0x1C bytes) and the elements at +0x1C.
#ifndef TGUIFRAMECOMPONENT_H
#define TGUIFRAMECOMPONENT_H
#include "TGUIAPI.h"
#include "TGUIComponent.h"
#include "TGUIElement.h"

namespace Toshi {

class TGUI_API TGUIFrameComponent : public TGUIComponent
{
public:
    enum { ELEMENT_COUNT = 9 };

    TGUIFrameComponent();
    virtual ~TGUIFrameComponent();

    virtual TClass& GetClass() const;
    virtual TGUIFrameComponent* Clone() const;
    virtual bool GetPreferredSize(PPropertyValue* value, int& width, int& height,
                                  short maxWidth, short maxHeight) const;
    virtual TGUIElement* GetElements();
    virtual void DestroyCache(void* cache) const;

    static TClass m_sClass;

protected:
    TGUIFrameComponent(const TGUIFrameComponent& other);

    virtual const TGUIComponentInfo* GetComponentInfo() const;
    virtual void Paint(TGUIDisplayContext* context, PPropertyValue* value, const TGUIRectangle& rect,
                       TGUIComponentCache* cache) const;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    static TGUIComponentInfo ms_component_info;

    TGUIElement m_aElements[ELEMENT_COUNT];     // +0x1C
};

} // namespace Toshi
#endif
