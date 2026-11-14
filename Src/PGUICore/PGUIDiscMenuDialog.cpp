// PGUIDiscMenuDialog accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIDiscMenuDialog.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIDiscMenuDialog::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIDiscMenuDialog::ms_oPropertySet;

PGUIDiscMenuDialog::PGUIDiscMenuDialog(const PGUIDiscMenuDialog& other)
    : PGUIMenuDialog(other)
{
    m_unkF4 = 0;
}

PGUIDiscMenuDialog* PGUIDiscMenuDialog::Clone() const
{
    return new PGUIDiscMenuDialog(*this);
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIDiscMenuDialog::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIDiscMenuDialog::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

Toshi::TGUIWidgetInfo* PGUIDiscMenuDialog::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIDiscMenuDialog::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

void PGUIDiscMenuDialog::Pack()
{
    PGUIMenuDialog::Pack();
}

bool PGUIDiscMenuDialog::Serialise(PProperties* properties)
{
    if (!PGUIMenuDialog::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIDiscMenuDialog::Deserialise(const PProperties* properties)
{
    if (!PGUIMenuDialog::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIDiscMenuDialog::OnButtonRelease(Toshi::TInputInterface::InputEvent* event, int doodad)
{
    if (doodad & 0x1E00) {
        return true;
    }
    if (PGUIMenuDialog::OnButtonRelease(event, doodad) == true) {
        return true;
    }
    return false;
}

bool PGUIDiscMenuDialog::OnButtonPress(Toshi::TInputInterface::InputEvent* event, int doodad)
{
    if (doodad & 0x1E00) {
        return true;
    }
    if (PGUIMenuDialog::OnButtonPress(event, doodad) == true) {
        return true;
    }
    return false;
}
