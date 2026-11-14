// Z:\Toshi\Source\TGUI\TGUIPropertySpec.cpp - GetName is still to do.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TSystem.h"
#include "TGUIPropertySpec.h"
#include "PPropertyValue.h"

namespace Toshi {

bool TGUIPropertySpec::operator==(const TGUIPropertySpec& other)
{
    return m_oName == other.m_oName;
}

int TGUIPropertySpec::GetSortHint() const
{
    return m_iSortHint;
}

const TClass* TGUIPropertySpec::GetBaseClass() const
{
    return m_pBaseClass;
}

bool TGUIPropertySpec::IsClassName() const
{
    return m_iKind == KIND_CLASS_NAME;
}

const TPCString& TGUIPropertySpec::GetEnumName(int index) const
{
    return m_aEnumNames[index];
}

int TGUIPropertySpec::GetEnumValue(const TPCString& name) const
{
    for (int i = 0; i < m_iEnumCount; i++) {
        if (m_aEnumNames[i] == name) {
            return i;
        }
    }
    return -1;
}

int TGUIPropertySpec::GetEnumCount() const
{
    if (m_iKind == KIND_ENUMERATION) {
        return m_iEnumCount;
    }
    return 0;
}

bool TGUIPropertySpec::IsEnumerated() const
{
    if (m_iKind != KIND_ENUMERATION) {
        return false;
    }
    if (m_iEnumCount > 0) {
        return true;
    }
    return false;
}

bool TGUIPropertySpec::AllowsAutoInstall() const
{
    return m_bAutoInstall;
}

void TGUIPropertySpec::SetType(const TClass* type)
{
    m_pType = type;
}

const TClass* TGUIPropertySpec::GetType() const
{
    return m_pType;
}

void TGUIPropertySpec::SetName(const TPCString& name)
{
    m_oName = name;
}

TGUIPropertySpec::TGUIPropertySpec(const TPCString& name)
    : m_pType(PPropertyValue::TYPE_UNDEF), m_oName(name), m_bAutoInstall(false), m_pSourceClass(0), m_iSortHint(0), m_iKind(0)
{
}

TGUIPropertySpec::~TGUIPropertySpec()
{
    if (m_iKind == KIND_ENUMERATION) {
        if (m_aEnumNames != 0) {
            delete[] m_aEnumNames;
        }
    }
}

// Only an enumeration copies its names and only a class-name property its base class: the kind of the
// target decides which, and is not copied itself.
TGUIPropertySpec& TGUIPropertySpec::operator=(const TGUIPropertySpec& other)
{
    m_pType = other.m_pType;
    m_oName = other.m_oName;
    m_bAutoInstall = other.m_bAutoInstall;
    m_pSourceClass = other.m_pSourceClass;
    m_iSortHint = other.m_iSortHint;
    if (m_iKind == KIND_ENUMERATION) {
        m_iEnumCount = other.m_iEnumCount;
        if (m_aEnumNames != 0) {
            delete[] m_aEnumNames;
        }
        if (other.m_aEnumNames == 0) {
            m_aEnumNames = 0;
        } else {
            m_aEnumNames = new TPCString[m_iEnumCount];
            for (int i = 0; i < m_iEnumCount; i++) {
                m_aEnumNames[i] = other.m_aEnumNames[i];
            }
        }
    } else if (m_iKind == KIND_CLASS_NAME) {
        m_pBaseClass = other.m_pBaseClass;
    }
    return *this;
}

TGUIPropertySpec::TGUIPropertySpec(const TPCString& name, const TClass* type, bool autoInstall, const TClass* sourceClass,
                                   int sortHint)
    : m_pType(type), m_oName(name), m_bAutoInstall(autoInstall), m_pSourceClass(sourceClass), m_iSortHint(sortHint), m_iKind(0)
{
}

TGUIPropertySpec::TGUIPropertySpec(const TPCString& name, const TClass* type, bool autoInstall, const TClass* sourceClass,
                                   int sortHint, const TClass* baseClass)
    : m_pType(type), m_oName(name), m_bAutoInstall(autoInstall), m_pSourceClass(sourceClass), m_iSortHint(sortHint),
      m_iKind(KIND_CLASS_NAME)
{
    m_pBaseClass = baseClass;
}

TGUIPropertySpec::TGUIPropertySpec(const TPCString& name, const TClass* type, bool autoInstall, const TClass* sourceClass,
                                   int sortHint, int enumCount, const char* const* enumNames)
    : m_pType(type), m_oName(name), m_bAutoInstall(autoInstall), m_pSourceClass(sourceClass), m_iSortHint(sortHint),
      m_iKind(KIND_ENUMERATION)
{
    m_iEnumCount = enumCount;
    m_aEnumNames = new TPCString[enumCount];
    for (int i = 0; i < m_iEnumCount; i++) {
        m_aEnumNames[i] = TSystem::GetCStringPool()->Get(enumNames[i]);
    }
}

// The sort hint is not copied.
TGUIPropertySpec::TGUIPropertySpec(const TGUIPropertySpec& other)
    : m_pType(other.m_pType), m_oName(other.m_oName), m_bAutoInstall(other.m_bAutoInstall),
      m_pSourceClass(other.m_pSourceClass), m_iKind(other.m_iKind)
{
    if (m_iKind == KIND_ENUMERATION) {
        m_iEnumCount = other.m_iEnumCount;
        m_aEnumNames = new TPCString[m_iEnumCount];
        for (int i = 0; i < m_iEnumCount; i++) {
            m_aEnumNames[i] = other.m_aEnumNames[i];
        }
    } else if (m_iKind == KIND_CLASS_NAME) {
        m_pBaseClass = other.m_pBaseClass;
    }
}

} // namespace Toshi
