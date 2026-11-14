// Minimal Direct3D 8 interface declarations (only what the game's renderer calls). The member
// order is the public IDirect3DDevice8 / IDirect3D8 vtable order of the DirectX 8 SDK, which the
// renderer's call sites (call [vtable + 4 * slot]) confirm. Parameter types that no code here
// uses are kept opaque.
#ifndef D3D8MIN_H
#define D3D8MIN_H

typedef long HRESULT;
typedef unsigned long DWORD;
typedef unsigned int UINT;

struct _D3DMATRIX
{
    float m[4][4];
};
typedef _D3DMATRIX D3DMATRIX;
enum
{
    D3DUSAGE_WRITEONLY = 0x00000008,
    D3DUSAGE_SOFTWAREPROCESSING = 0x00000010,
    D3DUSAGE_DYNAMIC = 0x00000200
};
enum
{
    D3DLOCK_NOSYSLOCK = 0x00000800,
    D3DLOCK_NOOVERWRITE = 0x00001000,
    D3DLOCK_DISCARD = 0x00002000
};
enum _D3DFORMAT
{
    D3DFMT_A8R8G8B8 = 21,
    D3DFMT_X8R8G8B8 = 22,
    D3DFMT_A1R5G5B5 = 25,
    D3DFMT_INDEX16 = 101
};
enum
{
    D3DPOOL_DEFAULT = 0,
    D3DPOOL_MANAGED = 1
};
struct _D3DGAMMARAMP
{
    unsigned short red[256];
    unsigned short green[256];
    unsigned short blue[256];
};
struct IDirect3DBaseTexture8;
struct IDirect3DSurface8;
struct IDirect3DTexture8;
struct tagRECT;
struct _D3DLOCKED_RECT;

enum D3DTRANSFORMSTATETYPE
{
    D3DTS_VIEW = 2,
    D3DTS_PROJECTION = 3,
    D3DTS_WORLD = 256
};

enum D3DTEXTURESTAGESTATETYPE
{
    D3DTSS_COLOROP = 1,
    D3DTSS_COLORARG1 = 2,
    D3DTSS_COLORARG2 = 3,
    D3DTSS_ALPHAOP = 4,
    D3DTSS_ALPHAARG1 = 5,
    D3DTSS_ALPHAARG2 = 6,
    D3DTSS_ADDRESSU = 13,
    D3DTSS_ADDRESSV = 14,
    D3DTSS_MAGFILTER = 16,
    D3DTSS_MINFILTER = 17,
    D3DTSS_MIPFILTER = 18
};

enum D3DRENDERSTATETYPE
{
    D3DRS_ZENABLE = 7,
    D3DRS_CULLMODE = 22,
    D3DRS_LIGHTING = 137
};

enum
{
    D3DTADDRESS_WRAP = 1,
    D3DTADDRESS_MIRROR = 2,
    D3DTADDRESS_CLAMP = 3,
    D3DTADDRESS_BORDER = 4,
    D3DTEXF_LINEAR = 2,
    D3DCULL_CW = 2,
    D3DZB_TRUE = 1
};

struct IDirect3DDevice8;
struct IDirect3DIndexBuffer8;
struct IDirect3DVertexBuffer8;

struct IDirect3DDevice8
{
    virtual HRESULT __stdcall QueryInterface(const void* iid, void** object) = 0;       // 0
    virtual unsigned long __stdcall AddRef() = 0;                                       // 1
    virtual unsigned long __stdcall Release() = 0;                                      // 2
    virtual HRESULT __stdcall TestCooperativeLevel() = 0;                               // 3
    virtual UINT __stdcall GetAvailableTextureMem() = 0;                                // 4
    virtual HRESULT __stdcall ResourceManagerDiscardBytes(DWORD bytes) = 0;             // 5
    virtual HRESULT __stdcall GetDirect3D(void** d3d) = 0;                              // 6
    virtual HRESULT __stdcall GetDeviceCaps(void* caps) = 0;                            // 7
    virtual HRESULT __stdcall GetDisplayMode(void* mode) = 0;                           // 8
    virtual HRESULT __stdcall GetCreationParameters(void* parameters) = 0;              // 9
    virtual HRESULT __stdcall SetCursorProperties(UINT x, UINT y, IDirect3DSurface8* bitmap) = 0; // 10
    virtual void __stdcall SetCursorPosition(int x, int y, DWORD flags) = 0;            // 11
    virtual int __stdcall ShowCursor(int show) = 0;                                     // 12
    virtual HRESULT __stdcall CreateAdditionalSwapChain(void* params, void** chain) = 0; // 13
    virtual HRESULT __stdcall Reset(void* presentParameters) = 0;                       // 14
    virtual HRESULT __stdcall Present(const void* src, const void* dst, void* window, const void* dirty) = 0; // 15
    virtual HRESULT __stdcall GetBackBuffer(UINT index, int type, IDirect3DSurface8** buffer) = 0; // 16
    virtual HRESULT __stdcall GetRasterStatus(void* status) = 0;                        // 17
    virtual void __stdcall SetGammaRamp(DWORD flags, const _D3DGAMMARAMP* ramp) = 0;   // 18
    virtual void __stdcall GetGammaRamp(_D3DGAMMARAMP* ramp) = 0;                       // 19
    virtual HRESULT __stdcall CreateTexture(UINT width, UINT height, UINT levels, DWORD usage, int format, int pool, IDirect3DTexture8** texture) = 0; // 20
    virtual HRESULT __stdcall CreateVolumeTexture(UINT, UINT, UINT, UINT, DWORD, int, int, void**) = 0; // 21
    virtual HRESULT __stdcall CreateCubeTexture(UINT, UINT, DWORD, int, int, void**) = 0; // 22
    virtual HRESULT __stdcall CreateVertexBuffer(UINT length, DWORD usage, DWORD fvf, int pool, void** buffer) = 0; // 23
    virtual HRESULT __stdcall CreateIndexBuffer(UINT length, DWORD usage, int format, int pool, void** buffer) = 0; // 24
    virtual HRESULT __stdcall CreateRenderTarget(UINT, UINT, int, int, int, IDirect3DSurface8**) = 0; // 25
    virtual HRESULT __stdcall CreateDepthStencilSurface(UINT, UINT, int, int, IDirect3DSurface8**) = 0; // 26
    virtual HRESULT __stdcall CreateImageSurface(UINT, UINT, int, IDirect3DSurface8**) = 0; // 27
    virtual HRESULT __stdcall CopyRects(IDirect3DSurface8*, const void*, UINT, IDirect3DSurface8*, const void*) = 0; // 28
    virtual HRESULT __stdcall UpdateTexture(IDirect3DBaseTexture8*, IDirect3DBaseTexture8*) = 0; // 29
    virtual HRESULT __stdcall GetFrontBuffer(IDirect3DSurface8*) = 0;                   // 30
    virtual HRESULT __stdcall SetRenderTarget(IDirect3DSurface8*, IDirect3DSurface8*) = 0; // 31
    virtual HRESULT __stdcall GetRenderTarget(IDirect3DSurface8**) = 0;                 // 32
    virtual HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface8**) = 0;          // 33
    virtual HRESULT __stdcall BeginScene() = 0;                                         // 34
    virtual HRESULT __stdcall EndScene() = 0;                                           // 35
    virtual HRESULT __stdcall Clear(DWORD count, const void* rects, DWORD flags, DWORD colour, float z, DWORD stencil) = 0; // 36
    virtual HRESULT __stdcall SetTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX* matrix) = 0; // 37
    virtual HRESULT __stdcall GetTransform(D3DTRANSFORMSTATETYPE state, D3DMATRIX* matrix) = 0; // 38
    virtual HRESULT __stdcall MultiplyTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX* matrix) = 0; // 39
    virtual HRESULT __stdcall SetViewport(const void* viewport) = 0;                    // 40
    virtual HRESULT __stdcall GetViewport(void* viewport) = 0;                          // 41
    virtual HRESULT __stdcall SetMaterial(const void* material) = 0;                    // 42
    virtual HRESULT __stdcall GetMaterial(void* material) = 0;                          // 43
    virtual HRESULT __stdcall SetLight(DWORD index, const void* light) = 0;             // 44
    virtual HRESULT __stdcall GetLight(DWORD index, void* light) = 0;                   // 45
    virtual HRESULT __stdcall LightEnable(DWORD index, int enable) = 0;                 // 46
    virtual HRESULT __stdcall GetLightEnable(DWORD index, int* enable) = 0;             // 47
    virtual HRESULT __stdcall SetClipPlane(DWORD index, const float* plane) = 0;        // 48
    virtual HRESULT __stdcall GetClipPlane(DWORD index, float* plane) = 0;              // 49
    virtual HRESULT __stdcall SetRenderState(int state, DWORD value) = 0;               // 50
    virtual HRESULT __stdcall GetRenderState(int state, DWORD* value) = 0;              // 51
    virtual HRESULT __stdcall BeginStateBlock() = 0;                                    // 52
    virtual HRESULT __stdcall EndStateBlock(DWORD* token) = 0;                          // 53
    virtual HRESULT __stdcall ApplyStateBlock(DWORD token) = 0;                         // 54
    virtual HRESULT __stdcall CaptureStateBlock(DWORD token) = 0;                       // 55
    virtual HRESULT __stdcall DeleteStateBlock(DWORD token) = 0;                        // 56
    virtual HRESULT __stdcall CreateStateBlock(int type, DWORD* token) = 0;             // 57
    virtual HRESULT __stdcall SetClipStatus(const void* status) = 0;                    // 58
    virtual HRESULT __stdcall GetClipStatus(void* status) = 0;                          // 59
    virtual HRESULT __stdcall GetTexture(DWORD stage, IDirect3DBaseTexture8** texture) = 0; // 60
    virtual HRESULT __stdcall SetTexture(DWORD stage, IDirect3DBaseTexture8* texture) = 0; // 61
    virtual HRESULT __stdcall GetTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD* value) = 0; // 62
    virtual HRESULT __stdcall SetTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value) = 0; // 63
    virtual HRESULT __stdcall ValidateDevice(DWORD* passes) = 0;                        // 64
    virtual HRESULT __stdcall GetInfo(DWORD id, void* info, DWORD size) = 0;            // 65
    virtual HRESULT __stdcall SetPaletteEntries(UINT number, const void* entries) = 0;  // 66
    virtual HRESULT __stdcall GetPaletteEntries(UINT number, void* entries) = 0;        // 67
    virtual HRESULT __stdcall SetCurrentTexturePalette(UINT number) = 0;                // 68
    virtual HRESULT __stdcall GetCurrentTexturePalette(UINT* number) = 0;               // 69
    virtual HRESULT __stdcall DrawPrimitive(int type, UINT start, UINT count) = 0;      // 70
    virtual HRESULT __stdcall DrawIndexedPrimitive(int type, UINT minIndex, UINT numVertices, UINT startIndex, UINT primCount) = 0; // 71
    virtual HRESULT __stdcall DrawPrimitiveUP(int type, UINT count, const void* data, UINT stride) = 0; // 72
    virtual HRESULT __stdcall DrawIndexedPrimitiveUP(int type, UINT minIndex, UINT numVertices, UINT primCount, const void* indices, int indexFormat, const void* vertices, UINT stride) = 0; // 73
};

struct IDirect3DTexture8
{
    virtual HRESULT __stdcall QueryInterface(const void* iid, void** object) = 0;       // 0
    virtual unsigned long __stdcall AddRef() = 0;                                       // 1
    virtual unsigned long __stdcall Release() = 0;                                      // 2
    virtual HRESULT __stdcall GetDevice(IDirect3DDevice8** device) = 0;                 // 3
    virtual HRESULT __stdcall SetPrivateData(const void*, const void*, DWORD, DWORD) = 0; // 4
    virtual HRESULT __stdcall GetPrivateData(const void*, void*, DWORD*) = 0;           // 5
    virtual HRESULT __stdcall FreePrivateData(const void*) = 0;                         // 6
    virtual DWORD __stdcall SetPriority(DWORD priority) = 0;                            // 7
    virtual DWORD __stdcall GetPriority() = 0;                                          // 8
    virtual void __stdcall PreLoad() = 0;                                               // 9
    virtual int __stdcall GetType() = 0;                                                // 10
    virtual DWORD __stdcall SetLOD(DWORD lod) = 0;                                      // 11
    virtual DWORD __stdcall GetLOD() = 0;                                               // 12
    virtual DWORD __stdcall GetLevelCount() = 0;                                        // 13
    virtual HRESULT __stdcall GetLevelDesc(UINT level, void* desc) = 0;                 // 14
    virtual HRESULT __stdcall GetSurfaceLevel(UINT level, IDirect3DSurface8** surface) = 0; // 15
    virtual HRESULT __stdcall LockRect(UINT level, _D3DLOCKED_RECT* locked, const tagRECT* rect, DWORD flags) = 0; // 16
    virtual HRESULT __stdcall UnlockRect(UINT level) = 0;                               // 17
    virtual HRESULT __stdcall AddDirtyRect(const tagRECT* rect) = 0;                    // 18
};

struct IDirect3DIndexBuffer8
{
    virtual HRESULT __stdcall QueryInterface(const void* iid, void** object) = 0;       // 0
    virtual unsigned long __stdcall AddRef() = 0;                                       // 1
    virtual unsigned long __stdcall Release() = 0;                                      // 2
    virtual HRESULT __stdcall GetDevice(IDirect3DDevice8** device) = 0;                 // 3
    virtual HRESULT __stdcall SetPrivateData(const void*, const void*, DWORD, DWORD) = 0; // 4
    virtual HRESULT __stdcall GetPrivateData(const void*, void*, DWORD*) = 0;           // 5
    virtual HRESULT __stdcall FreePrivateData(const void*) = 0;                         // 6
    virtual DWORD __stdcall SetPriority(DWORD priority) = 0;                            // 7
    virtual DWORD __stdcall GetPriority() = 0;                                          // 8
    virtual void __stdcall PreLoad() = 0;                                               // 9
    virtual int __stdcall GetType() = 0;                                                // 10
    virtual HRESULT __stdcall Lock(UINT offset, UINT size, unsigned char** data, DWORD flags) = 0; // 11
    virtual HRESULT __stdcall Unlock() = 0;                                             // 12
    virtual HRESULT __stdcall GetDesc(void* desc) = 0;                                  // 13
};

struct IDirect3DVertexBuffer8
{
    virtual HRESULT __stdcall QueryInterface(const void* iid, void** object) = 0;       // 0
    virtual unsigned long __stdcall AddRef() = 0;                                       // 1
    virtual unsigned long __stdcall Release() = 0;                                      // 2
    virtual HRESULT __stdcall GetDevice(IDirect3DDevice8** device) = 0;                 // 3
    virtual HRESULT __stdcall SetPrivateData(const void*, const void*, DWORD, DWORD) = 0; // 4
    virtual HRESULT __stdcall GetPrivateData(const void*, void*, DWORD*) = 0;           // 5
    virtual HRESULT __stdcall FreePrivateData(const void*) = 0;                         // 6
    virtual DWORD __stdcall SetPriority(DWORD priority) = 0;                            // 7
    virtual DWORD __stdcall GetPriority() = 0;                                          // 8
    virtual void __stdcall PreLoad() = 0;                                               // 9
    virtual int __stdcall GetType() = 0;                                                // 10
    virtual HRESULT __stdcall Lock(UINT offset, UINT size, unsigned char** data, DWORD flags) = 0; // 11
    virtual HRESULT __stdcall Unlock() = 0;                                             // 12
    virtual HRESULT __stdcall GetDesc(void* desc) = 0;                                  // 13
};


// original macro: the unconditional "if (p)" inside an already tested "if (p)" shows up the same way in
// TRenderD3DInterface::DestroyDisplay and in both block DestroyHAL functions (the usual DirectX sample macro).
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); } }

#endif
