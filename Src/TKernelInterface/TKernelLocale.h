// Toshi locale classes - kernel-internal declarations. Only what has been reconstructed so far
// (TLocale, TLocaleInfo and TLocalisedString are still to do: see the import stubs in include\TLString.h).
#ifndef TKERNELLOCALE_H
#define TKERNELLOCALE_H

#include "TPString.h"

namespace Toshi {

class TLocalisedString;

// One available language: its number, name and file name, and how its text is wrapped.
class TLocaleInfo
{
public:
    enum WordBreakStyle
    {
        WORDBREAK_DEFAULT = 0,
        WORDBREAK_JAPANESE = 1
    };

    TOSHI_API TLocaleInfo(int index, const TPCString& name, const TPCString& fileName);
    TOSHI_API TLocaleInfo(const TLocaleInfo& other);
    TOSHI_API ~TLocaleInfo();
    TOSHI_API TLocaleInfo& operator=(const TLocaleInfo& other);
    TOSHI_API TPCString GetName() const;
    TOSHI_API TPCString GetFileName() const;
    TOSHI_API int GetIndex() const;
    TOSHI_API WordBreakStyle GetWordBreakStyle() const;

private:
    /* 0x00 */ int m_iIndex;
    /* 0x04 */ TPCString m_oName;
    /* 0x08 */ TPCString m_oFileName;
    /* 0x0C */ WordBreakStyle m_eWordBreakStyle;
};

// The active locale (only the constructor so far).
class TLocale
{
public:
    TOSHI_API TLocale();
    TOSHI_API TLocaleInfo* GetCurrentLocaleInfo();

private:
    friend class TLocalisedString;
    void Remove(TLocalisedString& string);

    /* 0x00 */ int m_unk00;
    /* 0x04 */ int m_unk04;
    /* 0x08 */ int m_unk08;
    /* 0x0C */ int m_unk0C;
    /* 0x10 */ int m_unk10;
    /* 0x14 */ int m_unk14;
    /* 0x18 */ int m_unk18;
    /* 0x1C */ int m_unk1C;
    /* 0x20 */ int m_unk20;
    /* 0x24 */ int m_unk24;
    /* 0x28 */ int m_unk28;
    /* 0x2C */ int m_unk2C;
    /* 0x30 */ int m_unk30;
    /* 0x34 */ int m_unk34;
    /* 0x38 */ int m_unk38;
    /* 0x3C */ int m_unk3C;
    /* 0x40 */ int m_unk40;
    /* 0x44 */ int m_unk44;
    /* 0x48 */ TLocaleInfo* m_pCurrentLocaleInfo;
};

// Sent when the active locale changes. operator= is the compiler-generated one.
class __declspec(dllexport) TLocaleChangeEvent
{
public:
    TLocaleChangeEvent(TLocale* locale, TLocaleInfo* info);

private:
    TLocale* m_pLocale;         // +0x00
    TLocaleInfo* m_pLocaleInfo; // +0x04
};

} // namespace Toshi
#endif
