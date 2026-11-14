// PGUIRowData (PGUICore.dll): the data of one row of a table box - one state word and one parameter value
// per column. A row is a node of the table box's row list. Only the accessors are written so far.
#ifndef PGUIROWDATA_H
#define PGUIROWDATA_H
#include "PGUIAPI.h"
#include "TNodeList.h"
#include "TObject.h"

class PPropertyValue;

class PGUI_API PGUIRowData : public Toshi::TObject, public Toshi::TNodeList<PGUIRowData>::TNode
{
public:
    unsigned int GetState() const;
    void RemoveState(int column, unsigned int mask);
    void AddState(int column, unsigned int mask);
    void SetState(int column, unsigned int state);
    void SetState(unsigned int state);
    void AddState(unsigned int mask);
    void RemoveState(unsigned int mask);
    unsigned int GetState(int column) const;
    PPropertyValue* GetParameterValues(int column);
    PPropertyValue** GetParameterValues();
    int GetColumnCount() const;

private:
    int m_iColumnCount;                     // +0x10
    PPropertyValue** m_ppParameterValues;   // +0x14
    unsigned int* m_puStates;               // +0x18
};

#endif
