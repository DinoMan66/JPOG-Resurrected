// Z:\Toshi\Source\TKernel\TNTree.cpp - TGenericNTree (simple members only).
#include "TKernelContainers.h"

namespace Toshi {

TGenericNTree::TNode& TGenericNTree::TNode::operator=(const TNode& o)
{
    m_pParent = o.m_pParent;
    m_apChildren[0] = o.m_apChildren[0];
    return *this;
}

int TGenericNTree::TNode::FindChild(const TNode* child, int childCount) const
{
    for (int i = 0; i < childCount; i++) {
        if (m_apChildren[i] == child) {
            return i;
        }
    }
    return -1;
}

void TGenericNTree::TNode::Remove(int childCount)
{
    TNode* parent = m_pParent;
    if (parent) {
        int index = parent->FindChild(this, childCount);
        if (index >= 0) {
            TNode* child = parent->m_apChildren[index];
            if (child) {
                child->m_pParent = 0;
                parent->m_apChildren[index] = 0;
            }
        }
    }
}

void TGenericNTree::TNode::RemoveChild(TNode* child, int childCount)
{
    int index = FindChild(child, childCount);
    if (index >= 0) {
        RemoveChild(index);
    }
}

void TGenericNTree::TNode::RemoveChild(int index)
{
    TNode* child = m_apChildren[index];
    if (child) {
        child->m_pParent = 0;
        m_apChildren[index] = 0;
    }
}

void TGenericNTree::TNode::InsertChild(int index, TNode* child)
{
    m_apChildren[index] = child;
    child->m_pParent = this;
}

TGenericNTree::TNode* TGenericNTree::TNode::Child(int index) const
{
    return m_apChildren[index];
}

TGenericNTree::TNode* TGenericNTree::TNode::Parent() const
{
    return m_pParent;
}

TGenericNTree::TGenericNTree()
{
    m_pRoot = 0;
}

void TGenericNTree::TNode::Reset(int childCount)
{
    m_pParent = 0;
    for (int i = 0; i < childCount; i++) {
        m_apChildren[i] = 0;
    }
}

void TGenericNTree::RemoveRoot()
{
    m_pRoot = 0;
}

void TGenericNTree::InsertRoot(TNode* root)
{
    m_pRoot = root;
    root->m_pParent = 0;
}

TGenericNTree::TNode* TGenericNTree::Root() const
{
    return m_pRoot;
}

} // namespace Toshi
