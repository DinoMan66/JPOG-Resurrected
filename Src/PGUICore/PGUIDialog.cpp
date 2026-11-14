// PGUIDialog accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIDialog.h"
#include "TGUIScreen.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIDialog::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIDialog::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUIDialog::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIDialog::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

// Bit 14 of the doodad starts a pointer drag: remember where the pointer was
bool PGUIDialog::OnButtonPress(Toshi::TInputInterface::InputEvent* event, int doodad)
{
    if (doodad & 0x4000)
    {
        m_bUnkA4 = true;
        Toshi::TGUIScreen* screen = GetScreen();
        m_iPressPointerX = screen->GetPointerPositionX();
        m_iPressPointerY = screen->GetPointerPositionY();
        return true;
    }
    return Toshi::TGUIWindow::OnButtonPress(event, doodad);
}

bool PGUIDialog::OnPointerMove(int x, int y)
{
    return Toshi::TGUIWidget::OnPointerMove(x, y);
}

bool PGUIDialog::AllowsChildren() const
{
    return true;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIDialog::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIDialog::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

void PGUIDialog::Pack()
{
    PackChildren();

    if (GetStyle() != 0)
    {
        int width = GetWidth();
        int height = GetHeight();

        SetComponentBBox(0, 0, 0, width, height);
        SetComponentBBox(1, 0, 0, width, height);
    }

    SetValidated(true);
}

bool PGUIDialog::Serialise(PProperties* properties)
{
    if (!TGUIWindow::Serialise(properties)) {
        return false;
    }
    return true;
}

PGUIDialog::PGUIDialog(const PGUIDialog& other)
    : TGUIWindow(other)
{
    m_bUnkA4 = false;
}

PGUIDialog* PGUIDialog::Clone() const
{
    return new PGUIDialog(*this);
}
