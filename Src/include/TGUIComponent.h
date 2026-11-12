// Toshi::TGUIComponent (TGuiInterface.dll): base class of the parts a GUI style is built from
// (frame, icon, text, horizontal and vertical triplet). A component sits in a style state's list.
// Vtable: [0] GetClass [1] Delete [2] destructor [3] Clone [4] Deserialise [5] Serialise
//         [6] GetPreferredSize [7] GetComponentInfo [8] GetElements [9] Paint
//         [10] NotifyElementsChanged [11] DestroyCache
#ifndef TGUICOMPONENT_H
#define TGUICOMPONENT_H
#include "TGUIAPI.h"
#include "TObject.h"
#include "TNodeList.h"
#include "TGUIMemory.h"

class PProperties;
class PPropertyValue;

namespace Toshi {

class TGUIComponentCache;
class TGUIComponentInfo;
class TGUIDisplayContext;
class TGUIElement;
class TGUIRectangle;
class TGUIStyle;

class TGUI_API TGUIComponent : public TObject, public TNodeList<TGUIComponent>::TNode
{
public:
    TGUIComponent();
    virtual ~TGUIComponent();

    virtual TClass& GetClass() const;                                                   // slot 0
    virtual TGUIComponent* Clone() const = 0;                                           // slot 3
    virtual bool Deserialise(const PProperties* properties, TGUIStyle* style);          // slot 4
    virtual bool Serialise(PProperties* properties, TGUIStyle* style);                  // slot 5
    virtual bool GetPreferredSize(PPropertyValue* value, int& width, int& height,
                                  short maxWidth, short maxHeight) const = 0;           // slot 6

protected:
    virtual const TGUIComponentInfo* GetComponentInfo() const = 0;                      // slot 7

public:
    virtual TGUIElement* GetElements() = 0;                                             // slot 8

protected:
    virtual void Paint(TGUIDisplayContext* context, PPropertyValue* value, const TGUIRectangle& rect,
                       TGUIComponentCache* cache) const = 0;                            // slot 9

public:
    virtual void NotifyElementsChanged();                                               // slot 10
    virtual void DestroyCache(void* cache) const;                                       // slot 11

    void GetMargins(int& left, int& right, int& top, int& bottom);
    void SetMargins(int left, int right, int top, int bottom);
    int GetMarginLeft() const { return m_cMarginLeft; }
    int GetMarginRight() const { return m_cMarginRight; }
    int GetMarginTop() const { return m_cMarginTop; }
    int GetMarginBottom() const { return m_cMarginBottom; }
    void SetMarginLeft(int margin);
    void SetMarginRight(int margin);
    void SetMarginTop(int margin);
    void SetMarginBottom(int margin);

    static TClass m_sClass;

    // Components live in the GUI's own memory pile (see TGUIMemory.h)
    static void* operator new(size_t size) { return TGUINew(size); }
    static void* operator new(size_t size, void* memory) { return memory; }
    static void operator delete(void* memory) { TGUIDelete(memory); }

protected:
    TGUIComponent(const TGUIComponent& other);
    void CopyElements(TGUIElement* destination, const TGUIElement* source, int count);

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    signed char m_cMarginLeft;          // +0x10
    signed char m_cMarginRight;         // +0x11
    signed char m_cMarginTop;           // +0x12
    signed char m_cMarginBottom;        // +0x13
    TGUIComponent* m_apChildren[2];     // +0x14 owned; cloned by the copy constructor, deleted by the destructor
};

} // namespace Toshi
#endif
