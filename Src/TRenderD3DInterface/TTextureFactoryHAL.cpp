// Toshi::TTextureFactoryHAL.
// Source unit: Z:\Toshi\Source\TRenderD3D\TTextureFactoryD3D.cpp (path string in the binary).
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TTextureFactoryHAL.h"
#include "TTextureResource.h"
#include "TRenderInterface.h"

namespace Toshi {

TTextureFactoryHAL::TTextureFactoryHAL()
{
}

TTextureFactoryHAL::~TTextureFactoryHAL()
{
}

void TTextureFactoryHAL::Dump()
{
    TTextureFactory::Dump();
}

TTextureResource* TTextureFactoryHAL::CreateTextureFromFile(const char* fileName, unsigned int flags)
{
    TTextureResource* texture = FindTexture(fileName);
    if (texture != 0)
        return texture;
    texture = TTextureResource::CreateHAL(GetRenderer(), 0, this);
    texture->Create(fileName, flags);
    RegisterTexture(fileName, texture);
    texture->Validate();
    return texture;
}

TOSHI_DEFINE_CLASS(TTextureFactoryHAL, TTextureFactory)
TOSHI_DEFINE_CLASS_FUNCTIONS_CONCRETE(TTextureFactoryHAL)

} // namespace Toshi
