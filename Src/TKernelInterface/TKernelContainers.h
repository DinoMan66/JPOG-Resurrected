// TGenericPool / TGenericNTree - kernel-internal declarations (members protected in the binary).
#ifndef TKERNELCONTAINERS_H
#define TKERNELCONTAINERS_H

namespace Toshi {

class __declspec(dllexport) TGenericPool
{
public:
    struct TNode
    {
        TNode* m_pNext;
        TNode& operator=(const TNode& o);
    };
    struct TBlock
    {
        TBlock* m_pNext;
        TBlock& operator=(const TBlock& o);
    };

protected:
    ~TGenericPool();
    void Reinit();
    void Reset();
    bool AllocBlock();
    void Free(void* p);
    void* Alloc();

private:
    void ResetBlock(TBlock* block);

    int    m_iUnitSize;     // +0x00 stride of one unit
    int    m_iAlignment;    // +0x04 alignment of the first unit (also the slack allocated per block)
    int    m_iBlockSize;    // +0x08 bytes of units per block
    int    m_iMaxSize;      // +0x0C limit for m_iTotalSize (0 = unlimited)
    int    m_iTotalSize;    // +0x10 bytes handed out to blocks so far
    TBlock* m_pBlocks;      // +0x14
    TNode* m_pFree;         // +0x18
};

class __declspec(dllexport) TGenericNTree
{
public:
    class TNode
    {
    public:
        TNode& operator=(const TNode& o);

    protected:
        void Reset(int childCount);
        int FindChild(const TNode* child, int childCount) const;
        void Remove(int childCount);
        void RemoveChild(int index);
        void RemoveChild(TNode* child, int childCount);
        void InsertChild(int index, TNode* child);
        TNode* Child(int index) const;
        TNode* Parent() const;

        friend class TGenericNTree;
        TNode* m_pParent;           // +0
        TNode* m_apChildren[1];     // +4, childCount entries
    };

protected:
    TGenericNTree();
    void RemoveRoot();
    void InsertRoot(TNode* root);
    TNode* Root() const;

    TNode* m_pRoot;
};

} // namespace Toshi
#endif
