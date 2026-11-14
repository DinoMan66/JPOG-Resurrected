// PGUIGridLayout (PGUICore.dll): a layout manager that places the children in a grid of rows and columns.
// Only the accessors are written so far.
#ifndef PGUIGRIDLAYOUT_H
#define PGUIGRIDLAYOUT_H
#include "PGUIAPI.h"
#include "PGUILayoutManager.h"

class PPropertyValue;

class PGUI_API PGUIGridLayout : public Toshi::PGUILayoutManager
{
public:
    bool Val_columns_property(const PPropertyValue& value);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual PGUIGridLayout* Clone() const;                       // slot 13
    PGUIGridLayout();
    int GetNumCOls() const;     // sic: the exported name has this spelling
    int GetNumRows() const;
    void SetNumRows(int rows);
    void SetNumCols(int columns);

    void Set_columns_property(const PPropertyValue& value);
    void Set_rows_property(const PPropertyValue& value);
    PPropertyValue Get_rows_property() const;
    PPropertyValue Get_columns_property() const;

    virtual void DoPack(Toshi::TGUIWidget* widget) const;                           // slot 14
    virtual void DoLayout(Toshi::TGUIWidget* widget, int& arg1, int& arg2) const;   // slot 15

protected:
    PGUIGridLayout(const PGUIGridLayout& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    short m_sNumRows;           // +0x14
    short m_sNumCols;           // +0x16

    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
    static Toshi::TGUILayoutInfo* ms_layout_info;
};

#endif
