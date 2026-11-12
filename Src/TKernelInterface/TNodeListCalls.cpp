// Z:\Toshi\Source\TKernel\TNodeList.cpp - TGenericNodeList members that call their siblings.
// Kept in a second translation unit: the original calls GetList/Next/Prev/IsEmpty out of line from these,
// while the same-file definitions in TNodeList.cpp would be expanded inline by the compiler.
#include "TGenericLists.h"

namespace Toshi {

bool TGenericNodeList::Iterator::operator!()
{
    return IsNull();
}

bool TGenericNodeList::TNode::IsLinked() const
{
    if (GetList() != 0) {
        return true;
    }
    return false;
}

void TGenericNodeList::RemoveAll()
{
    while (!IsEmpty()) {
        RemoveHead();
    }
}

void TGenericNodeList::DeleteHead()
{
    delete RemoveHead();
}

void TGenericNodeList::DeleteTail()
{
    delete RemoveTail();
}

inline TGenericNodeList::TNode* TGenericNodeList::RemoveTail()
{
    if (!IsEmpty()) {
        return Remove(*m_oRoot.Prev());
    }
    return 0;
}

inline TGenericNodeList::TNode* TGenericNodeList::RemoveHead()
{
    if (!IsEmpty()) {
        return Remove(*m_oRoot.Next());
    }
    return 0;
}

TGenericNodeList::TGenericNodeList(TGenericNodeList& other)
{
}

TGenericNodeList& TGenericNodeList::operator=(TGenericNodeList& other)
{
    return *this;
}

TGenericNodeList::TGenericNodeList()
{
    m_iCount = 0;
}

TGenericNodeList::~TGenericNodeList()
{
    DeleteAll();
}

} // namespace Toshi
