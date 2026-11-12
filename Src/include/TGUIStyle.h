// Toshi::TGUIStyle (TGuiInterface.dll): a named "look" for a kind of widget. A style belongs to one widget
// class (TGUIWidgetInfo), keeps the four margins widgets of that style use and one TGUIStyleRootComponent
// per state the style defines. Styles are loaded from the GUI property files and kept in the GUI
// interface's list of style instances.
// Size 0x44.
#ifndef TGUISTYLE_H
#define TGUISTYLE_H
#include "TGUIAPI.h"
#include "TGUIDeserialisable.h"
#include "TGUIMemory.h"
#include "TGUIStyleRootComponent.h"
#include "TNodeList.h"
#include "TPString.h"

namespace Toshi {

class TGUIInterface;
class TGUIWidgetInfo;

class TGUI_API TGUIStyle : public TGUIDeserialisable, public TNodeList<TGUIStyle>::TNode
{
public:
    TGUIStyle();
    virtual ~TGUIStyle();

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
    virtual TGUIStyle* Clone() const;                                       // slot 13

    int GetParameterCount() const { return m_ucParameterCount; }
    const TGUIWidgetInfo* GetWidgetInfo() const { return m_pWidgetInfo; }
    const TPCString& GetName() const { return m_oName; }
    void SetName(TPCString& name) { m_oName = name; }
    TGUIStyleRootComponent& GetRootComponent(int index) { return m_pRootComponents[index]; }

    // margins, in pixels
    void GetMargins(int& left, int& right, int& top, int& bottom) const
    {
        left = m_sMarginLeft;
        right = m_sMarginRight;
        top = m_sMarginTop;
        bottom = m_sMarginBottom;
    }
    int GetMarginRight() const { return m_sMarginRight; }
    int GetMarginLeft() const { return m_sMarginLeft; }
    int GetMarginBottom() const { return m_sMarginBottom; }
    int GetMarginTop() const { return m_sMarginTop; }
    void SetMargins(int left, int right, int top, int bottom)
    {
        m_sMarginLeft = left;
        m_sMarginRight = right;
        m_sMarginTop = top;
        m_sMarginBottom = bottom;
    }
    void SetMarginRight(int margin) { m_sMarginRight = margin; }
    void SetMarginLeft(int margin) { m_sMarginLeft = margin; }
    void SetMarginBottom(int margin) { m_sMarginBottom = margin; }
    void SetMarginTop(int margin) { m_sMarginTop = margin; }

    static void* operator new(size_t size) { return TGUINew(size); }
    static void* operator new(size_t size, void* memory) { return memory; }
    static void* operator new[](size_t size) { return TGUINew(size); }
    static void operator delete(void* memory) { TGUIDelete(memory); }
    static void operator delete[](void* memory) { TGUIDelete(memory); }

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
    TGUIInterface* m_pInterface;                    // +0x10
    TGUIStyleRootComponent* m_pRootComponents;      // +0x14, one per state
    const TGUIWidgetInfo* m_pWidgetInfo;            // +0x18
    TPCString m_oName;                              // +0x1C
    unsigned char m_ucParameterCount;               // +0x20
    /* 0x24 */ int m_unk24;
    /* 0x28 */ int m_unk28;
    /* 0x2C */ int m_unk2C;
    /* 0x30 */ int m_unk30;
    /* 0x34 */ int m_unk34;
    /* 0x38 */ int m_unk38;
    short m_sMarginTop;                             // +0x3C
    short m_sMarginBottom;                          // +0x3E
    short m_sMarginLeft;                            // +0x40
    short m_sMarginRight;                           // +0x42
};

} // namespace Toshi
#endif
