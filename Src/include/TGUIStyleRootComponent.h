// Toshi::TGUIStyleRootComponent - root of a GUI style: the list of its states and the margins around
// them (TGuiInterface.dll). The destructor is the compiler-generated one and deletes the states.
// operator=, DeserialiseStates and SerialiseStates are still to do.
#ifndef TGUISTYLEROOTCOMPONENT_H
#define TGUISTYLEROOTCOMPONENT_H
#include "TGUIAPI.h"
#include "TNodeList.h"
#include "TGUIStyleState.h"

namespace Toshi {

class TGUI_API TGUIStyleRootComponent : public TNodeList<TGUIStyleState>
{
public:
    TGUIStyleRootComponent();

    void AddState(TGUIStyleState* state);
    TNodeList<TGUIStyleState>& GetStates();
    TGUIStyleState* FindState(const TGUIStateRule& rule);
    TGUIStyleState* CreateState(const TGUIStateRule& rule);

    void GetMargins(int& left, int& right, int& top, int& bottom);
    void SetMargins(int left, int right, int top, int bottom);
    int GetMarginLeft() const;
    int GetMarginRight() const;
    int GetMarginTop() const;
    int GetMarginBottom() const;
    void SetMarginLeft(int margin);
    void SetMarginRight(int margin);
    void SetMarginTop(int margin);
    void SetMarginBottom(int margin);

private:
    int m_iMarginLeft;      // +0x10
    int m_iMarginRight;     // +0x14
    int m_iMarginTop;       // +0x18
    int m_iMarginBottom;    // +0x1C
};

} // namespace Toshi
#endif
