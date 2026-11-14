// Toshi::TGUITextureSection (TGuiInterface.dll): a named rectangle of a texture (and how it is drawn:
// rotated, mirrored, wrapped). The GUI draws all its pictures and font glyphs from texture sections; the
// sections are kept in lists by the texture they belong to.
// Size 0x28. Derived: TGUIFontGlyph, TGUITextureAnimation.
#ifndef TGUITEXTURESECTION_H
#define TGUITEXTURESECTION_H
#include "TGUIAPI.h"
#include "TNodeList.h"
#include "TObject.h"
#include "TPString.h"

namespace Toshi {

class TGUI_API TGUITextureSection : public TObject, public TNodeList<TGUITextureSection>::TNode
{
public:
    TGUITextureSection();
    TGUITextureSection(const TGUITextureSection& other);
    virtual ~TGUITextureSection();

    virtual TClass& GetClass() const;                           // slot 0
    virtual TGUITextureSection* Clone() const;                  // slot 3
    virtual void GetBBox(unsigned short& x, unsigned short& y, unsigned short& width, unsigned short& height,
                         float scale) const                     // slot 5
    {
        x = m_usX;
        y = m_usY;
        width = m_usWidth;
        height = m_usHeight;
    }
    virtual void GetBBox(unsigned short& x, unsigned short& y, unsigned short& width, unsigned short& height,
                         int frame) const                       // slot 4
    {
        x = m_usX;
        y = m_usY;
        width = m_usWidth;
        height = m_usHeight;
    }
    virtual void SetBBox(unsigned short x, unsigned short y, unsigned short width, unsigned short height,
                         int frame)                             // slot 6
    {
        m_usX = x;
        m_usY = y;
        m_usWidth = width;
        m_usHeight = height;
    }

    void Set(short texture, const TPCString& name, int x, int y, int width, int height, int rotation, bool wrap,
             bool mirrorX, bool mirrorY);
    void SetMirrorY(bool mirror) { m_bMirrorY = mirror; }
    void SetMirrorX(bool mirror) { m_bMirrorX = mirror; }
    void SetWrap(bool wrap) { m_bWrap = wrap; }
    void SetRotation(unsigned short rotation) { m_ucRotation = rotation; }
    void SetHeight(unsigned short height) { m_usHeight = height; }
    void SetWidth(unsigned short width) { m_usWidth = width; }
    void SetY(unsigned short y) { m_usY = y; }
    void SetX(unsigned short x) { m_usX = x; }
    void SetTexture(short texture) { m_sTexture = texture; }

    bool GetMirrorY() const { return m_bMirrorY; }
    bool GetMirrorX() const { return m_bMirrorX; }
    bool GetWrap() const { return m_bWrap; }
    unsigned short GetRotation() const { return m_ucRotation; }
    unsigned short GetHeight() const { return m_usHeight; }
    unsigned short GetWidth() const { return m_usWidth; }
    unsigned short GetY() const { return m_usY; }
    unsigned short GetX() const { return m_usX; }
    const TPCString& GetName() const { return m_oName; }
    void SetName(const TPCString& name) { m_oName = name; }

    static TClass m_sClass;

protected:
    void Assign(const TGUITextureSection& other);

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    short m_sTexture;                       // +0x10
    /* 0x12 */ short m_unk12;
    TPCString m_oName;                      // +0x14
    unsigned short m_usX;                   // +0x18
    unsigned short m_usY;                   // +0x1A
    unsigned short m_usWidth;               // +0x1C
    unsigned short m_usHeight;              // +0x1E
    unsigned char m_ucRotation : 2;         // +0x20, a quarter turn count
    unsigned char m_ucUnk20 : 6;
    /* 0x21 */ unsigned char m_unk21;
    /* 0x22 */ unsigned char m_unk22;
    /* 0x23 */ unsigned char m_unk23;
    unsigned char m_bWrap : 1;              // +0x24
    unsigned char m_bMirrorX : 1;
    unsigned char m_bMirrorY : 1;
    unsigned char m_ucUnk24 : 5;
    /* 0x25 */ unsigned char m_unk25[3];
};

} // namespace Toshi
#endif
