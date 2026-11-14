// Toshi::TGUIWidget (TGuiInterface.dll): base class of everything the GUI shows and the player interacts with
// (windows, buttons, labels, ...). A widget is loaded from a property list, sits in its parent's list of
// children, has a position, a size, a name and a set of state flags, and receives input events.
// Vtable: [0] GetClass [1] Delete [2] destructor [3] Deserialise [4] Serialise [5] GetPropertyCount
//         [6] FindPropertyInfo [7] GetPropertyInfo [8] ValidatePropertyInfo [9] SetInterface [10] GetInterface
//         [11] GetPropertyInfoSet [12] GetPropertyInfoOrderedSet [13] Clone (pure) [14] ManagesChildren
//         [15] AllowsChildren [16] AcceptsFocus [17] AllowsFocus [18] NotifyDescendantAddition
//         [19] NotifyDescendantRemoval [20] NotifyDescendantRemoved [21] NotifyFocusLost [22] NotifyFocusGained
//         [23] NotifySlaveStateChanged [24] OnButtonPress [25] OnButtonRepeat [26] OnButtonRelease
//         [27] OnButtonHit [28] OnAxisMove [29] OnPointerMove [30] OnPointerEnter [31] OnPointerExit
//         [32] OnPaint [33] Pack [34] (pure) [35] DeserialiseState [36] DeserialiseParameters
//         [37] DeserialiseChildren [38] SerialiseState [39] SerialiseParameters [40] SerialiseChildren
//         [41] NotifyParentChange
// Only the members the reconstructed accessors use are named; the rest are placeholders with their offset.
#ifndef TGUIWIDGET_H
#define TGUIWIDGET_H
#include "TGUIAPI.h"
#include "TGUIDeserialisable.h"
#include "TGUIMemory.h"
#include "TNodeList.h"
#include "TPString.h"
#include "TInputInterface.h"

class PProperties;
class PPropertyValue;

namespace Toshi {

class TGUIDisplayContext;
class TGUIInterface;
class TGUIPropertySpec;
class TGUILayoutManager;
class TGUIRectangle;
class TGUIStyle;
class TGUIStyleParameterInfo;
class TGUITextureSection;
class TGUIWidgetInfo;
class TLString;
class TGUIScreen;
class TGUIWindow;

class TGUI_API TGUIWidget : public TGUIDeserialisable, public TNodeList<TGUIWidget>::TNode
{
public:
    // The names are placeholders: the values are the ones the binary stores and compares.
    enum PlaceMode
    {
        PLACE_MODE_0 = 0,
        PLACE_MODE_1 = 1    // the default
    };

    enum SizeMode
    {
        SIZE_MODE_0 = 0,
        SIZE_MODE_1 = 1,
        SIZE_MODE_2 = 2     // the default
    };

    // Where a scroll bar or slider sits and which way it runs; PGUICore's widgets use them as parameters.
    // The enumerator values are not known yet.
    enum Placement
    {
    };

    enum Orientation
    {
    };

    // The four directions focus can move in; the enumerator names are placeholders
    enum NeighbourDirection
    {
        NEIGHBOUR_DIRECTION_0,
        NEIGHBOUR_DIRECTION_1,
        NEIGHBOUR_DIRECTION_2,
        NEIGHBOUR_DIRECTION_3,
        NEIGHBOUR_DIRECTION_NONE = 6    // GetDirectionEnum finds no such name
    };

    // The bits of m_uiState
    enum
    {
        STATE_ENABLED = 0x01,
        STATE_FOCUSED = 0x02,
        STATE_VISIBLE = 0x04,
        STATE_ROLLOVER = 0x08,
        STATE_SELECTED = 0x10
    };

    TGUIWidget();
    virtual ~TGUIWidget();

    virtual TClass& GetClass() const;                                                   // slot 0
    virtual bool Deserialise(const PProperties* properties);                            // slot 3
    virtual bool Serialise(PProperties* properties);                                    // slot 4
    virtual int GetPropertyCount() const;                                               // slot 5
    virtual const TGUIPropertySpec* FindPropertyInfo(const TPCString& name) const;      // slot 6
    virtual const TGUIPropertySpec* GetPropertyInfo(int index) const;                   // slot 7
    virtual bool ValidatePropertyInfo(const TGUIPropertySpec* info) const;              // slot 8
    virtual void SetInterface(TGUIInterface* gui);                                      // slot 9
    virtual TGUIInterface* GetInterface() const { return m_pInterface; }                // slot 10

protected:
    virtual const TArray<TGUIPropertySpec*>* GetPropertyInfoSet() const { return ms_oPropertySet; }    // slot 11
    // slot 12
    virtual const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const
    {
        return ms_oPropertySetOrdered;
    }

public:
    virtual TGUIWidget* Clone() const = 0;                                              // slot 13
    virtual bool ManagesChildren() const { return false; }                              // slot 14
    virtual bool AllowsChildren() const { return false; }                               // slot 15
    virtual bool AcceptsFocus() const { return false; }                                 // slot 16
    virtual TGUIWidget* AllowsFocus(TGUIWidget* from);                                  // slot 17
    virtual void NotifyDescendantAddition(TGUIWidget* descendant);                      // slot 18
    virtual void NotifyDescendantRemoval(TGUIWidget* descendant);                       // slot 19
    virtual void NotifyDescendantRemoved(TGUIWidget* ancestor, TGUIWidget* descendant); // slot 20
    virtual void NotifyFocusLost(TGUIWidget* from, TGUIWidget* to);                     // slot 21
    virtual void NotifyFocusGained(TGUIWidget* from, TGUIWidget* to);                   // slot 22
    virtual void NotifySlaveStateChanged(TGUIWidget* slave, unsigned int mask) {}       // slot 23
    virtual bool OnButtonPress(TInputInterface::InputEvent* event, int doodad);         // slot 24
    virtual bool OnButtonRepeat(TInputInterface::InputEvent* event, int doodad);        // slot 25
    virtual bool OnButtonRelease(TInputInterface::InputEvent* event, int doodad);       // slot 26
    virtual bool OnButtonHit(TInputInterface::InputEvent* event, int doodad);           // slot 27
    virtual bool OnAxisMove(TInputInterface::InputEvent* event, int doodad);            // slot 28
    virtual bool OnPointerMove(int x, int y);                                          // slot 29
    virtual bool OnPointerEnter();                                                      // slot 30
    virtual bool OnPointerExit();                                                       // slot 31
    virtual bool OnPaint(TGUIDisplayContext* context);                                  // slot 32
    virtual void Pack() {}                                                              // slot 33

    // state flags
    bool IsEnabled() const { return (m_uiState & STATE_ENABLED) != 0; }
    bool IsFocused() const { return (m_uiState & STATE_FOCUSED) != 0; }
    bool IsVisible() const { return (m_uiState & STATE_VISIBLE) != 0; }
    bool IsRollover() const { return (m_uiState & STATE_ROLLOVER) != 0; }
    bool IsSelected() const { return (m_uiState & STATE_SELECTED) != 0; }
    bool IsState(unsigned int mask, unsigned int value) const { return (m_uiState & mask) == value; }
    bool IsState(unsigned int mask) const { return (m_uiState & mask) != 0; }
    // Applies value to the state bits selected by mask and tells the widget's observers
    void SetState(unsigned int mask, bool on) { SetState(mask, on == true ? mask : 0); }
    void SetSelected(bool on) { SetState(STATE_SELECTED, on); }
    void SetRollover(bool on) { SetState(STATE_ROLLOVER, on); }
    void SetFocused(bool on) { SetState(STATE_FOCUSED, on); }
    void SetEnabled(bool on) { SetState(STATE_ENABLED, on); }
    void SetVisible(bool on) { SetState(STATE_VISIBLE, on); }

    // layout
    bool IsLayoutValid() const { return m_bLayoutValid; }
    void SetLayoutValid(bool valid) { m_bLayoutValid = valid; }
    TGUIWidget* GetChildAtPoint(int x, int y, unsigned int flags, unsigned int mask);
    void SetPaintChildrenFirst(bool first) { m_bPaintChildrenFirst = first; }
    bool DoesPaintChildrenFirst() const { return m_bPaintChildrenFirst; }
    void SetValidated(bool validated) { m_bValidated = validated; }
    bool IsValidated() const { return m_bValidated; }
    void SetAnimSync(float sync) { m_fAnimSync = sync; }
    float GetAnimSync() const { return m_fAnimSync; }

    // tree
    const TNodeList<TGUIWidget>& GetChildren() const { return m_oChildren; }
    int GetChildCount() const { return m_oChildren.Count(); }
    TGUIWidget* GetParentWidget() const { return m_pParent; }

    TGUIStyle* GetStyle() const { return m_pStyle; }
    TGUILayoutManager* GetLayoutManager() const { return m_pLayoutManager; }
    const TGUIWidgetInfo* GetWidgetInfo() const { return m_pWidgetInfo; }
    void SetLayoutManager(TGUILayoutManager* manager);

    // name, position and size
    const TPCString& GetName() const { return m_oName; }
    void SetName(const TPCString& name) { m_oName = name; }
    PlaceMode GetPlaceMode() const { return m_ePlaceMode; }
    SizeMode GetSizeModeVert() const { return m_eSizeModeVert; }
    SizeMode GetSizeModeHoriz() const { return m_eSizeModeHoriz; }
    void GetBBox(TGUIRectangle& box) const;
    int GetHeight() const { return m_sHeight; }
    int GetWidth() const { return m_sWidth; }
    int GetYPos() const { return m_sY; }
    int GetXPos() const { return m_sX; }
    void GetSize(int& width, int& height) const
    {
        width = m_sWidth;
        height = m_sHeight;
    }
    void GetPosition(int& x, int& y) const
    {
        x = m_sX;
        y = m_sY;
    }
    void SetPlaceMode(PlaceMode mode) { m_ePlaceMode = mode; }
    void SetSizeMode(SizeMode horizontal, SizeMode vertical)
    {
        m_eSizeModeHoriz = horizontal;
        m_eSizeModeVert = vertical;
    }
    void SetStyle(TGUIStyle* style);
    void Create(TGUIInterface* gui, TGUIStyle* style, const TPCString& name);
    void SetFixedSize(int width, int height);
    void AddWidget(TGUIWidget* widget, bool front);
    void RemoveWidget(TGUIWidget* widget);
    void SetFixedHeight(int height);
    void SetFixedWidth(int width);
    void SetHeight(int height);
    void SetWidth(int width);
    bool CanResizeHoriz() const;
    bool CanResizeVert() const;
    bool CanMove() const;
    TGUIWidget* FindChildManager();
    TGUIWidget* FindIndexedChild(int index) const;
    bool CanFocus();
    void TransformDeviceToWidget(int x, int y, int& widgetX, int& widgetY) const;
    void TransformWidgetToDevice(int x, int y, int& deviceX, int& deviceY) const;
    void InvalidateComponentCache(bool recursive);
    void SetParameter(int index, const TLString& value);
    void SetParameter(int index, TGUITextureSection* value);
    PPropertyValue GetParameter(int index) const;
    bool Val_style_parameter(const PPropertyValue& value, TGUIStyleParameterInfo* info);
    PPropertyValue Get_style_parameter(TGUIStyleParameterInfo* info) const;
    void Set_state_property(const TPCString& name, bool set);
    void Set_state_property(int index, bool set);
    bool Get_state_property(int index);
    bool Get_state_property(const TPCString& name);
    void GetMargins(int& left, int& right, int& top, int& bottom);
    void GetInteriorSize(int& width, int& height) const;
    bool IsDescendantOf(const TGUIWidget* ancestor) const;
    bool IsAncestorOf(const TGUIWidget* descendant) const;
    TGUIWindow* GetWindow();
    TGUIScreen* GetScreen();
    void RequestFocus();
    void SetState(unsigned int mask, unsigned int value);
    void SetSize(int width, int height);
    void SetSizeModeVert(SizeMode mode) { m_eSizeModeVert = mode; }
    void SetSizeModeHoriz(SizeMode mode) { m_eSizeModeHoriz = mode; }
    void SetYPos(int y) { SetPosition(m_sX, y); }
    void SetXPos(int x) { SetPosition(x, m_sY); }
    void SetPosition(int x, int y);
    void SetPositionCenter();
    bool HitTest(int x, int y, int& localX, int& localY);

    // interior size: the widget's size without the margins of its style
    TGUIWidget* FindNamedChild(const TPCString& name) const;

    int GetInteriorWidth() const;
    int GetInteriorHeight() const;

    // position among the siblings (the front widget is painted last)
    void OrderPosition(int position);
    void OrderBackward();
    void OrderForward();
    void OrderToBack();
    void OrderToFront();
    void OrderChildSetPosition(TGUIWidget* child, int position);
    void OrderChildMovePosition(TGUIWidget* child, int offset);

    static const TGUIWidgetInfo* GetStaticWidgetInfo() { return ms_widget_info; }
    static NeighbourDirection GetDirectionEnum(const TPCString& name);
    static const TPCString& GetDirectionName(NeighbourDirection direction) { return ms_paDirectionName[direction]; }

    // property accessors: the GUI property files set these through the widget's property specs
    bool Val_animsync_property(const PPropertyValue& value);
    PPropertyValue Get_animsync_property() const;
    void Set_animsync_property(const PPropertyValue& value);
    PPropertyValue Get_placemode_property() const;
    void Set_placemode_property(const PPropertyValue& value);
    PPropertyValue Get_sizemode_vert_property() const;
    void Set_sizemode_vert_property(const PPropertyValue& value);
    PPropertyValue Get_sizemode_horiz_property() const;
    void Set_sizemode_horiz_property(const PPropertyValue& value);
    PPropertyValue Get_height_property() const;
    PPropertyValue Get_width_property() const;
    PPropertyValue Get_ypos_property() const;
    void Set_ypos_property(const PPropertyValue& value);
    PPropertyValue Get_xpos_property() const;
    void Set_xpos_property(const PPropertyValue& value);
    bool Val_sizemode_horiz_property(const PPropertyValue& value);
    bool Val_sizemode_vert_property(const PPropertyValue& value);
    bool Val_placemode_property(const PPropertyValue& value);
    bool Val_xpos_property(const PPropertyValue& value);
    bool Val_ypos_property(const PPropertyValue& value);
    bool Val_width_property(const PPropertyValue& value);
    bool Val_height_property(const PPropertyValue& value);
    void Set_height_property(const PPropertyValue& value);
    void Set_width_property(const PPropertyValue& value);
    bool Val_name_property(const PPropertyValue& value);
    PPropertyValue Get_name_property() const;
    void Set_name_property(const PPropertyValue& value);

    static void* operator new(size_t size) { return TGUINew(size); }
    static void* operator new(size_t size, void* memory) { return memory; }
    static void* operator new[](size_t size) { return TGUINew(size); }
    static void operator delete(void* memory) { TGUIDelete(memory); }
    static void operator delete[](void* memory) { TGUIDelete(memory); }

    static TClass m_sClass;
    static TGUIWidgetInfo* ms_widget_info;
    static TPCString* ms_paDirectionName;

protected:
    static TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static TArray<TGUIPropertySpec*>* ms_oPropertySet;

    TGUIWidget(const TGUIWidget& other);
    void PackChildren();
    void SetComponentBBox(int component, int x, int y, int width, int height);
    void GetComponentInteriorBBox(int component, int& left, int& top, int& right, int& bottom);
    void RemoveFocus();

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    /* 0x10 */ int m_unk10;     // two TGenericEmitter objects (0xC bytes each) start here
    /* 0x14 */ int m_unk14;
    /* 0x18 */ int m_unk18;
    /* 0x1C */ int m_unk1C;
    /* 0x20 */ int m_unk20;
    /* 0x24 */ int m_unk24;
    TGUIInterface* m_pInterface;                // +0x28
    TGUIStyle* m_pStyle;                        // +0x2C
    /* 0x30 */ unsigned char m_unk30;
    PPropertyValue* m_pParameters;              // +0x34, one value per parameter of the style
protected:
    const TGUIWidgetInfo* m_pWidgetInfo;        // +0x38 (each derived class's constructor sets its own)
private:
    /* 0x3C */ int m_unk3C;
    TGUILayoutManager* m_pLayoutManager;        // +0x40 owned
    TGUIWidget* m_pParent;                      // +0x44
    TNodeList<TGUIWidget> m_oChildren;          // +0x48
    /* 0x58 */ int m_unk58;     // list of state slaves (TDList)
    /* 0x5C */ int m_unk5C;
    /* 0x60 */ int m_unk60;     // list of actions (TDList)
    /* 0x64 */ int m_unk64;
    TPCString m_oName;                          // +0x68
    short m_sX;                                 // +0x6C
    short m_sY;                                 // +0x6E
    short m_sWidth;                             // +0x70
    short m_sHeight;                            // +0x72
    SizeMode m_eSizeModeHoriz;                  // +0x74
    SizeMode m_eSizeModeVert;                   // +0x78
    PlaceMode m_ePlaceMode;                     // +0x7C
    float m_fAnimSync;                          // +0x80
    bool m_bValidated;                          // +0x84
    bool m_bPaintChildrenFirst;                 // +0x85
    bool m_bLayoutValid;                        // +0x86
    unsigned int m_uiState;                     // +0x88
};

} // namespace Toshi
#endif
