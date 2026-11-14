// Toshi::TGUIPairNode - a list node that holds a key and a value (TGuiInterface.dll). TGUIStyle keeps the
// widget properties it fixes as a list of TGUIPairNode<TPCString, PPropertyValue>.
#ifndef TGUIPAIRNODE_H
#define TGUIPAIRNODE_H
#include "TNodeList.h"

namespace Toshi {

template <class Key, class Value>
struct TGUIPairNode : public TNodeList<TGUIPairNode<Key, Value> >::TNode
{
    Key m_oKey;         // +0x0C
    Value m_oValue;     // +0x10
};

} // namespace Toshi
#endif
