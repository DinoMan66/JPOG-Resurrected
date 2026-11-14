// Toshi localised strings - kernel-internal declarations. Only what has been reconstructed so far.
// A TLString is a 4-byte handle to a reference-counted TLocalisedString (count at +0).
#ifndef TKERNELLSTRING_H
#define TKERNELLSTRING_H
#include "TPString.h"
#include "TKernelLocale.h"

namespace Toshi {

// TLString.cpp defines TOSHI_EXPORT_LSTRING: the kernel exports both classes as a whole.
#ifdef TOSHI_EXPORT_LSTRING
#define TOSHI_LSTRING_CLASS __declspec(dllexport)
#else
#define TOSHI_LSTRING_CLASS
#endif

class TLString;

class TOSHI_LSTRING_CLASS TLocalisedString
{
    friend class TLString;
public:
    TOSHI_API bool IsTemporary() const;
    TOSHI_API const TPWString& GetLocalisedString() const;
    TOSHI_API const TPCString& GetIdentifierString() const;
    TOSHI_API int GetIdentifierInt() const;
    TOSHI_FREELIST_DECLARE()

private:
    TOSHI_API TLocalisedString();
    TOSHI_API TLocalisedString(int index, TPCString identifier, TLocale* locale);
    ~TLocalisedString();
    TOSHI_API void Delete();

    /* 0x00 */ int m_iRefCount;
    /* 0x04 */ int m_iIndex;
    /* 0x08 */ TPCString m_oIdentifier;
    /* 0x0C */ TPWString m_oString;
    /* 0x10 */ TLocale* m_pLocale;
};

class TOSHI_LSTRING_CLASS TLString
{
public:
    TOSHI_API TLString();
    TOSHI_API TLString(TLocalisedString* data);
    TOSHI_API TLString(const TLString& other);
    TOSHI_API ~TLString();
    TOSHI_API TLString& operator=(const TLString& other);
    TOSHI_API bool operator<(const TLString& other) const;
    TOSHI_API bool operator!=(const TLString& other) const;
    TOSHI_API bool operator==(const TLString& other) const;
    TOSHI_API int Compare(const TLString& other) const;
    TOSHI_API bool IsTemporary() const;
    TOSHI_API TLocale* GetLocale() const;

    // An empty string when there is no data (the statics ms_wsEmpty / ms_csEmpty are kernel exports).
    const TWString& operator*() const
    {
        if (!m_pData) return ms_wsEmpty;
        return *m_pData->m_oString;
    }
    const TWString* operator->() const
    {
        if (!m_pData) return &ms_wsEmpty;
        return m_pData->m_oString;
    }
    operator const TWString*() const
    {
        if (!m_pData) return &ms_wsEmpty;
        return m_pData->m_oString;
    }
    const TWString& GetLocalisedString() const
    {
        if (!m_pData) return ms_wsEmpty;
        return *m_pData->m_oString;
    }
    const TCString& GetIdentifierString() const
    {
        if (!m_pData) return ms_csEmpty;
        return *m_pData->m_oIdentifier;
    }
    TWString& GetVolatileString() const { return m_pData->m_oString.GetVolatileWString(); }

    TOSHI_API static const TWString ms_wsEmpty;
    TOSHI_API static const TCString ms_csEmpty;

private:
    void Release();

    TLocalisedString* m_pData;
};

} // namespace Toshi
#endif
