// Toshi::TMatrix44ID - kernel-internal declaration. A TMatrix44 that carries an integer ID (+0x40, object size 0x44).
// The copy constructor and operator= are the compiler-generated ones (the kernel exports them).
#ifndef TKERNELMATRIXID_H
#define TKERNELMATRIXID_H
#include "TVector.h"

namespace Toshi {

class __declspec(dllexport) TMatrix44ID : public TMatrix44
{
public:
    TMatrix44ID();
    unsigned int GetID();
    void SetID(unsigned int id);

private:
    unsigned int m_uID;     // +0x40
};

} // namespace Toshi
#endif
