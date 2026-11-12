// Z:\Toshi\Source\TKernel\TDList.cpp - TGenericPriList destruction.
// Kept in a second translation unit: the original calls RemoveAll out of line from this destructor,
// while the same-file definition in TDList.cpp would be expanded inline by the compiler.
// (TGenericDList's constructor and destructor are defined in the header.)
#include "TGenericLists.h"

namespace Toshi {

// The priority list's destructor calls the plain list's RemoveAll (same address): the unlink code is identical.
TGenericPriList::~TGenericPriList()
{
    ((TGenericDList*)this)->RemoveAll();
}

} // namespace Toshi
