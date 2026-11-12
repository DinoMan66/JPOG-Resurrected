// Toshi locale classes - kernel-internal declarations. Only what has been reconstructed so far
// (TLocale, TLocaleInfo and TLocalisedString are still to do: see the import stubs in include\TLString.h).
#ifndef TKERNELLOCALE_H
#define TKERNELLOCALE_H

namespace Toshi {

class TLocale;
class TLocaleInfo;

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
