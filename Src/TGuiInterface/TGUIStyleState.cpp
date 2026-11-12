// Z:\Toshi\Source\TGUI - TGUIStyleState. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TGUIStyleState.h"

namespace Toshi {

TGUIStyleState::TGUIStyleState(const TGUIStateRule& rule)
    : m_oRule(rule)
{
}

// Deep copy: every component is cloned
TGUIStyleState::TGUIStyleState(const TGUIStyleState& other)
{
    for (TNodeList<TGUIComponent>::Iterator it = other.m_oComponents.Begin(); it != other.m_oComponents.End(); ++it) {
        AddComponent(it->Clone());
    }
    m_oRule = other.m_oRule;
}

TNodeList<TGUIComponent>& TGUIStyleState::GetComponents()
{
    return m_oComponents;
}

void TGUIStyleState::SetStateRule(const TGUIStateRule& rule)
{
    m_oRule = rule;
}

void TGUIStyleState::GetStateRule(TGUIStateRule& rule) const
{
    rule = m_oRule;
}

} // namespace Toshi
