// Z:\Toshi\Source\TGUI - TGUIInterface. The original file name is not in the binary's strings.
// Only the accessors are written so far.
#define TGUIINTERFACE_EXPORTS
#include "TGUIInterface.h"
#include "TGUIFont.h"
#include "TGUITextureSection.h"
#include "TGUIStyle.h"
#include "TGUITextureFactory.h"
#include "TGUIWidgetInfo.h"
#include "TGUILayoutInfo.h"
#include "TGUIComponentInfo.h"
#include "TNewDelete.h"

namespace Toshi {

TNodeList<TGUIComponentInfo> TGUIInterface::ms_oComponentClasses;
TNodeList<TGUILayoutInfo> TGUIInterface::ms_oLayoutClasses;
TNodeList<TGUIWidgetInfo> TGUIInterface::ms_oWidgetClasses;

void TGUIInterface::AddWidgetClass(TGUIWidgetInfo& info)
{
    ms_oWidgetClasses.InsertHead(&info);
}

void TGUIInterface::AddLayoutClass(TGUILayoutInfo* info)
{
    ms_oLayoutClasses.InsertHead(info);
}

void TGUIInterface::AddComponentClass(TGUIComponentInfo* info)
{
    ms_oComponentClasses.InsertHead(info);
}

TGUIWidgetInfo* TGUIInterface::FindWidgetClass(const TPCString& name)
{
    for (TNodeList<TGUIWidgetInfo>::Iterator it = ms_oWidgetClasses.Begin(); it != ms_oWidgetClasses.End(); ++it)
    {
        if (name == it->GetWidgetName())
            return it.Get();
    }
    return 0;
}

TGUILayoutInfo* TGUIInterface::FindLayoutClass(const TPCString& name)
{
    for (TNodeList<TGUILayoutInfo>::Iterator it = ms_oLayoutClasses.Begin(); it != ms_oLayoutClasses.End(); ++it)
    {
        if (name == it->GetLayoutName())
            return it.Get();
    }
    return 0;
}

TGUIComponentInfo* TGUIInterface::FindComponentClass(const TPCString& name)
{
    for (TNodeList<TGUIComponentInfo>::Iterator it = ms_oComponentClasses.Begin(); it != ms_oComponentClasses.End(); ++it)
    {
        if (name == it->GetComponentName())
            return it.Get();
    }
    return 0;
}

const TNodeList<TGUIComponentInfo>& TGUIInterface::GetComponentClassList()
{
    return ms_oComponentClasses;
}

const TNodeList<TGUILayoutInfo>& TGUIInterface::GetLayoutClassList()
{
    return ms_oLayoutClasses;
}

const TNodeList<TGUIWidgetInfo>& TGUIInterface::GetWidgetClassList()
{
    return ms_oWidgetClasses;
}

TKernelInterface* TGUIInterface::GetKernelInterface() const
{
    return m_pKernelInterface;
}

void TGUIInterface::SetKernelInterface(TKernelInterface* kernel)
{
    m_pKernelInterface = kernel;
}

TGUIScreen* TGUIInterface::GetDefaultScreen() const
{
    return m_pDefaultScreen;
}

void TGUIInterface::SetDefaultScreen(TGUIScreen* screen)
{
    m_pDefaultScreen = screen;
}

TGUITextureFactory* TGUIInterface::GetTextureFactory() const
{
    return m_pTextureFactory;
}

TGUIFontFactory* TGUIInterface::GetFontFactory() const
{
    return m_pFontFactory;
}

TGUISoundFactory* TGUIInterface::GetSoundFactory() const
{
    return m_pSoundFactory;
}

void TGUIInterface::SetTextureFactory(TGUITextureFactory* factory)
{
    m_pTextureFactory = factory;
}

void TGUIInterface::SetFontFactory(TGUIFontFactory* factory)
{
    m_pFontFactory = factory;
}

void TGUIInterface::SetSoundFactory(TGUISoundFactory* factory)
{
    m_pSoundFactory = factory;
}

const TArray<TPCString>& TGUIInterface::GetSkuArray() const
{
    return m_oSkus;
}

void TGUIInterface::DeleteAllSkus()
{
    m_oSkus.Clear();
}

TGUIFont* TGUIInterface::FindFont(const TPCString& name) const
{
    for (TNodeList<TGUIFont>::Iterator it = m_oFonts.Begin(); it != m_oFonts.End(); ++it)
    {
        if (name == it->GetName())
            return it.Get();
    }
    return 0;
}

short TGUIInterface::FindTexture(const TPCString& name) const
{
    return m_pTextureFactory->vf3(name);
}

const TNodeList<TGUIFont>& TGUIInterface::GetFontList() const
{
    return m_oFonts;
}

const TNodeList<TGUITextureSection>& TGUIInterface::GetTextureSectionList() const
{
    return m_oTextureSections;
}

const TNodeList<TGUIWidget>& TGUIInterface::GetScreenInstanceList() const
{
    return m_oScreenInstances;
}

const TNodeList<TGUIInterface::TopLevelInfo>& TGUIInterface::GetTopLevelInstanceList() const
{
    return m_oTopLevelInstances;
}

const TNodeList<TGUIStyle>& TGUIInterface::GetStyleInstanceList() const
{
    return m_oStyleInstances;
}

void TGUIInterface::DeleteFont(TGUIFont* font)
{
    m_oFonts.Remove(font);
    delete font;
}

void TGUIInterface::DeleteStyleInstance(TGUIStyle* style)
{
    m_oStyleInstances.Remove(style);
    delete style;
}

} // namespace Toshi
