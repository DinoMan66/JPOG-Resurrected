// Toshi::TModelD3D (TRenderD3DInterface.dll, TModelD3D.cpp) - the Direct3D model. It adds no members
// to TModel; the class size stays 0x90.
#ifndef TMODELD3D_H
#define TMODELD3D_H
#include "TModel.h"
#include "TRenderD3DAPI.h"

namespace Toshi {

class TRENDERD3D_API TModelD3D : public TModel
{
public:
    TModelD3D();
    virtual ~TModelD3D();

    virtual bool Create(const char* name, bool load);
    virtual void Delete();
    virtual bool Load(const char* name);
    virtual void Unload();

protected:
    virtual bool LoadTMDHAL(TFile* file);
};

} // namespace Toshi
#endif
