// Z:\Toshi\Source\TKernel\TNodeList.cpp - TGenericNodeList::IsEmpty.
// Own translation unit: the original's RemoveAll/RemoveHead/RemoveTail/DeleteHead/DeleteTail call it out of line.
#include "TGenericLists.h"

namespace Toshi {

bool TGenericNodeList::IsEmpty() const
{
    if (m_oRoot.Next() == &m_oRoot) {
        return true;
    }
    return false;
}

} // namespace Toshi
