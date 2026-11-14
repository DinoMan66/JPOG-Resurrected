// PGUIListItem accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIListItem.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIListItem::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIListItem::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUIListItem::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIListItem::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

bool PGUIListItem::Deserialise(const PProperties* properties)
{
    if (!TGUIWidget::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIListItem::Serialise(PProperties* properties)
{
    if (!TGUIWidget::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIListItem::AcceptsFocus() const
{
    return true;
}

void PGUIListItem::SetIndex(int index)
{
    m_iIndex = index;
}

int PGUIListItem::GetIndex() const
{
    return m_iIndex;
}

void PGUIListItem::SetData(PGUIItemData* data)
{
    m_pData = data;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIListItem::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIListItem::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

void PGUIListItem::Pack()
{
    if (GetStyle() != 0)
    {
        int width = GetWidth();
        int height = GetHeight();

        SetComponentBBox(0, 0, 0, width, height);
        SetComponentBBox(1, 0, 0, width, height);
    }

    SetValidated(true);
}

PGUIListItem::PGUIListItem(const PGUIListItem& other)
    : Toshi::TGUIWidget(other)
{
}

PGUIListItem* PGUIListItem::Clone() const
{
    return new PGUIListItem(*this);
}
