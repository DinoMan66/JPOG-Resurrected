// Toshi::TGUITextureAnimation (TGuiInterface.dll): a texture section that changes over time. It is a list of
// frames (each one a texture section and how long it stays) played at a frequency; GetBBox/SetBBox work on
// the frame the animation is showing.
// Size 0x3C.
#ifndef TGUITEXTUREANIMATION_H
#define TGUITEXTUREANIMATION_H
#include "TGUIAPI.h"
#include "TArray.h"
#include "TGUITextureSection.h"

namespace Toshi {

class TGUI_API TGUITextureAnimation : public TGUITextureSection
{
public:
    // One step of the animation, 8 bytes; the members are not known yet
    class Frame
    {
    public:
        /* 0x00 */ int m_unk00;
        /* 0x04 */ int m_unk04;
    };

    TGUITextureAnimation();
    virtual ~TGUITextureAnimation();

    virtual TClass& GetClass() const;
    virtual TGUITextureSection* Clone() const;
    virtual void GetBBox(unsigned short& x, unsigned short& y, unsigned short& width, unsigned short& height,
                         float scale) const;
    virtual void GetBBox(unsigned short& x, unsigned short& y, unsigned short& width, unsigned short& height,
                         int frame) const;
    virtual void SetBBox(unsigned short x, unsigned short y, unsigned short width, unsigned short height,
                         int frame);

    // frames are counted from 1
    Frame& GetFrame(int number) { return m_oFrames[number - 1]; }
    TArray<Frame>& GetFrames() { return m_oFrames; }
    void SetFrequency(float frequency) { m_fFrequency = frequency; }
    float GetFrequency() const { return m_fFrequency; }

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    float m_fFrequency;             // +0x28
    TArray<Frame> m_oFrames;        // +0x2C
};

} // namespace Toshi
#endif
