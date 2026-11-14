// Toshi::TGUIDeserialisable (TGuiInterface.dll): abstract base of the GUI objects that are loaded from and
// saved to property lists (fonts, styles, layout managers, widgets). A derived class describes its properties
// with TGUIPropertySpec entries; this class looks them up by position or by name.
// Vtable: [0] GetClass [1] Delete [2] destructor [3] Deserialise [4] Serialise [5] GetPropertyCount
//         [6] FindPropertyInfo [7] GetPropertyInfo [8] ValidatePropertyInfo [9] SetInterface
//         [10] GetInterface [11] GetPropertyInfoSet [12] GetPropertyInfoOrderedSet
#ifndef TGUIDESERIALISABLE_H
#define TGUIDESERIALISABLE_H
#include "TGUIAPI.h"
#include "TObject.h"
#include "TPString.h"
#include "TArray.h"
#include "TSortedArray.h"
#include "TGUIPropertySpec.h"

class PProperties;
class PPropertyValue;

namespace Toshi {

class TGUIInterface;

class TGUI_API TGUIDeserialisable : public TObject
{
public:
    TGUIDeserialisable();
    // A copy has no state of its own
    TGUIDeserialisable(const TGUIDeserialisable& other) : TObject(other) {}
    virtual ~TGUIDeserialisable();

    virtual TClass& GetClass() const;                                                   // slot 0
    virtual bool Deserialise(const PProperties* properties);                            // slot 3
    virtual bool Serialise(PProperties* properties);                                    // slot 4
    virtual int GetPropertyCount() const;                                               // slot 5
    virtual const TGUIPropertySpec* FindPropertyInfo(const TPCString& name) const;      // slot 6
    virtual const TGUIPropertySpec* GetPropertyInfo(int index) const;                   // slot 7
    virtual bool ValidatePropertyInfo(const TGUIPropertySpec* info) const;              // slot 8
    virtual void SetInterface(TGUIInterface* gui) = 0;                                  // slot 9
    virtual TGUIInterface* GetInterface() const = 0;                                    // slot 10

    bool SetProperty(const TGUIPropertySpec* spec, const PPropertyValue& value);
    bool SetProperty(const TPCString& name, const PPropertyValue& value);
    bool ValidateProperty(const TPCString& name, const PPropertyValue& value) const;
    PPropertyValue GetProperty(const TGUIPropertySpec* spec, bool& found) const;
    PPropertyValue GetProperty(const TPCString& name, bool& found) const;

protected:
    virtual const TArray<TGUIPropertySpec*>* GetPropertyInfoSet() const = 0;            // slot 11
    // slot 12: the same specs, sorted
    virtual const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const = 0;

public:
    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

} // namespace Toshi
#endif
