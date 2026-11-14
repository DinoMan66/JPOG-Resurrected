// Toshi::TTextureFactoryHAL (TRenderD3DInterface.dll) - Direct3D texture factory. Adds no members
// to TTextureFactory.
#ifndef TTEXTUREFACTORYHAL_H
#define TTEXTUREFACTORYHAL_H
#include "TTextureFactory.h"
#include "TRenderD3DAPI.h"

namespace Toshi {

class TRENDERD3D_API TTextureFactoryHAL : public TTextureFactory
{
    TOSHI_DECLARE_CLASS(TTextureFactoryHAL)
public:
    TTextureFactoryHAL();
    virtual ~TTextureFactoryHAL();

    virtual void Dump();
    virtual TTextureResource* CreateTextureFromFile(const char* fileName, unsigned int flags);
    virtual TTextureResource* CreateTextureFromMemory(void* data, unsigned int dataSize,
                                                      unsigned int flags, unsigned int width,
                                                      unsigned int height);
    virtual TTextureResource* CreateEx(void* data, unsigned int dataSize, unsigned int width,
                                       unsigned int height, unsigned int mipLevels,
                                       TTEXTURERESOURCEFORMAT format, unsigned int flags);
};

} // namespace Toshi
#endif
