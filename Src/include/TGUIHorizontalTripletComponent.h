// Toshi::TGUIHorizontalTripletComponent (TGuiInterface.dll): a GUI component made of three elements side by
// side (left end, middle, right end). Size 0x88: the TGUIComponent base (0x1C bytes) and the elements at +0x1C.
#ifndef TGUIHORIZONTALTRIPLETCOMPONENT_H
#define TGUIHORIZONTALTRIPLETCOMPONENT_H
#include "TGUIAPI.h"
#include "TGUIComponent.h"
#include "TGUIElement.h"

namespace Toshi {

class TGUI_API TGUIHorizontalTripletComponent : public TGUIComponent
{
public:
    enum { ELEMENT_COUNT = 3 };

    TGUIHorizontalTripletComponent();
    virtual ~TGUIHorizontalTripletComponent();

    virtual TClass& GetClass() const;
    virtual TGUIComponent* Clone() const;
    virtual bool GetPreferredSize(PPropertyValue* value, int& width, int& height,
                                  short maxWidth, short maxHeight) const;
    virtual TGUIElement* GetElements();

    static TClass m_sClass;

protected:
    TGUIHorizontalTripletComponent(const TGUIHorizontalTripletComponent& other);

    virtual const TGUIComponentInfo* GetComponentInfo() const;
    virtual void Paint(TGUIDisplayContext* context, PPropertyValue* value, const TGUIRectangle& rect,
                       TGUIComponentCache* cache) const;

    void CalculateDimensions(PPropertyValue* value, int& height, int& leftWidth, int& middleWidth,
                             int& rightWidth) const;

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
