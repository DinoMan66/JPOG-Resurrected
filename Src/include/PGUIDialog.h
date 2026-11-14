// PGUIDialog (PGUICore.dll): a window that is shown on top of the screen and holds other widgets.
// Only the accessors are written so far.
#ifndef PGUIDIALOG_H
#define PGUIDIALOG_H
#include "PGUIAPI.h"
#include "TGUIWindow.h"

class PGUI_API PGUIDialog : public Toshi::TGUIWindow
{
public:
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual PGUIDialog* Clone() const;                                  // slot 13
    virtual void Pack();                                                // slot 33
    virtual bool AllowsChildren() const;                                // slot 15

protected:
    PGUIDialog(const PGUIDialog& other);
    virtual bool OnButtonPress(Toshi::TInputInterface::InputEvent* event, int doodad);  // slot 24
    virtual bool OnPointerMove(int x, int y);                           // slot 29
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    bool m_bUnkA4;                          // +0xA4 set while a button is held (pointer drag)
    unsigned char m_unkA5[3];               // +0xA5
    int m_iPressPointerX;                   // +0xA8 pointer position when the button was pressed
    int m_iPressPointerY;                   // +0xAC

    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
