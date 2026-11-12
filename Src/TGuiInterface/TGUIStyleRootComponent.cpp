// Z:\Toshi\Source\TGUI - TGUIStyleRootComponent. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TGUIStyleRootComponent.h"

namespace Toshi {

TGUIStyleRootComponent::TGUIStyleRootComponent()
    : m_iMarginLeft(0)
    , m_iMarginRight(0)
    , m_iMarginTop(0)
    , m_iMarginBottom(0)
{
}

void TGUIStyleRootComponent::AddState(TGUIStyleState* state)
{
    InsertTail(state);
}

TNodeList<TGUIStyleState>& TGUIStyleRootComponent::GetStates()
{
    return *this;
}

void TGUIStyleRootComponent::GetMargins(int& left, int& right, int& top, int& bottom)
{
    left = m_iMarginLeft;
    right = m_iMarginRight;
    top = m_iMarginTop;
    bottom = m_iMarginBottom;
}

void TGUIStyleRootComponent::SetMargins(int left, int right, int top, int bottom)
{
    m_iMarginLeft = left;
    m_iMarginRight = right;
    m_iMarginTop = top;
    m_iMarginBottom = bottom;
}

int TGUIStyleRootComponent::GetMarginLeft() const
{
    return m_iMarginLeft;
}

int TGUIStyleRootComponent::GetMarginRight() const
{
    return m_iMarginRight;
}

int TGUIStyleRootComponent::GetMarginTop() const
{
    return m_iMarginTop;
}

int TGUIStyleRootComponent::GetMarginBottom() const
{
    return m_iMarginBottom;
}

void TGUIStyleRootComponent::SetMarginLeft(int margin)
{
    m_iMarginLeft = margin;
}

void TGUIStyleRootComponent::SetMarginRight(int margin)
{
    m_iMarginRight = margin;
}

void TGUIStyleRootComponent::SetMarginTop(int margin)
{
    m_iMarginTop = margin;
}

void TGUIStyleRootComponent::SetMarginBottom(int margin)
{
    m_iMarginBottom = margin;
}

} // namespace Toshi
