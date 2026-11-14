// Z:\Toshi\Source\TGUI\TGUIScreen.h - only what the widget code needs so far.
#ifndef TGUISCREEN_H
#define TGUISCREEN_H

#include "TGUIAPI.h"
#include "TGUIWindow.h"

namespace Toshi {

class TGUIInputManager;
class TGUIInputContext;
class TGUIAudioContext;
class TGUIDisplayContext;
class TGUITextureSection;

class TGUI_API TGUIScreen : public TGUIWindow
{
public:
    static TClass m_sClass;

    virtual bool Deserialise(const PProperties* properties);    // slot 3
    virtual bool Serialise(PProperties* properties);            // slot 4
    virtual TGUIWidget* AllowsFocus(TGUIWidget* from);          // slot 17
    virtual bool OnButtonRelease(TInputInterface::InputEvent* event, int doodad);   // slot 26
    virtual void Pack();                                        // slot 33
    virtual void Layout(short width, short height);             // slot 34 (pure in TGUIWidget, not declared there yet)

    void ReleaseFocus(TGUIWidget* widget);
    void ChangeWidgetFocus(TGUIWidget* widget, bool force);

    int GetPointerPositionX() const { return m_iPointerX; }
    int GetPointerPositionY() const { return m_iPointerY; }
    void GetPointerPosition(int& x, int& y) const;
    void SetPointerSpeed(float speed);
    bool IsPointerVisible() const;
    void SetPointerVisible(bool visible);
    TGUIWidget* GetFocusedWidget() const;
    TGUIWindow* GetFocusedWindow() const;
    TGUIInputContext* GetInputContext() const;
    void SetInputContext(TGUIInputContext* context);
    TGUIAudioContext* GetAudioContext() const;
    void SetAudioContext(TGUIAudioContext* context);
    TGUIDisplayContext* GetDisplayContext() const;
    void SetDisplayContext(TGUIDisplayContext* context);
    TGUIInputManager* GetInputManager();
    void PushInputManager(TGUIInputManager* manager);
    void PopInputManager(TGUIInputManager* manager);
    TGUIWidget* GetFocusGrabWidget() const;
    bool IsPaintContinued();
    void NotifyDescendantCanFocus(TGUIWidget* widget);
    void NotifyFocusGained();
    void NotifyFocusLost();
    void GrabPointer(TGUIWidget* widget);
    void ContinuePaint();
    void RestartPaint();
    void SetPointerAccel(int accel, int unused, int limit);
    void SetPointerImage(TGUITextureSection* image, int hotspotX, int hotspotY);

protected:
    virtual const TArray<TGUIPropertySpec*>* GetPropertyInfoSet() const;       // slot 11
    virtual const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12
    void Paint(TGUIWidget* from);
    static void __stdcall pointer_out_callback(TGUIWidget* widget);

private:
    static TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static TArray<TGUIPropertySpec*>* ms_oPropertySet;

    unsigned char m_unkA4[0x1C];                // +0xA4
    TGUIDisplayContext* m_pDisplayContext;      // +0xC0
    TGUIAudioContext* m_pAudioContext;          // +0xC4
    TGUIInputContext* m_pInputContext;          // +0xC8
    int m_iInputManagerIndex;                   // +0xCC top of the input manager stack
    TGUIInputManager* m_apInputManagers[8];     // +0xD0
    TGUIWindow* m_pFocusedWindow;               // +0xF0
    TGUIWidget* m_pFocusedWidget;               // +0xF4
    TGUIWidget* m_pPointerGrabWidget;           // +0xF8 set by GrabPointer
    unsigned char m_unkFC[4];                   // +0xFC
    int m_unk100;                               // +0x100 number of entries of the focus grab array
    unsigned char m_unk104[4];                  // +0x104
    TGUIWidget** m_unk108;                      // +0x108 focus grab widgets, the last one is the current grabber
    unsigned char m_unk10C[8];                  // +0x10C
    int m_iPointerX;                            // +0x114
    int m_iPointerY;                            // +0x118
    float m_fPointerSpeed;                      // +0x11C
    unsigned char m_unk120[4];                  // +0x120
    TGUITextureSection* m_pPointerImage;        // +0x124
    int m_unk128;                               // +0x128
    int m_unk12C;                               // +0x12C
    bool m_bPointerVisible;                     // +0x130
    unsigned char m_unk131[3];                  // +0x131
    TGUIWidget* m_unk134;                       // +0x134 widget the interrupted paint continues from
    int m_unk138;                               // +0x138
    int m_unk13C;                               // +0x13C
    int m_unk140;                               // +0x140
};

} // namespace Toshi

#endif
