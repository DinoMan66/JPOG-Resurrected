// Toshi::TGUIFont (TGuiInterface.dll): a bitmap font of the GUI - a name, an id, the textures its glyphs live
// on and the list of glyph sections. Fonts are kept in TGUIInterface's font list. Only the accessors are written so far.
#ifndef TGUIFONT_H
#define TGUIFONT_H
#include "TGUIAPI.h"
#include "TGUIDeserialisable.h"
#include "TArray.h"
#include "TNodeList.h"
#include "TPString.h"

namespace Toshi {

class TGUIInterface;
class TGUITextureSection;

class TGUI_API TGUIFont : public TGUIDeserialisable, public TNodeList<TGUIFont>::TNode
{
public:
    virtual void SetInterface(TGUIInterface* gui);                  // slot 9
    virtual TGUIInterface* GetInterface() const;                    // slot 10

    TArray<short>& GetTextureList();
    TNodeList<TGUITextureSection>& GetGlyphList();
    void SetSpacing(int spacing);
    int GetSpacing() const;
    void SetFontHeight(int height);
    int GetFontHeight() const;
    const TPCString& GetName() const;
    void SetName(const TPCString& name);
    bool Create(const TPCString& name, int height, int spacing);
    void SetFontID(int id);
    int GetFontID() const;
    static void SetScale(float scaleX, float scaleY);

protected:
    virtual const TArray<TGUIPropertySpec*>* GetPropertyInfoSet() const;       // slot 11
    virtual const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    static TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static TArray<TGUIPropertySpec*>* ms_oPropertySet;
    static float ms_fScaleY;
    static float ms_fScaleX;

    TGUIInterface* m_pInterface;                // +0x10
    TPCString m_oName;                          // +0x14
    int m_iFontID;                              // +0x18
    TArray<short> m_oTextures;                  // +0x1C
    TNodeList<TGUITextureSection> m_oGlyphs;    // +0x2C
    unsigned char m_unk3C[0xC];                 // +0x3C
    int m_iFontHeight;                          // +0x48
    int m_iSpacing;                             // +0x4C
};

} // namespace Toshi
#endif
