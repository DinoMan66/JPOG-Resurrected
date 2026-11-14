// Toshi::TGUIStateRule - condition a style state applies under (TGuiInterface.dll). The struct is passed by
// reference to TGUIStyleState::SetStateRule/GetStateRule, TGUIStyleRootComponent::FindState and
// TGUIWidgetInfo::GetStateExpression; its two words are not understood yet, so they keep offset names.
#ifndef TGUISTATERULE_H
#define TGUISTATERULE_H

namespace Toshi {

struct TGUIStateRule
{
    TGUIStateRule()
        : m_unk00(0)
        , m_unk04(0)
    {
    }

    bool operator==(const TGUIStateRule& other) const
    {
        return m_unk00 == other.m_unk00 && m_unk04 == other.m_unk04;
    }

    /* 0x00 */ unsigned int m_unk00;
    /* 0x04 */ unsigned int m_unk04;
};

} // namespace Toshi
#endif
