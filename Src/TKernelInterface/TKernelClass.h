// TClass - kernel-internal declaration (importing modules use include/TObject.h, which hides the layout).
// Layout from the accessors: name +0, create +4, create-in-place +8, initialise +0xC, deinitialise +0x10,
// parent +0x14, version +0x20 (minor byte, major word at +0x22), static-initialised flag +0x24; object size 0x28.
#ifndef TKERNELCLASS_H
#define TKERNELCLASS_H

namespace Toshi {

class TObject;

class __declspec(dllexport) TClass
{
public:
    typedef TObject* (__stdcall *CreateObjectFn)();
    typedef TObject* (__stdcall *CreateObjectInPlaceFn)(void*);
    typedef void     (__stdcall *StaticFn)();

    TClass(const char* name, TClass* parent, CreateObjectFn create, CreateObjectInPlaceFn createInPlace,
           StaticFn initialise, StaticFn deinitialise, unsigned int version);
    ~TClass();

    const char* GetName() const;
    const TClass* GetParent() const;
    unsigned int GetVersion() const;
    unsigned short GetVersionMajor() const;
    unsigned short GetVersionMinor() const;
    bool IsExactly(const TClass& other) const;
    bool IsStaticInitialised() const;
    bool DetachClassFromParent();
    void InitialiseStatic();
    void DeinitialiseStatic();
    TObject* CreateObject() const;
    TObject* CreateObjectInPlace(void* memory) const;
    bool IsA(const TClass& other) const;
    bool IsAttached() const;
    bool AttachClassToParent();
    bool operator==(const TClass& other) const;
    static const TClass* __stdcall Find(const char* name, const TClass* parent);

private:
    const char* m_pName;                    // +0x00
    CreateObjectFn m_pCreate;               // +0x04
    CreateObjectInPlaceFn m_pCreateInPlace; // +0x08
    StaticFn m_pInitialise;                 // +0x0C
    StaticFn m_pDeinitialise;               // +0x10
    TClass* m_pParent;                      // +0x14
    TClass* m_pNextSibling;                 // +0x18  (class tree: sibling list under the parent)
    TClass* m_pFirstChild;                  // +0x1C
    union
    {
        unsigned int m_uVersion;            // +0x20
        struct
        {
            unsigned char m_uVersionMinor;  // +0x20
            unsigned char m_uVersionPad;    // +0x21
            unsigned short m_uVersionMajor; // +0x22
        } m_oParts;
    };
    bool m_bStaticInitialised;              // +0x24

    static const TClass* __stdcall FindRecurse(const char* name, const TClass* cls, bool siblings);
};

} // namespace Toshi
#endif
