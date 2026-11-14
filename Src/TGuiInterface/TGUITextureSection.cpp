// Z:\Toshi\Source\TGUI - TGUITextureSection. The original file name is not in the binary's strings.
// The default constructor and the destructor are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUITextureSection.h"
#include "TNewDelete.h"

namespace Toshi {

TGUITextureSection* TGUITextureSection::Clone() const
{
    return new TGUITextureSection(*this);
}

TGUITextureSection::TGUITextureSection(const TGUITextureSection& other)
{
    Assign(other);
}

void TGUITextureSection::Set(short texture, const TPCString& name, int x, int y, int width, int height, int rotation,
                             bool wrap, bool mirrorX, bool mirrorY)
{
    m_sTexture = texture;
    m_oName = name;
    m_usX = x;
    m_usY = y;
    m_usWidth = width;
    m_usHeight = height;
    m_ucRotation = rotation;
    m_bWrap = wrap;
    m_bMirrorX = mirrorX;
    m_bMirrorY = mirrorY;
}

void TGUITextureSection::Assign(const TGUITextureSection& other)
{
    m_sTexture = other.m_sTexture;
    m_oName = other.GetName();
    m_usX = other.GetX();
    m_usY = other.GetY();
    m_usWidth = other.GetWidth();
    m_usHeight = other.GetHeight();
    m_ucRotation = other.GetRotation();
    m_bWrap = other.GetWrap();
    m_bMirrorX = other.GetMirrorX();
    m_bMirrorY = other.GetMirrorY();
}

TClass TGUITextureSection::m_sClass("TGUITextureSection", &TObject::m_sClass, TGUITextureSection::CreateObject,
                                    TGUITextureSection::CreateObjectInPlace, TGUITextureSection::InitialiseStatic,
                                    TGUITextureSection::DeinitialiseStatic, 0x10000);

TClass& TGUITextureSection::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUITextureSection::DeinitialiseStatic()
{
}

void __stdcall TGUITextureSection::InitialiseStatic()
{
}

TObject* __stdcall TGUITextureSection::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUITextureSection;
}

TObject* __stdcall TGUITextureSection::CreateObject()
{
    return new TGUITextureSection;
}

} // namespace Toshi
