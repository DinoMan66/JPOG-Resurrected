// PGUIButton (PGUICore.dll): the base of the clickable widgets. It adds a "pressed" state bit and an emitter
// (at +0x8C) that tells listeners when the button was pressed. Only the accessors are written so far.
#ifndef PGUIBUTTON_H
#define PGUIBUTTON_H
#include "PGUIAPI.h"
#include "TGUIWidget.h"

class PGUI_API PGUIButton : public Toshi::TGUIWidget
{
public:
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    // Bit of the widget state, added to the ones TGUIWidget defines
    enum
    {
        STATE_PRESSED = 0x20
    };

    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual bool AcceptsFocus() const;                                  // slot 16

    bool IsPressed() const;
    void SetPressed(bool pressed);

protected:
    PGUIButton(const PGUIButton& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    // PGUIButton is abstract, so its factory functions create nothing
    static Toshi::TObject* __stdcall CreateObject();
    static Toshi::TObject* __stdcall CreateObjectInPlace(void* memory);

    unsigned char m_unk8C[0xC];     // +0x8C (a TGenericEmitter, not declared here yet)

    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
