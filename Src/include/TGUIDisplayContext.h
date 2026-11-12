// Toshi::TGUIDisplayContext (TGuiInterface.dll): abstract drawing interface for the GUI. A renderer
// (PGUITRDisplayContext in PGUIRenderer.dll) implements the pure virtual slots; this class keeps the
// clip rectangle stack and the animation clock and forwards the convenience Draw* calls to them.
// Slots 7-22 are pure virtuals the renderer overrides (PushScale, PopTransform, PushModulateColour, ...,
// DrawLabel); their signatures are not recovered yet, so they stay placeholders.
#ifndef TGUIDISPLAYCONTEXT_H
#define TGUIDISPLAYCONTEXT_H
#include "TGUIAPI.h"
#include "TObject.h"
#include "TGUIAlignment.h"
#include "TGUIColour.h"
#include "TGUIRectangle.h"

namespace Toshi {

class TGUIFormattedText;
class TGUITextureSection;

class TGUI_API TGUIDisplayContext : public TObject
{
public:
    enum { MAX_CLIPS = 32 };

    TGUIDisplayContext();
    virtual ~TGUIDisplayContext();

    virtual TClass& GetClass() const;                                                           // slot 0
    virtual void PushClip(int x, int y, int width, int height);                                 // slot 3
    virtual void PopClip();                                                                     // slot 4
    virtual void PushRotation(float angle);                                                     // slot 6
    virtual void PushRotation(float angle, int centreX, int centreY) = 0;                       // slot 5 (overloads are laid out in reverse declaration order)
    virtual void vf7() = 0;
    virtual void vf8() = 0;
    virtual void vf9() = 0;
    virtual void vf10() = 0;
    virtual void vf11() = 0;
    virtual void vf12() = 0;
    virtual void vf13() = 0;
    virtual void vf14() = 0;
    virtual void vf15() = 0;
    virtual void vf16() = 0;
    virtual void vf17() = 0;
    virtual void vf18() = 0;
    virtual void vf19() = 0;
    virtual void vf20() = 0;
    virtual void vf21() = 0;
    virtual void vf22() = 0;
    virtual void DrawFormattedText(TGUIFormattedText& text, int x, int y, int width, int height);  // slot 23
    virtual void Imp_DrawTextureSection(const TGUITextureSection* section, const TGUIColour& colour,
                                        int x, int y, int width, int height,
                                        TGUIAlignment horizontal, TGUIAlignment vertical) = 0;   // slot 24
    virtual void Imp_DrawFilledRectangle(int left, int top, int right, int bottom,
                                         const TGUIColour& colour) = 0;                            // slot 25
    virtual void Imp_DrawOutlineRectangle(int left, int top, int right, int bottom,
                                          const TGUIColour& colour) = 0;                           // slot 26

    void DrawOutlineRectangle(const TGUIRectangle& rect, const TGUIColour& colour);
    void DrawOutlineRectangle(int x, int y, int width, int height, const TGUIColour& colour);
    void DrawFilledRectangle(const TGUIRectangle& rect, const TGUIColour& colour);
    void DrawFilledRectangle(int x, int y, int width, int height, const TGUIColour& colour);
    void DrawTextureSection(const TGUITextureSection* section, const TGUIColour& colour,
                            const TGUIRectangle* rect, TGUIAlignment horizontal, TGUIAlignment vertical);
    void DrawTextureSection(const TGUITextureSection* section, const TGUIColour& colour,
                            int x, int y, int width, int height,
                            TGUIAlignment horizontal, TGUIAlignment vertical);

    float GetCurrentTime() const;
    void SetCurrentTime(float time);
    void SetTimeOffset(float offset);

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    int m_iClipDepth;                       // +0x004 index of the current clip in m_aClip
    TGUIRectangle m_aClip[MAX_CLIPS];       // +0x008
    float m_fBaseTime;                      // +0x208
    float m_fCurrentTime;                   // +0x20C base time plus the offset
};

} // namespace Toshi
#endif
