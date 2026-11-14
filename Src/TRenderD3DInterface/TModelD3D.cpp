// Toshi::TModelD3D - creation, loading and deletion.
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TModelD3D.h"

namespace Toshi {

bool TModelD3D::Create(const char* name, bool load)
{
    m_uiFlags |= FLAG_CREATED;
    if (load == true)
    {
        if (!Load(name))
        {
            m_uiFlags &= ~FLAG_CREATED;
            return false;
        }
    }
    return true;
}

void TModelD3D::Delete()
{
    Unload();
    delete this;
}

bool TModelD3D::Load(const char* name)
{
    if (IsLoaded() == true)
        return true;
    if (!LoadTMD(name))
        return false;
    m_uiFlags |= FLAG_LOADED;
    return true;
}

TModelD3D::~TModelD3D()
{
}

} // namespace Toshi
