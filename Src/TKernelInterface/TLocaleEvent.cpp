// Z:\Toshi\Source\TKernel\TLocale.cpp - TLocaleChangeEvent only.
#define TOSHI_API __declspec(dllexport)
#include "TKernelLocale.h"

namespace Toshi {

TLocaleChangeEvent::TLocaleChangeEvent(TLocale* locale, TLocaleInfo* info)
{
    m_pLocale = locale;
    m_pLocaleInfo = info;
}

} // namespace Toshi
