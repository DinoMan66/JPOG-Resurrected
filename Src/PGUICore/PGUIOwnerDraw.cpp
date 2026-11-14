// PGUIOwnerDraw accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIOwnerDraw.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIOwnerDraw::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIOwnerDraw::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUIOwnerDraw::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIOwnerDraw::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

// The callback belongs to the owner of the original widget, so a clone starts without one.
PGUIOwnerDraw::PGUIOwnerDraw(const PGUIOwnerDraw& other)
    : PGUIPanel(other)
{
    m_pCallBack = 0;
}

PGUIOwnerDraw* PGUIOwnerDraw::Clone() const
{
    return new PGUIOwnerDraw(*this);
}

PGUIOwnerDraw::CallBack* PGUIOwnerDraw::GetCallBack()
{
    return m_pCallBack;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIOwnerDraw::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIOwnerDraw::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUIOwnerDraw::Serialise(PProperties* properties)
{
    if (!PGUIPanel::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIOwnerDraw::Deserialise(const PProperties* properties)
{
    if (!PGUIPanel::Deserialise(properties)) {
        return false;
    }
    return true;
}

PGUIOwnerDraw::CallBack* PGUIOwnerDraw::SetCallBack(CallBack* callBack)
{
    CallBack* previous = m_pCallBack;
    m_pCallBack = callBack;
    return previous;
}

void PGUIOwnerDraw::Pack()
{
    if (m_pCallBack) {
        m_pCallBack->Pack(this);
    }
    SetValidated(true);
}
