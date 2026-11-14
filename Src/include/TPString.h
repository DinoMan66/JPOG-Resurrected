// Toshi pooled strings (stubs; the real classes live in TKernelInterface.dll).
// Imports seen in PPropertyParser.dll:
//   ?Delete@TPooledCString@Toshi@@AAEXXZ            private: void Delete()
//   ?Delete@TPooledWString@Toshi@@AAEXXZ
//   ?ms_sEmpty@TPCString@Toshi@@2VTCString@2@B      public: static const TCString ms_sEmpty
//   ?ms_sEmpty@TPWString@Toshi@@2VTWString@2@B
//   ?Compare@TPCString@Toshi@@QBEHABV12@@Z          int Compare(const TPCString&) const
//   ?Get@TCStringPool@Toshi@@QAE?AVTPCString@2@ABVTCString@2@@Z
//   ??HToshi@@YG?AVTCString@0@ABV10@ABVTPCString@0@@Z   TCString operator+(const TCString&, const TPCString&)
// A TPCString/TPWString is a 4-byte handle to a reference-counted pooled string
// (count at +0, the string object at +4). Everything except Compare is inline: the binary
// has the reference counting written out at each use, and ICC emits local copies of the
// (not inlined) assignment and destructor in each object file.
#ifndef TPSTRING_H
#define TPSTRING_H
#include "TMemory.h"
#include "TCString.h"
#include "TFreeList.h"
#ifdef TOSHI_KERNEL_BUILD
#define TOSHI_EXPORT __declspec(dllexport)
#else
#define TOSHI_EXPORT
#endif

namespace Toshi {

class TPCString;
class TPWString;
class TCStringPool;
class TWStringPool;

// The kernel exports the whole pooled-string handle classes. TPCString.cpp and TPWString.cpp define
// TOSHI_EXPORT_PSTRING so that those translation units emit every member; everybody else keeps them inline.
#ifdef TOSHI_EXPORT_PSTRING
#define TOSHI_PSTRING_CLASS __declspec(dllexport)
#else
#define TOSHI_PSTRING_CLASS
#endif

class TOSHI_PSTRING_CLASS TPooledCString
{
    friend class TPCString;
    friend class TCStringPool;
public:
    int      m_iRefCount;                       // +0
    TCString m_oString;                         // +4
    TCStringPool* m_pStringPool;                // +0xC (read by TPCString::GetStringPool)
    TOSHI_FREELIST_DECLARE()
private:
    TPooledCString(const char* s, TCStringPool* pool)
        : m_iRefCount(0), m_oString(s), m_pStringPool(pool)
    {
    }
    ~TPooledCString();
    TOSHI_API void Delete();
};

class TOSHI_PSTRING_CLASS TPooledWString
{
    friend class TPWString;
    friend class TWStringPool;
public:
    int      m_iRefCount;                       // +0
    TWString m_oString;                         // +4
    TWStringPool* m_pStringPool;                // +0xC (read by TPWString::GetStringPool)
    TOSHI_FREELIST_DECLARE()
private:
    TPooledWString(const TWChar* s, TWStringPool* pool)
        : m_iRefCount(0), m_oString(s), m_pStringPool(pool)
    {
    }
    ~TPooledWString();
    TOSHI_API void Delete();
};

class TOSHI_PSTRING_CLASS TPCString
{
    friend class TCStringPool;
public:
    TOSHI_EXPORT TPCString() { m_pPooled = 0; }
    TPCString(const TPCString& o)
    {
        // clear first, then copy: matches PPropertyName's copy ctors (experiment D, round 16)
        m_pPooled = 0;
        if (o.m_pPooled)
        {
            m_pPooled = o.m_pPooled;
            if (m_pPooled) m_pPooled->m_iRefCount++;
        }
    }
    ~TPCString();                                   // non-inline: see MATCHING_NOTES #21
    TPCString& operator=(const TPCString& o);
    bool operator==(const TPCString& o) const { return m_pPooled == o.m_pPooled; }
    bool operator!=(const TPCString& o) const { return m_pPooled != o.m_pPooled; }
    bool operator<(const TPCString& o) const { return Compare(o) < 0; }
    const TCString& GetCString() const
    {
        if (m_pPooled) return m_pPooled->m_oString;
        return ms_sEmpty;
    }
    TCString& GetVolatileCString() const { return m_pPooled->m_oString; }
    TCStringPool* GetStringPool() const { return m_pPooled->m_pStringPool; }
    // the kernel also exports operator* and operator const TCString* (??D / ??B)
    const TCString& operator*() const
    {
        if (!m_pPooled) return ms_sEmpty;
        return m_pPooled->m_oString;
    }
    operator const TCString*() const
    {
        if (!m_pPooled) return &ms_sEmpty;
        return &m_pPooled->m_oString;
    }
    const TCString* operator->() const
    {
        if (!m_pPooled) return &ms_sEmpty;
        return &m_pPooled->m_oString;
    }
    bool IsEmpty() const
    {
        if (m_pPooled) return m_pPooled->m_oString.IsEmpty();
        return true;
    }

    TOSHI_API int Compare(const TPCString& o) const;
    TOSHI_API static const TCString ms_sEmpty;

private:
    TPCString(TPooledCString* pooled)
    {
        m_pPooled = pooled;
        if (m_pPooled) m_pPooled->m_iRefCount++;
    }
    void Release()
    {
        if (m_pPooled)
        {
            if (--m_pPooled->m_iRefCount == 0)
                m_pPooled->Delete();
        }
        m_pPooled = 0;
    }
    TPooledCString* m_pPooled;
};
// These are defined here WITHOUT `inline` on purpose: the original object code calls a local
// out-of-line copy of them in each translation unit, which ICC only produces for non-inline
// functions (MATCHING_NOTES #21). Each .cpp is compiled and compared on its own; a linkable
// build will need these turned into per-file (static) copies - still to do.
// TPCString's destructor is never inlined. The assignments (and the TPWString/TLString
// destructors) were inlined in some of the original translation units and not in others; a
// .cpp that needs the out-of-line form defines TOSHI_STRING_ASSIGN_NOT_INLINED before its
// includes (PPropertyName, PPropertyReader and PPropertyValue do).
#ifdef TOSHI_STRING_ASSIGN_NOT_INLINED
#define TPCSTRING_ASSIGN_INLINE
#define TPWSTRING_INLINE
#else
#define TPCSTRING_ASSIGN_INLINE inline
#define TPWSTRING_INLINE inline
#endif
TPCString::~TPCString()
{
    if (m_pPooled) Release();
}
TPCSTRING_ASSIGN_INLINE TPCString& TPCString::operator=(const TPCString& o)
{
    TPooledCString* p = o.m_pPooled;
    if (m_pPooled != p)
    {
        if (m_pPooled)
        {
            if (--m_pPooled->m_iRefCount == 0)
                m_pPooled->Delete();
        }
        m_pPooled = o.m_pPooled;
        if (m_pPooled) m_pPooled->m_iRefCount++;
    }
    return *this;
}

class TOSHI_PSTRING_CLASS TPWString
{
    friend class TWStringPool;
public:
    TOSHI_EXPORT TPWString() { m_pPooled = 0; }
    TPWString(const TPWString& o)
    {
        // clear first, then copy: matches PPropertyName's copy ctors (experiment D, round 16)
        m_pPooled = 0;
        if (o.m_pPooled)
        {
            m_pPooled = o.m_pPooled;
            if (m_pPooled) m_pPooled->m_iRefCount++;
        }
    }
    ~TPWString();
    TPWString& operator=(const TPWString& o);
    bool operator==(const TPWString& o) const { return m_pPooled == o.m_pPooled; }
    bool operator!=(const TPWString& o) const { return m_pPooled != o.m_pPooled; }
    bool operator<(const TPWString& o) const { return Compare(o) < 0; }
    const TWString& GetWString() const
    {
        return m_pPooled == 0 ? ms_sEmpty : m_pPooled->m_oString;
    }
    TWString& GetVolatileWString() const { return m_pPooled->m_oString; }
    TWStringPool* GetStringPool() const { return m_pPooled->m_pStringPool; }
    // the kernel also exports operator* and operator const TWString* (??D / ??B)
    const TWString& operator*() const
    {
        if (!m_pPooled) return ms_sEmpty;
        return m_pPooled->m_oString;
    }
    operator const TWString*() const
    {
        if (!m_pPooled) return &ms_sEmpty;
        return &m_pPooled->m_oString;
    }
    const TWString* operator->() const
    {
        if (!m_pPooled) return &ms_sEmpty;
        return &m_pPooled->m_oString;
    }
    bool IsEmpty() const { return GetWString().IsEmpty(); }

    TOSHI_API int Compare(const TPWString& o) const;
    TOSHI_API static const TWString ms_sEmpty;

private:
    TPWString(TPooledWString* pooled)
    {
        m_pPooled = pooled;
        if (m_pPooled) m_pPooled->m_iRefCount++;
    }
    void Release()
    {
        if (m_pPooled)
        {
            if (--m_pPooled->m_iRefCount == 0)
                m_pPooled->Delete();
        }
        m_pPooled = 0;
    }
    TPooledWString* m_pPooled;
};
// Concatenation with a pooled string (the text of a missing handle is the empty string).
TOSHI_API TWString __stdcall operator+(const TWString& a, const TPWString& b);
TPWSTRING_INLINE TPWString::~TPWString()
{
    if (m_pPooled) Release();
}
TPWSTRING_INLINE TPWString& TPWString::operator=(const TPWString& o)
{
    TPooledWString* p = o.m_pPooled;
    if (m_pPooled != p)
    {
        if (m_pPooled)
        {
            if (--m_pPooled->m_iRefCount == 0)
                m_pPooled->Delete();
        }
        m_pPooled = o.m_pPooled;
        if (m_pPooled) m_pPooled->m_iRefCount++;
    }
    return *this;
}

TOSHI_API TCString __stdcall operator+(const TCString& a, const TPCString& b);

class TCStringPool
{
public:
    TOSHI_API TCStringPool(const char* name, int a, int b);
    TOSHI_API TCStringPool(int a, int b);
    TOSHI_API TPCString Get(const TCString& s);
    TOSHI_API TPCString Get(int i);
    TOSHI_API TPCString Get(const char* s);
    TOSHI_API TPCString GetOptional(const TCString& s);
    TOSHI_API TPCString GetOptional(int i);
    TOSHI_API TPCString GetOptional(const char* s);
    TOSHI_API TPCString GetVolatile(const TCString& s);
    TOSHI_API TPCString GetVolatile(int i);
    TOSHI_API TPCString GetVolatile(const char* s);
    TOSHI_API bool IsPresent(const TCString& s);
    TOSHI_API bool IsPresent(int i);
    TOSHI_API bool IsPresent(const char* s);
    TOSHI_API bool WriteFile(const char* name);
    TOSHI_API void Dump() const;

protected:
    TOSHI_API bool ReadFile(const char* name);
    TOSHI_API void Remove(TPooledCString& pooled);

private:
    friend class TPooledCString;
    struct Entry
    {
        int m_unk0;
        int m_unk4;
    };

    /* 0x00 */ int m_unk00;
    /* 0x04 */ int m_unk04;
    /* 0x08 */ int m_unk08;
    /* 0x0C */ Entry* m_unk0C;
};

class TWStringPool
{
public:
    TOSHI_API TWStringPool();
    TOSHI_API TPWString Get(const TWString& s);
    TOSHI_API TPWString Get(const TWChar* s);
    TOSHI_API TPWString Get(int i);
    TOSHI_API TPWString GetVolatile(const TWString& s);
    TOSHI_API TPWString GetVolatile(const TWChar* s);
    TOSHI_API TPWString GetVolatile(int i);

protected:
    TOSHI_API void Remove(TPooledWString& pooled);

private:
    friend class TPooledWString;
    struct Entry
    {
        int m_unk0;
        int m_unk4;
    };

    /* 0x00 */ int m_unk00;
    /* 0x04 */ int m_unk04;
    /* 0x08 */ int m_unk08;
    /* 0x0C */ Entry* m_unk0C;
};

// A pooled string unregisters itself from the pool that created it.
inline TPooledCString::~TPooledCString()
{
    if (m_pStringPool) m_pStringPool->Remove(*this);
}
inline TPooledWString::~TPooledWString()
{
    if (m_pStringPool) m_pStringPool->Remove(*this);
}

} // namespace Toshi
#endif
