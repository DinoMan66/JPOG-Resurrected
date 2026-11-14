// Z:\Toshi\Source\TKernel\TLString.cpp - the reference-counted handle to a localised string.
#define TOSHI_API __declspec(dllexport)
#define TOSHI_EXPORT_LSTRING
#include "TKernelLString.h"

namespace Toshi {

TLString::TLString()
{
    m_pData = 0;
}

TLString::TLString(TLocalisedString* data)
{
    m_pData = data;
    if (m_pData) {
        m_pData->m_iRefCount++;
    }
}

TLString::TLString(const TLString& other)
{
    m_pData = 0;
    if (other.m_pData) {
        m_pData = other.m_pData;
        if (m_pData) {
            m_pData->m_iRefCount++;
        }
    }
}

TLString::~TLString()
{
    if (m_pData) {
        Release();
    }
}

void TLString::Release()
{
    if (m_pData) {
        if (--m_pData->m_iRefCount == 0) {
            m_pData->Delete();
        }
    }
    m_pData = 0;
}

TLString& TLString::operator=(const TLString& other)
{
    TLocalisedString* data = other.m_pData;
    if (m_pData != data) {
        if (m_pData) {
            if (--m_pData->m_iRefCount == 0) {
                m_pData->Delete();
            }
        }
        m_pData = other.m_pData;
        if (m_pData) {
            m_pData->m_iRefCount++;
        }
    }
    return *this;
}

bool TLString::operator<(const TLString& other) const
{
    return (m_pData - other.m_pData) < 0;
}

bool TLString::operator!=(const TLString& other) const
{
    return m_pData != other.m_pData;
}

bool TLString::operator==(const TLString& other) const
{
    return m_pData == other.m_pData;
}

int TLString::Compare(const TLString& other) const
{
    return m_pData - other.m_pData;
}

bool TLString::IsTemporary() const
{
    return m_pData ? m_pData->IsTemporary() : false;
}

TLocale* TLString::GetLocale() const
{
    return m_pData ? m_pData->m_pLocale : 0;
}

TLocalisedString::TLocalisedString()
    : m_iRefCount(0), m_iIndex(-1), m_pLocale(0)
{
}

TLocalisedString::TLocalisedString(int index, TPCString identifier, TLocale* locale)
    : m_iRefCount(0), m_iIndex(index), m_oIdentifier(identifier), m_pLocale(locale)
{
}

TLocalisedString::~TLocalisedString()
{
    if (m_pLocale) {
        m_pLocale->Remove(*this);
    }
}

const TPWString& TLocalisedString::GetLocalisedString() const
{
    return m_oString;
}

const TPCString& TLocalisedString::GetIdentifierString() const
{
    return m_oIdentifier;
}

int TLocalisedString::GetIdentifierInt() const
{
    return m_iIndex;
}

} // namespace Toshi
