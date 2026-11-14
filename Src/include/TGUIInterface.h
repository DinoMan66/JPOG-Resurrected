// Toshi::TGUIInterface (TGuiInterface.dll): the GUI system's root object. It owns the factories that create
// textures, fonts and sounds, the lists of everything loaded from the GUI definition files (styles, top-level
// widgets, screens, texture sections, fonts, SKU names) and the screen that receives input by default.
// Only the accessors are written so far; the members whose purpose is unknown keep offset names.
// Layout (from the accessors): the lists are 0x10 bytes each, one after the other from +0x20.
#ifndef TGUIINTERFACE_H
#define TGUIINTERFACE_H
#include "TGUIAPI.h"
#include "TObject.h"
#include "TArray.h"
#include "TNodeList.h"
#include "TPString.h"

namespace Toshi {

class TKernelInterface;
class TGUITextureFactory;
class TGUIFontFactory;
class TGUISoundFactory;
class TGUIScreen;
class TGUIStyle;
class TGUIWidget;
class TGUIFont;
class TGUIWidgetInfo;
class TGUILayoutInfo;
class TGUIComponentInfo;
class TGUITextureSection;

class TGUI_API TGUIInterface : public TObject
{
public:
    struct TopLevelInfo;

    TGUIInterface();
    virtual ~TGUIInterface();
    virtual TClass& GetClass() const;

    TKernelInterface* GetKernelInterface() const;
    void SetKernelInterface(TKernelInterface* kernel);
    TGUIScreen* GetDefaultScreen() const;
    void SetDefaultScreen(TGUIScreen* screen);

    TGUITextureFactory* GetTextureFactory() const;
    TGUIFontFactory* GetFontFactory() const;
    TGUISoundFactory* GetSoundFactory() const;
    void SetTextureFactory(TGUITextureFactory* factory);
    void SetFontFactory(TGUIFontFactory* factory);
    void SetSoundFactory(TGUISoundFactory* factory);

    const TArray<TPCString>& GetSkuArray() const;
    void DeleteAllSkus();
    TGUIFont* FindFont(const TPCString& name) const;
    TGUIWidgetInfo* FindWidgetClass(const TPCString& name);
    TGUILayoutInfo* FindLayoutClass(const TPCString& name);
    TGUIComponentInfo* FindComponentClass(const TPCString& name);
    short FindTexture(const TPCString& name) const;
    const TNodeList<TGUIFont>& GetFontList() const;
    const TNodeList<TGUITextureSection>& GetTextureSectionList() const;
    const TNodeList<TGUIWidget>& GetScreenInstanceList() const;
    const TNodeList<TopLevelInfo>& GetTopLevelInstanceList() const;
    const TNodeList<TGUIStyle>& GetStyleInstanceList() const;

    void DeleteFont(TGUIFont* font);
    void DeleteStyleInstance(TGUIStyle* style);

    static TClass m_sClass;

    static void AddWidgetClass(TGUIWidgetInfo& info);
    static void AddLayoutClass(TGUILayoutInfo* info);
    static void AddComponentClass(TGUIComponentInfo* info);
    static const TNodeList<TGUIComponentInfo>& GetComponentClassList();
    static const TNodeList<TGUILayoutInfo>& GetLayoutClassList();
    static const TNodeList<TGUIWidgetInfo>& GetWidgetClassList();

private:
    static TNodeList<TGUIComponentInfo> ms_oComponentClasses;
    static TNodeList<TGUILayoutInfo> ms_oLayoutClasses;
    static TNodeList<TGUIWidgetInfo> ms_oWidgetClasses;

    int m_unk04;                                        // +0x04
    TKernelInterface* m_pKernelInterface;               // +0x08
    unsigned char m_unk0C[8];                           // +0x0C
    TGUITextureFactory* m_pTextureFactory;              // +0x14
    TGUIFontFactory* m_pFontFactory;                    // +0x18
    TGUISoundFactory* m_pSoundFactory;                  // +0x1C
    TNodeList<TGUIStyle> m_oStyleInstances;             // +0x20
    TNodeList<TopLevelInfo> m_oTopLevelInstances;       // +0x30
    TNodeList<TGUIWidget> m_oScreenInstances;           // +0x40
    TNodeList<TGUITextureSection> m_oTextureSections;   // +0x50
    TNodeList<TGUIFont> m_oFonts;                       // +0x60
    TArray<TPCString> m_oSkus;                          // +0x70
    TGUIScreen* m_pDefaultScreen;                       // +0x80
};

} // namespace Toshi
#endif
