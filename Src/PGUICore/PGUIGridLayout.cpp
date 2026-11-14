// PGUIGridLayout accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIGridLayout.h"
#include "PPropertyValue.h"
#include "TNewDelete.h"

static inline const int& Min(const int& a, const int& b)
{
    return (a < b) ? a : b;
}

static inline const int& Max(const int& a, const int& b)
{
    return (a > b) ? a : b;
}

int PGUIGridLayout::GetNumCOls() const
{
    return m_sNumCols;
}

int PGUIGridLayout::GetNumRows() const
{
    return m_sNumRows;
}

void PGUIGridLayout::SetNumRows(int rows)
{
    m_sNumRows = rows;
}

void PGUIGridLayout::SetNumCols(int columns)
{
    m_sNumCols = columns;
}

PPropertyValue PGUIGridLayout::Get_rows_property() const
{
    return PPropertyValue((int)m_sNumRows);
}

PPropertyValue PGUIGridLayout::Get_columns_property() const
{
    return PPropertyValue((int)m_sNumCols);
}

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIGridLayout::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIGridLayout::ms_oPropertySet;
Toshi::TGUILayoutInfo* PGUIGridLayout::ms_layout_info;

PGUIGridLayout::PGUIGridLayout()
{
    m_sNumRows = 1;
    m_sNumCols = 1;
    m_pLayoutInfo = ms_layout_info;
}

PGUIGridLayout::PGUIGridLayout(const PGUIGridLayout& other)
    : PGUILayoutManager(other)
{
    m_sNumRows = other.m_sNumRows;
    m_sNumCols = other.m_sNumCols;
    m_pLayoutInfo = ms_layout_info;
}

PGUIGridLayout* PGUIGridLayout::Clone() const
{
    return new (tmalloc(sizeof(PGUIGridLayout), 0, -1)) PGUIGridLayout(*this);
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIGridLayout::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIGridLayout::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUIGridLayout::Serialise(PProperties* properties)
{
    if (!TGUILayoutManager::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIGridLayout::Deserialise(const PProperties* properties)
{
    if (!TGUILayoutManager::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIGridLayout::Val_columns_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    return value.GetInteger() > 0;
}

void PGUIGridLayout::Set_columns_property(const PPropertyValue& value)
{
    m_sNumCols = Min(Max(value.GetInteger(), 1), 16);
}

void PGUIGridLayout::Set_rows_property(const PPropertyValue& value)
{
    m_sNumRows = Min(Max(value.GetInteger(), 1), 64);
}
