// Toshi::TRenderCapture (TRenderInterface.dll, TRenderCapture.cpp, 0x9bf0-0x9c10): abstract
// screen capture; implemented by the platform renderer (TRenderCaptureD3D). The slot order
// follows the TRenderCaptureD3D vtable.
#ifndef TRENDERCAPTURE_H
#define TRENDERCAPTURE_H
#include "TRenderAPI.h"

namespace Toshi {

class TRENDER_API TRenderCapture
{
public:
    enum FORMAT { };

    TRenderCapture();
    virtual ~TRenderCapture() {}                                        // slot 0

    virtual bool Create(FORMAT format, int width, int height) = 0;      // slot 1
    virtual void Destroy() = 0;                                         // slot 2
    virtual bool Request() = 0;                                         // slot 3
    virtual bool Wait() = 0;                                            // slot 4
    virtual bool Poll() = 0;                                            // slot 5
    virtual void* ObtainBuffer() = 0;                                   // slot 6
    virtual void ReleaseBuffer() = 0;                                   // slot 7

private:
    TRenderCapture(const TRenderCapture&);                              // not exported
    TRenderCapture& operator=(const TRenderCapture&);
};

} // namespace Toshi
#endif
