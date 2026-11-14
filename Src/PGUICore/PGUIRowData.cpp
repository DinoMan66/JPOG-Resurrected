// PGUIRowData accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIRowData.h"

// The row's own state is the state of its first column
unsigned int PGUIRowData::GetState() const
{
    return m_puStates[0];
}

void PGUIRowData::RemoveState(int column, unsigned int mask)
{
    m_puStates[column] &= ~mask;
}

void PGUIRowData::AddState(int column, unsigned int mask)
{
    m_puStates[column] |= mask;
}

void PGUIRowData::SetState(int column, unsigned int state)
{
    m_puStates[column] = state;
}

unsigned int PGUIRowData::GetState(int column) const
{
    return m_puStates[column];
}

PPropertyValue* PGUIRowData::GetParameterValues(int column)
{
    return m_ppParameterValues[column];
}

PPropertyValue** PGUIRowData::GetParameterValues()
{
    return m_ppParameterValues;
}

int PGUIRowData::GetColumnCount() const
{
    return m_iColumnCount;
}

void PGUIRowData::SetState(unsigned int state)
{
    for (int column = 0; column < m_iColumnCount; column++)
    {
        m_puStates[column] = state;
    }
}

void PGUIRowData::AddState(unsigned int mask)
{
    for (int column = 0; column < m_iColumnCount; column++)
    {
        m_puStates[column] |= mask;
    }
}

void PGUIRowData::RemoveState(unsigned int mask)
{
    for (int column = 0; column < m_iColumnCount; column++)
    {
        m_puStates[column] &= ~mask;
    }
}
