// Toshi::PGUILayoutManager (PGUICore.dll): common base of PGUICore's layout managers that adds padding, fill and
// same-size flags to TGUILayoutManager. Only the property accessors are written so far.
#ifndef PGUILAYOUTMANAGER_H
#define PGUILAYOUTMANAGER_H
#include "PGUIAPI.h"
#include "TGUILayoutManager.h"

class PPropertyValue;

namespace Toshi {

class PGUI_API PGUILayoutManager : public TGUILayoutManager
{
public:
    bool GetForceSameHeight() const;
    bool GetForceSameWidth() const;
    int GetPadY() const;
    int GetPadX() const;
    void SetForceSameHeight(bool force);
    void SetForceSameWidth(bool force);
    void SetPad(int padX, int padY);
    void SetPadY(int padY);
    void SetPadX(int padX);

    bool Val_fillvertical_property(const PPropertyValue& value);
    PPropertyValue Get_fillvertical_property() const;
    void Set_fillvertical_property(const PPropertyValue& value);
    bool Val_fillhorizontal_property(const PPropertyValue& value);
    PPropertyValue Get_fillhorizontal_property() const;
    void Set_fillhorizontal_property(const PPropertyValue& value);
    bool Val_sameheight_property(const PPropertyValue& value);
    PPropertyValue Get_sameheight_property() const;
    void Set_sameheight_property(const PPropertyValue& value);
    bool Val_samewidth_property(const PPropertyValue& value);
    PPropertyValue Get_samewidth_property() const;
    void Set_samewidth_property(const PPropertyValue& value);
    bool Val_pady_property(const PPropertyValue& value);
    PPropertyValue Get_pady_property() const;
    void Set_pady_property(const PPropertyValue& value);
    bool Val_padx_property(const PPropertyValue& value);
    PPropertyValue Get_padx_property() const;
    void Set_padx_property(const PPropertyValue& value);

protected:
    PGUILayoutManager();
    PGUILayoutManager(const PGUILayoutManager& other);

    virtual const TArray<TGUIPropertySpec*>* GetPropertyInfoSet() const;        // slot 11
    virtual const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;     // slot 12

private:
    // PGUILayoutManager is abstract, so its factory functions create nothing
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);

    static TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static TArray<TGUIPropertySpec*>* ms_oPropertySet;
    static TGUILayoutInfo* ms_layout_info;

    short m_sPadX;                      // +0x0C
    short m_sPadY;                      // +0x0E
    bool m_bForceSameWidth;                  // +0x10
    bool m_bForceSameHeight;                 // +0x11
    bool m_bFillHorizontal;             // +0x12
    bool m_bFillVertical;               // +0x13
};

} // namespace Toshi

#endif
