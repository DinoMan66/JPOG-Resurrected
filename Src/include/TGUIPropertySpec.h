// Toshi::TGUIPropertySpec - describes one editable property of a GUI class (TGuiInterface.dll).
// Size 0x24 (vtable, then the members below).
#ifndef TGUIPROPERTYSPEC_H
#define TGUIPROPERTYSPEC_H
#include "TGUIAPI.h"
#include "TObject.h"
#include "TPString.h"

namespace Toshi {

class TGUI_API TGUIPropertySpec
{
public:
    // what kind of value the property holds (numbers are the ones the binary tests; names are descriptive guesses)
    enum PropertyKind
    {
        KIND_ENUMERATION = 1,   // one of a list of named values
        KIND_CLASS_NAME = 2     // the name of a class derived from m_pBaseClass
    };

    struct Comparator;      // orders the specs in the classes' ms_oPropertySetOrdered

    TGUIPropertySpec(const TPCString& name);
    virtual ~TGUIPropertySpec();
    TGUIPropertySpec& operator=(const TGUIPropertySpec& other);

    bool operator==(const TGUIPropertySpec& other);

    const TClass* GetType() const;
    void SetType(const TClass* type);
    const TPCString& GetName() const;
    void SetName(const TPCString& name);
    const TClass* GetSourceClass() const { return m_pSourceClass; }
    int GetSortHint() const;
    bool AllowsAutoInstall() const;
    bool IsClassName() const;
    const TClass* GetBaseClass() const;
    bool IsEnumerated() const;
    int GetEnumCount() const;
    const TPCString& GetEnumName(int index) const;

protected:
    TGUIPropertySpec(const TPCString& name, const TClass* type, bool autoInstall, const TClass* sourceClass, int sortHint);
    TGUIPropertySpec(const TPCString& name, const TClass* type, bool autoInstall, const TClass* sourceClass, int sortHint,
                     const TClass* baseClass);
    TGUIPropertySpec(const TPCString& name, const TClass* type, bool autoInstall, const TClass* sourceClass, int sortHint,
                     int enumCount, const char* const* enumNames);
    TGUIPropertySpec(const TGUIPropertySpec& other);

private:
    const TClass* m_pType;          // +0x04
    TPCString m_oName;              // +0x08
    bool m_bAutoInstall;            // +0x0C
    const TClass* m_pSourceClass;   // +0x10 the class that declares the property
    int m_iSortHint;                // +0x14
    int m_iKind;                    // +0x18 PropertyKind
    union
    {
        int m_iEnumCount;           // +0x1C when the kind is KIND_ENUMERATION
        const TClass* m_pBaseClass; // +0x1C otherwise
    };
    TPCString* m_aEnumNames;        // +0x20 m_iEnumCount names
};

} // namespace Toshi
#endif
