// Toshi::TGUIStyleState - one state of a GUI style: a state rule and the components drawn in that state
// (TGuiInterface.dll). States form the list kept by TGUIStyleRootComponent. The destructor is the
// compiler-generated one and deletes the components.
#ifndef TGUISTYLESTATE_H
#define TGUISTYLESTATE_H
#include "TGUIAPI.h"
#include "TNodeList.h"
#include "TGUIStateRule.h"
#include "TGUIComponent.h"

namespace Toshi {

class TGUI_API TGUIStyleState : public TNodeList<TGUIStyleState>::TNode
{
public:
    explicit TGUIStyleState(const TGUIStateRule& rule);
    TGUIStyleState(const TGUIStyleState& other);

    void AddComponent(TGUIComponent* component) { m_oComponents.InsertTail(component); }
    TNodeList<TGUIComponent>& GetComponents();
    void SetStateRule(const TGUIStateRule& rule);
    void GetStateRule(TGUIStateRule& rule) const;

private:
    TGUIStateRule m_oRule;                      // +0x0C
    TNodeList<TGUIComponent> m_oComponents;     // +0x14, owned
};

} // namespace Toshi
#endif
