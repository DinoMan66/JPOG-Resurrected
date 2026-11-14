// Toshi::TGUILayoutManager (TGuiInterface.dll): arranges the children of a widget. TGUILayoutManager is
// abstract; PGUICore derives the disc, overlay, ... layouts from it. A layout manager is owned by the
// widget it lays out (TGUIWidget::SetLayoutManager).
// Vtable after TGUIDeserialisable: [11] GetPropertyInfoSet [12] GetPropertyInfoOrderedSet [13] Clone (pure)
//         [14] DoPack (pure) [15] DoLayout (pure); the names and parameter types come from the exports of
//         PGUICore's layouts, what the two int references mean is not known yet.
// Size 0xC.
#ifndef TGUILAYOUTMANAGER_H
#define TGUILAYOUTMANAGER_H
#include "TGUIAPI.h"
#include "TGUIDeserialisable.h"

namespace Toshi {

class TGUIInterface;
class TGUILayoutInfo;
class TGUIWidget;

class TGUI_API TGUILayoutManager : public TGUIDeserialisable
{
public:
    TGUILayoutManager();
    virtual ~TGUILayoutManager();

    virtual TClass& GetClass() const;                                       // slot 0
    virtual bool Deserialise(const PProperties* properties);                // slot 3
    virtual bool Serialise(PProperties* properties);                        // slot 4
    virtual void SetInterface(TGUIInterface* gui) { m_pInterface = gui; }   // slot 9
    virtual TGUIInterface* GetInterface() const { return m_pInterface; }    // slot 10

protected:
    TGUILayoutManager(const TGUILayoutManager& other);

    virtual const TArray<TGUIPropertySpec*>* GetPropertyInfoSet() const { return ms_oPropertySet; }    // slot 11
    // slot 12
    virtual const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const
    {
        return ms_oPropertySetOrdered;
    }

public:
    virtual TGUILayoutManager* Clone() const = 0;                           // slot 13
    virtual void DoPack(TGUIWidget* widget) const = 0;                      // slot 14
    virtual void DoLayout(TGUIWidget* widget, int& arg1, int& arg2) const = 0;     // slot 15

    // How a layout aligns a child inside its slot; the enumerator values are not known yet
    enum Alignment
    {
    };

    const TGUILayoutInfo* GetLayoutInfo() const { return m_pLayoutInfo; }

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

protected:
    static TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static TArray<TGUIPropertySpec*>* ms_oPropertySet;

private:
    TGUIInterface* m_pInterface;        // +0x4

protected:
    // Each derived class's constructor points this at its own static layout info
    TGUILayoutInfo* m_pLayoutInfo;      // +0x8
};

} // namespace Toshi
#endif
