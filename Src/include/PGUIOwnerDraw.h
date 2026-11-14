// PGUIOwnerDraw (PGUICore.dll): a panel whose painting and packing are done by a callback object the owner
// supplies. Only the accessors are written so far.
#ifndef PGUIOWNERDRAW_H
#define PGUIOWNERDRAW_H
#include "PGUIAPI.h"
#include "PGUIPanel.h"

class PGUI_API PGUIOwnerDraw : public PGUIPanel
{
public:
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    class CallBack
    {
    public:
        virtual void Pack(PGUIOwnerDraw* owner) = 0;                                                    // slot 0
        virtual void Slot1() = 0;                                                                       // slot 1
        virtual void Paint(PGUIOwnerDraw* owner, Toshi::TGUIDisplayContext* context) = 0;               // slot 2
    };

    CallBack* GetCallBack();
    CallBack* SetCallBack(CallBack* callBack);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual PGUIOwnerDraw* Clone() const;                               // slot 13
    virtual void Pack();                                                // slot 33

protected:
    PGUIOwnerDraw(const PGUIOwnerDraw& other);

    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    CallBack* m_pCallBack;      // +0x8C

    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
