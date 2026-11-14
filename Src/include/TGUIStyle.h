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
#include "TGUIPairNode.h"
#include "TGUIStyleParameterInfo.h"
#include "TGUIStyleRootComponent.h"
#include "TNodeList.h"
#include "PPropertyValue.h"
#include "TPString.h"

namespace Toshi {

class TGUIInterface;
class TGUIWidgetInfo;
class TGUIWidget;

class TGUI_API TGUIStyle : public TGUIDeserialisable, public TNodeList<TGUIStyle>::TNode
{
public:
    TGUIStyle();
    TGUIStyle(const TGUIStyle& other);
    virtual ~TGUIStyle();

    virtual TClass& GetClass() const;                                       // slot 0
    virtual bool Deserialise(const PProperties* properties);                // slot 3
    virtual bool Serialise(PProperties* properties);                        // slot 4
    virtual void SetInterface(TGUIInterface* gui) { m_pInterface = gui; }   // slot 9
    virtual TGUIInterface* GetInterface() const { return m_pInterface; }    // slot 10

protected:
    TGUIPairNode<TPCString, PPropertyValue>* FindFixedWidgetPropertyPair(const TPCString& name) const;

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
    bool IsWidgetStyle(const TPCString& widgetName) const;
    PPropertyValue GetFixedWidgetProperty(const TPCString& name) const;
    void ReleaseFixedWidgetProperty(const TPCString& name);
    void ApplyFixedWidgetProperties(TGUIWidget* widget);
    bool IsWidgetPropertyFixed(const TPCString& name) const;
    void SetName(TPCString& name) { m_oName = name; }
    bool Val_name_property() const;
    PPropertyValue Get_name_property() const;
    void Set_name_property(const PPropertyValue& value);
    bool Val_margintop_property(const PPropertyValue& value);
    bool Val_marginbottom_property(const PPropertyValue& value);
    bool Val_marginleft_property(const PPropertyValue& value);
    bool Val_marginright_property(const PPropertyValue& value);
    PPropertyValue Get_margintop_property() const;
    void Set_margintop_property(const PPropertyValue& value);
    PPropertyValue Get_marginbottom_property() const;
    void Set_marginbottom_property(const PPropertyValue& value);
    PPropertyValue Get_marginleft_property() const;
    void Set_marginleft_property(const PPropertyValue& value);
    PPropertyValue Get_marginright_property() const;
    void Set_marginright_property(const PPropertyValue& value);
    bool IsCompatibleWith(TGUIWidget* widget);
    bool IsCompatibleWith(TGUIStyle* style);
    const TGUIStyleParameterInfo* GetParameterInfo(int index) const;
    const TGUIStyleParameterInfo* GetParameterInfo(const TPCString& name) const;
    int FindParameter(const TPCString& name) const;
    TGUIStyleState* GetState(const TPCString& component, unsigned int stateBits) const;
    TGUIStyleState* GetState(int component, unsigned int stateBits) const;
    TGUIStyleRootComponent& GetRootComponent(int index) { return m_pRootComponents[index]; }

    // margins, in pixels
    void GetMargins(int& left, int& right, int& top, int& bottom)
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
    TGUIStyleParameterInfo* m_pParameterInfos;      // +0x24, m_ucParameterCount entries
    TNodeList<TGUIPairNode<TPCString, PPropertyValue> > m_oFixedProperties;     // +0x28, 0x10 bytes
    /* 0x38 */ int m_unk38;
    short m_sMarginTop;                             // +0x3C
    short m_sMarginBottom;                          // +0x3E
    short m_sMarginLeft;                            // +0x40
    short m_sMarginRight;                           // +0x42
};

} // namespace Toshi
#endif
