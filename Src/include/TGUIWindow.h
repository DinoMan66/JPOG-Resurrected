// Toshi::TGUIWindow (TGuiInterface.dll): a widget that owns a group of children and decides which of them
// has the focus. The default focus is the child that gets the focus whenever the window is shown or
// activated again. TGUIWindow is abstract (its Clone is still pure), so the dialogs derive from it.
// Size 0xA4.
#ifndef TGUIWINDOW_H
#define TGUIWINDOW_H
#include "TGUIAPI.h"
#include "TGUIWidget.h"
#include "TSortedArray.h"

class PPropertyValue;

namespace Toshi {

class TGUI_API TGUIWindow : public TGUIWidget
{
public:
    TGUIWindow();
    virtual ~TGUIWindow();

    virtual TClass& GetClass() const;                           // slot 0
    virtual bool Deserialise(const PProperties* properties);    // slot 3
    virtual bool Serialise(PProperties* properties);            // slot 4
    virtual bool AcceptsFocus() const { return m_pDefaultFocus != 0; }  // slot 16

protected:
    TGUIWindow(const TGUIWindow& other);
    virtual const TArray<TGUIPropertySpec*>* GetPropertyInfoSet() const { return ms_oPropertySet; }    // slot 11
    // slot 12
    virtual const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const
    {
        return ms_oPropertySetOrdered;
    }
    virtual void NotifyFocusGained(TGUIWidget* from, TGUIWidget* to);   // slot 22
    virtual void NotifyFocusLost(TGUIWidget* from, TGUIWidget* to);     // slot 21

public:
    TGUIWidget* GetDefaultFocus() const { return m_pDefaultFocus; }
    static const TGUIWidgetInfo* GetStaticWidgetInfo() { return ms_widget_info; }
    void SetDefaultFocus(TGUIWidget* widget);

    // set from the "default_focus" property, which names the child
    bool Val_default_focus_property(const PPropertyValue& value);
    void Set_default_focus_property(const PPropertyValue& value);
    PPropertyValue Get_default_focus_property() const;

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

protected:
    static TGUIWidgetInfo* ms_widget_info;
    static TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static TArray<TGUIPropertySpec*>* ms_oPropertySet;

private:
    // one entry of the focus map: where the focus goes from m_pWidget when it moves in m_eDirection
    struct FocusNeighbour
    {
        struct Comparator;      // orders the map by widget, then direction
        ~FocusNeighbour() {}

        TGUIWidget* m_pWidget;              // +0x0
        NeighbourDirection m_eDirection;    // +0x4
        TGUIWidget* m_pNeighbour;           // +0x8
    };

    TGUIWidget* m_pDefaultFocus;    // +0x8C
    TGUIWidget* m_pFocus;           // +0x90 the child that will get the focus next
    TSortedArray<FocusNeighbour, FocusNeighbour::Comparator> m_oFocusMap;    // +0x94
};

} // namespace Toshi
#endif
