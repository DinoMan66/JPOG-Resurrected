// Z:\Toshi\Source\TKernel\TDList.cpp - TGenericDList and TGenericPriList.
// Not written: Append-style functions.
#include "TGenericLists.h"

namespace Toshi {

// ---- TGenericDList::TNode ----

void TGenericDList::TNode::Remove()
{
    m_pPrev->m_pNext = m_pNext;
    m_pNext->m_pPrev = m_pPrev;
    m_pNext = this;
    m_pPrev = this;
}

void TGenericDList::TNode::InsertAfter(TNode* n)
{
    m_pPrev = n;
    m_pNext = n->m_pNext;
    n->m_pNext = this;
    m_pNext->m_pPrev = this;
}

void TGenericDList::TNode::InsertBefore(TNode* n)
{
    m_pNext = n;
    m_pPrev = n->m_pPrev;
    n->m_pPrev = this;
    m_pPrev->m_pNext = this;
}

bool TGenericDList::TNode::IsLinked() const
{
    return this != m_pNext;
}

TGenericDList::TNode* TGenericDList::TNode::Prev() const
{
    return m_pPrev;
}

TGenericDList::TNode* TGenericDList::TNode::Next() const
{
    return m_pNext;
}

void TGenericDList::TNode::Reset()
{
    m_pNext = this;
    m_pPrev = this;
}

// ---- TGenericDList ----

void TGenericDList::InsertSegmentAtTail(TNode* first, TNode* last)
{
    last->m_pNext = &m_oRoot;
    first->m_pPrev = m_oRoot.m_pPrev;
    last->m_pNext->m_pPrev = last;
    first->m_pPrev->m_pNext = first;
}

void TGenericDList::InsertSegmentAtHead(TNode* first, TNode* last)
{
    first->m_pPrev = &m_oRoot;
    last->m_pNext = m_oRoot.m_pNext;
    first->m_pPrev->m_pNext = first;
    last->m_pNext->m_pPrev = last;
}

void __stdcall TGenericDList::RemoveSegment(TNode* first, TNode* last)
{
    first->m_pPrev->m_pNext = last->m_pNext;
    last->m_pNext->m_pPrev = first->m_pPrev;
    first->m_pPrev = first;
    last->m_pNext = last;
}

void __stdcall TGenericDList::InsertSegmentAfter(TNode* first, TNode* last, TNode* after)
{
    first->m_pPrev = after;
    last->m_pNext = after->m_pNext;
    first->m_pPrev->m_pNext = first;
    last->m_pNext->m_pPrev = last;
}

void __stdcall TGenericDList::InsertSegmentBefore(TNode* first, TNode* last, TNode* before)
{
    last->m_pNext = before;
    first->m_pPrev = before->m_pPrev;
    last->m_pNext->m_pPrev = last;
    first->m_pPrev->m_pNext = first;
}

void TGenericDList::RemoveAll()
{
    while (m_oRoot.m_pNext != &m_oRoot) {
        TNode* node = m_oRoot.m_pNext;
        node->m_pPrev->m_pNext = node->m_pNext;
        node->m_pNext->m_pPrev = node->m_pPrev;
        node->m_pNext = node;
        node->m_pPrev = node;
    }
}

void TGenericDList::RemoveTail()
{
    if (m_oRoot.Next() != &m_oRoot) {
        m_oRoot.Prev()->Remove();
    }
}

void TGenericDList::RemoveHead()
{
    if (m_oRoot.Next() != &m_oRoot) {
        m_oRoot.Next()->Remove();
    }
}

void TGenericDList::InsertTail(TNode* n)
{
    n->InsertBefore(&m_oRoot);
}

void TGenericDList::InsertHead(TNode* n)
{
    n->InsertAfter(&m_oRoot);
}

bool TGenericDList::IsEmpty() const
{
    return m_oRoot.Next() == &m_oRoot;
}

const TGenericDList::TNode* TGenericDList::REnd() const
{
    return &m_oRoot;
}

TGenericDList::TNode* TGenericDList::RBegin() const
{
    return m_oRoot.Prev();
}

const TGenericDList::TNode* TGenericDList::End() const
{
    return &m_oRoot;
}

TGenericDList::TNode* TGenericDList::Begin() const
{
    return m_oRoot.Next();
}

TGenericDList::TNode* TGenericDList::Tail() const
{
    return m_oRoot.Prev();
}

TGenericDList::TNode* TGenericDList::Head() const
{
    return m_oRoot.Next();
}

// ---- TGenericPriList::TNode ----

void TGenericPriList::TNode::SetPriority(int p)
{
    m_iPriority = p;
}

int TGenericPriList::TNode::GetPriority() const
{
    return m_iPriority;
}

bool TGenericPriList::TNode::IsLinked() const
{
    return this != m_pNext;
}

TGenericPriList::TNode* TGenericPriList::TNode::Prev() const
{
    return m_pPrev;
}

TGenericPriList::TNode* TGenericPriList::TNode::Next() const
{
    return m_pNext;
}

void TGenericPriList::TNode::Reset()
{
    m_pNext = this;
    m_pPrev = this;
    m_iPriority = 0;
}

// ---- TGenericPriList ----

TGenericPriList::TGenericPriList() : m_oRoot(TNode::UNINITIALISED)
{
    m_oRoot.m_pNext = &m_oRoot;
    m_oRoot.m_pPrev = &m_oRoot;
}

// The binary's RemoveAll is a call into TGenericDList::RemoveAll (same address): the unlink code is identical.
void TGenericPriList::RemoveAll()
{
    ((TGenericDList*)this)->RemoveAll();
}

void TGenericPriList::RemoveTail()
{
    if (m_oRoot.m_pNext != &m_oRoot) {
        TNode* node = m_oRoot.m_pPrev;
        node->m_pPrev->m_pNext = node->m_pNext;
        node->m_pNext->m_pPrev = node->m_pPrev;
        node->m_pNext = node;
        node->m_pPrev = node;
    }
}

// Nodes of equal priority keep their insertion order. Non-negative priorities are searched from the tail,
// negative ones from the head.
void TGenericPriList::Insert(TNode* node)
{
    int priority = node->m_iPriority;
    TNode* position;
    if (priority >= 0) {
        position = m_oRoot.m_pPrev;
        while (position != &m_oRoot && priority < position->m_iPriority) {
            position = position->m_pPrev;
        }
        node->m_pPrev = position;
        node->m_pNext = position->m_pNext;
        position->m_pNext = node;
        node->m_pNext->m_pPrev = node;
    } else {
        position = m_oRoot.m_pNext;
        while (position != &m_oRoot && priority >= position->m_iPriority) {
            position = position->m_pNext;
        }
        node->m_pNext = position;
        node->m_pPrev = position->m_pPrev;
        position->m_pPrev = node;
        node->m_pPrev->m_pNext = node;
    }
}

void TGenericPriList::RemoveHead()
{
    TNode* node = m_oRoot.m_pNext;
    if (node != &m_oRoot) {
        node->m_pPrev->m_pNext = node->m_pNext;
        node->m_pNext->m_pPrev = node->m_pPrev;
        node->m_pNext = node;
        node->m_pPrev = node;
    }
}

void TGenericPriList::Insert(TNode* n, int priority)
{
    n->SetPriority(priority);
    Insert(n);
}

bool TGenericPriList::IsEmpty() const
{
    return m_oRoot.m_pNext == &m_oRoot;
}

const TGenericPriList::TNode* TGenericPriList::REnd() const
{
    return &m_oRoot;
}

TGenericPriList::TNode* TGenericPriList::RBegin() const
{
    return m_oRoot.m_pPrev;
}

const TGenericPriList::TNode* TGenericPriList::End() const
{
    return &m_oRoot;
}

TGenericPriList::TNode* TGenericPriList::Begin() const
{
    return m_oRoot.m_pNext;
}

TGenericPriList::TNode* TGenericPriList::Tail() const
{
    return m_oRoot.m_pPrev;
}

TGenericPriList::TNode* TGenericPriList::Head() const
{
    return m_oRoot.m_pNext;
}

void TGenericPriList::InsertTail(TNode* n)
{
    n->m_iPriority = 0x7fff;
    n->m_pNext = &m_oRoot;
    n->m_pPrev = m_oRoot.m_pPrev;
    m_oRoot.m_pPrev = n;
    n->m_pPrev->m_pNext = n;
}

void TGenericPriList::InsertHead(TNode* n)
{
    n->m_iPriority = -0x8000;
    n->m_pPrev = &m_oRoot;
    n->m_pNext = m_oRoot.m_pNext;
    m_oRoot.m_pNext = n;
    n->m_pNext->m_pPrev = n;
}

void TGenericPriList::SetPriority(TNode* n, int priority)
{
    n->Remove();
    n->m_iPriority = priority;
    Insert(n);
}

} // namespace Toshi
