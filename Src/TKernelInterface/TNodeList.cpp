// Z:\Toshi\Source\TKernel\TNodeList.cpp - TGenericNodeList (nodes have a vtable, an owner list and next/prev).
// Not written: Append.
#include "TGenericLists.h"

namespace Toshi {

// ---- TGenericNodeList::Iterator ----

TGenericNodeList::Iterator& TGenericNodeList::Iterator::operator=(const Iterator& o)
{
    m_pNode = o.m_pNode;
    return *this;
}

bool TGenericNodeList::Iterator::IsNull()
{
    if (m_pNode == 0) {
        return true;
    }
    return false;
}

bool TGenericNodeList::Iterator::operator!=(Iterator& o) const
{
    return m_pNode != o.m_pNode;
}

bool TGenericNodeList::Iterator::operator==(Iterator& o) const
{
    return m_pNode == o.m_pNode;
}

TGenericNodeList::Iterator& TGenericNodeList::Iterator::operator--()
{
    if (m_pNode) {
        m_pNode = m_pNode->m_pPrev;
    }
    return *this;
}

TGenericNodeList::Iterator TGenericNodeList::Iterator::operator++(int)
{
    Iterator old = *this;
    if (m_pNode) {
        m_pNode = m_pNode->m_pNext;
    }
    return old;
}

TGenericNodeList::Iterator& TGenericNodeList::Iterator::operator++()
{
    if (m_pNode) {
        m_pNode = m_pNode->m_pNext;
    }
    return *this;
}

TGenericNodeList::Iterator::operator TNode*() const
{
    return m_pNode;
}

TGenericNodeList::TNode* TGenericNodeList::Iterator::operator->() const
{
    return m_pNode;
}

TGenericNodeList::TNode& TGenericNodeList::Iterator::operator*() const
{
    return *m_pNode;
}

TGenericNodeList::Iterator::~Iterator()
{
}

TGenericNodeList::Iterator::Iterator(TNode* n)
{
    m_pNode = n;
}

TGenericNodeList::Iterator::Iterator()
{
    m_pNode = 0;
}

TGenericNodeList::Iterator::Iterator(const Iterator& o)
{
    m_pNode = o.m_pNode;
}

// ---- TGenericNodeList::TNode ----

TGenericNodeList::TNode& TGenericNodeList::TNode::operator=(const TNode& o)
{
    m_pList = o.m_pList;
    m_pNext = o.m_pNext;
    m_pPrev = o.m_pPrev;
    return *this;
}

TGenericNodeList::TNode::TNode(const TNode& o)
{
    m_pList = o.m_pList;
    m_pNext = o.m_pNext;
    m_pPrev = o.m_pPrev;
}

TGenericNodeList::TNode::~TNode()
{
}

TGenericNodeList::TNode::TNode()
{
    m_pNext = this;
    m_pPrev = this;
    SetList(0);
}

TGenericNodeList* TGenericNodeList::TNode::SetList(TGenericNodeList* list)
{
    TGenericNodeList* old = m_pList;
    m_pList = list;
    return old;
}

TGenericNodeList* TGenericNodeList::TNode::GetList() const
{
    return m_pList;
}

TGenericNodeList::TNode* TGenericNodeList::TNode::Prev() const
{
    return m_pPrev;
}

TGenericNodeList::TNode* TGenericNodeList::TNode::Next() const
{
    return m_pNext;
}

// ---- TGenericNodeList ----

void TGenericNodeList::InsertBefore(TNode& ref, TNode& n)
{
    n.SetList(this);
    n.m_pNext = &ref;
    n.m_pPrev = ref.m_pPrev;
    n.m_pPrev->m_pNext = &n;
    ref.m_pPrev = &n;
    m_iCount++;
}

void TGenericNodeList::InsertAfter(TNode& ref, TNode& n)
{
    n.SetList(this);
    n.m_pNext = ref.m_pNext;
    n.m_pPrev = &ref;
    n.m_pNext->m_pPrev = &n;
    ref.m_pNext = &n;
    m_iCount++;
}

TGenericNodeList::TNode* TGenericNodeList::Remove(TNode& n)
{
    n.SetList(0);
    n.m_pPrev->m_pNext = n.m_pNext;
    n.m_pNext->m_pPrev = n.m_pPrev;
    n.m_pNext = &n;
    n.m_pPrev = &n;
    m_iCount--;
    return &n;
}

void TGenericNodeList::Delete(TNode& n)
{
    Remove(n);
    delete &n;
}

void TGenericNodeList::DeleteAll()
{
    while (!IsEmpty()) {
        Delete(*m_oRoot.Next());
    }
}

TGenericNodeList::Iterator TGenericNodeList::MakeIterator(TNode* n)
{
    return Iterator(n);
}

TGenericNodeList::Iterator TGenericNodeList::REnd() const
{
    return Iterator((TNode*)&m_oRoot);
}

TGenericNodeList::Iterator TGenericNodeList::RBegin() const
{
    return Iterator(m_oRoot.Prev());
}

TGenericNodeList::Iterator TGenericNodeList::End() const
{
    return Iterator((TNode*)&m_oRoot);
}

TGenericNodeList::Iterator TGenericNodeList::Begin() const
{
    return Iterator(m_oRoot.Next());
}

bool TGenericNodeList::IsValid(const TNode* n) const
{
    if (n == 0 || n == &m_oRoot) {
        return false;
    }
    return true;
}

int TGenericNodeList::Count() const
{
    return m_iCount;
}

void TGenericNodeList::InsertTail(TNode& n)
{
    InsertBefore(m_oRoot, n);
}

void TGenericNodeList::InsertHead(TNode& n)
{
    InsertAfter(m_oRoot, n);
}

TGenericNodeList::TNode* TGenericNodeList::Tail() const
{
    return m_oRoot.Prev();
}

TGenericNodeList::TNode* TGenericNodeList::Head() const
{
    return m_oRoot.Next();
}

} // namespace Toshi
