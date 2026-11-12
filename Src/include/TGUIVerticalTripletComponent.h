// Toshi::TGUIVerticalTripletComponent (TGuiInterface.dll): a GUI component made of three elements stacked
// vertically (top, middle, bottom). Size 0x88: the TGUIComponent base (0x1C bytes) and the elements at +0x1C.
#ifndef TGUIVERTICALTRIPLETCOMPONENT_H
#define TGUIVERTICALTRIPLETCOMPONENT_H
#include "TGUIAPI.h"
#include "TGUIComponent.h"
#include "TGUIElement.h"

namespace Toshi {

class TGUI_API TGUIVerticalTripletComponent : public TGUIComponent
{
public:
    enum { ELEMENT_COUNT = 3 };

    TGUIVerticalTripletComponent();
    virtual ~TGUIVerticalTripletComponent();

    virtual TClass& GetClass() const;
    virtual TGUIComponent* Clone() const;
    virtual bool GetPreferredSize(PPropertyValue* value, int& width, int& height,
                                  short maxWidth, short maxHeight) const;
    virtual TGUIElement* GetElements();

    static TClass m_sClass;

protected:
    TGUIVerticalTripletComponent(const TGUIVerticalTripletComponent& other);

    virtual const TGUIComponentInfo* GetComponentInfo() const;
    virtual void Paint(TGUIDisplayContext* context, PPropertyValue* value, const TGUIRectangle& rect,
                       TGUIComponentCache* cache) const;

    // slot 12: the sizes of the three parts; the width is the widest of them
    virtual void CalculateDimensions(PPropertyValue* value, int& width, int& topHeight, int& middleHeight,
                                     int& bottomHeight) const;

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
