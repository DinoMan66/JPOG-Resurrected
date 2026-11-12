// Toshi::TGUILayoutInfo - registry entry describing one layout manager class and its properties
// (TGuiInterface.dll). The entries form the list returned by TGUIInterface::GetLayoutClassList.
// The copy constructor is the compiler-generated one.
#ifndef TGUILAYOUTINFO_H
#define TGUILAYOUTINFO_H
#include "TGUIAPI.h"
#include "TObject.h"
#include "TPString.h"
#include "TArray.h"
#include "TNodeList.h"

namespace Toshi {

class TGUIPropertySpec;

class TGUI_API TGUILayoutInfo : public TNodeList<TGUILayoutInfo>::TNode
{
public:
    // the layout manager class is looked up by name
    TGUILayoutInfo(const TPCString& name, const TPCString& label, TArray<TGUIPropertySpec*>* properties);
    ~TGUILayoutInfo();

    const TPCString& GetLayoutName() const;
    const TPCString& GetLayoutLabel() const;
    const TClass* GetTClass() const;
    int GetPropertyCount() const;
    const TGUIPropertySpec* GetPropertyInfo(int index) const;

private:
    TPCString m_oLayoutName;                    // +0x0C
    TPCString m_oLayoutLabel;                   // +0x10
    const TClass* m_pClass;                     // +0x14
    TArray<TGUIPropertySpec*>* m_paProperties;  // +0x18
};

} // namespace Toshi
#endif
