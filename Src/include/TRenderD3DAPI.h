// Export macro for TRenderD3DInterface.dll (Direct3D renderer). Every class is exported whole.
#ifndef TRENDERD3DAPI_H
#define TRENDERD3DAPI_H
#ifdef TRENDERD3DINTERFACE_EXPORTS
#define TRENDERD3D_API __declspec(dllexport)
#else
#define TRENDERD3D_API __declspec(dllimport)
#endif
#endif
