// TObject - kernel-internal declaration (importing modules use include/TObject.h).
// vtable: [0] GetClass  [1] Delete  [2] scalar deleting destructor (exported as ??_7TObject@Toshi@@6B@)
#ifndef TKERNELOBJECT_H
#define TKERNELOBJECT_H
#include "TKernelClass.h"

namespace Toshi {

class __declspec(dllexport) TObject
{
public:
    virtual TClass& GetClass() const;
    virtual void Delete();
    bool IsExactly(const TClass& cls) const;
    bool IsA(const TClass& cls) const;

    static TClass m_sClass;

protected:
    TObject();
    virtual ~TObject();

private:
    TObject& operator=(const TObject&);

    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

} // namespace Toshi
#endif
