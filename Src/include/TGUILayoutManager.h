// Toshi::TGUILayoutManager (TGuiInterface.dll): arranges the children of a widget. TGUILayoutManager is
// abstract; PGUICore derives the disc, overlay, ... layouts from it. A layout manager is owned by the
// widget it lays out (TGUIWidget::SetLayoutManager).
// Vtable after TGUIDeserialisable: [11] GetPropertyInfoSet [12] GetPropertyInfoOrderedSet [13] Clone (pure)
//         [14] DoPack (pure) [15] DoLayout (pure); the parameters of the last two are still unknown.
// Size 0xC.
#ifndef TGUILAYOUTMANAGER_H
#define TGUILAYOUTMANAGER_H
#include "TGUIAPI.h"
#include "TGUIDeserialisable.h"

namespace Toshi {

class TGUIInterface;
class TGUILayoutInfo;

class TGUI_API TGUILayoutManager : public TGUIDeserialisable
{
public:
    virtual ~TGUILayoutManager();

    virtual TClass& GetClass() const;                                       // slot 0
    virtual bool Deserialise(const PProperties* properties);                // slot 3
    virtual bool Serialise(PProperties* properties);                        // slot 4
    virtual void SetInterface(TGUIInterface* gui) { m_pInterface = gui; }   // slot 9
    virtual TGUIInterface* GetInterface() const { return m_pInterface; }    // slot 10

protected:
    virtual const TArray<TGUIPropertySpec*>* GetPropertyInfoSet() const { return ms_oPropertySet; }    // slot 11
    // slot 12
    virtual const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const
    {
        return ms_oPropertySetOrdered;
    }

public:
    virtual TGUILayoutManager* Clone() const = 0;                           // slot 13
    virtual void vf14() = 0;                                                // DoPack
    virtual void vf15() = 0;                                                // DoLayout

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
    TGUILayoutInfo* m_pLayoutInfo;      // +0x8
};

} // namespace Toshi
#endif
