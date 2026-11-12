// Toshi::TGUIWidgetInfo (TGuiInterface.dll): the description of one widget class: its name and label,
// the TClass that creates it, the names of the components a style must provide for it, the state
// variables its states are built from, the properties it can load, the input actions it handles and how
// many widgets of the class exist at the moment.
// Size 0x48. The widget infos are kept in a list (TNodeList node at +0x00).
#ifndef TGUIWIDGETINFO_H
#define TGUIWIDGETINFO_H
#include "TGUIAPI.h"
#include "TArray.h"
#include "TSortedArray.h"
#include "TNodeList.h"
#include "TObject.h"
#include "TPString.h"
#include "TGUIStateVarInfo.h"

namespace Toshi {

class TGUIPropertySpec;

class TGUI_API TGUIWidgetInfo : public TNodeList<TGUIWidgetInfo>::TNode
{
public:
    TGUIWidgetInfo();
    ~TGUIWidgetInfo();

    const TClass* GetTClass() const { return m_pClass; }
    const TPCString& GetWidgetName() const { return m_oWidgetName; }
    const TPCString& GetWidgetLabel() const { return m_oWidgetLabel; }
    bool IsConcrete() const { return m_bConcrete; }

    // components a style has to define for this widget class
    TArray<TPCString>& GetComponentNameSet() { return m_oComponentNames; }
    int GetComponentCount() const { return m_oComponentNames.Count(); }
    const TPCString& GetComponentName(int index) const { return m_oComponentNames[index]; }

    // input actions, a bit set
    unsigned int GetInputActions() const { return m_uiInputActions; }
    void AddInputAction(unsigned int action) { m_uiInputActions |= action; }

    // number of live widgets of this class
    int GetInstanceCount() const { return m_iInstanceCount; }
    void AddInstance() { m_iInstanceCount++; }
    void DelInstance() { m_iInstanceCount--; }

protected:
    int GetPropertyCount() const { return m_pProperties->Count(); }
    const TGUIPropertySpec* GetPropertyInfo(int index) const { return (*m_pProperties)[index]; }

private:
    TPCString m_oWidgetName;                        // +0x0C
    TPCString m_oWidgetLabel;                       // +0x10
    const TClass* m_pClass;                         // +0x14
    TArray<TPCString> m_oComponentNames;            // +0x18
    TSortedArray<TGUIStateVarInfo, TGUIStateVarInfo::Comparator> m_oStateVars;    // +0x28
    TArray<TGUIPropertySpec*>* m_pProperties;       // +0x38
    unsigned int m_uiInputActions;                  // +0x3C
    bool m_bConcrete;                               // +0x40
    int m_iInstanceCount;                           // +0x44
};

} // namespace Toshi
#endif
