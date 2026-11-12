// Toshi::TGenericDList / TGenericPriList / TGenericNodeList - the kernel's untyped intrusive lists.
// Reconstructed from TKernelInterface.dll (members are protected in the binary: mangled 'I').
// Kernel-internal header: only the TKernelInterface sources include it.
#ifndef TGENERICLISTS_H
#define TGENERICLISTS_H

namespace Toshi {

class TThreadManager;
class TFileManager;
class TGenericEmitter;
class TGenericListener;

// Plain doubly linked list; the list object itself is the root node (End() == this).
class __declspec(dllexport) TGenericDList
{
public:
    class __declspec(dllexport) TNode
    {
    public:
        enum TUninitialised { UNINITIALISED };
        // operator= is the implicit member-wise copy (exported through the class).

    protected:
        TNode(TUninitialised) {}
        TNode();
        void Remove();
        void InsertAfter(TNode* n);
        void InsertBefore(TNode* n);
        bool IsLinked() const;
        TNode* Prev() const;
        TNode* Next() const;
        void Reset();

        friend class TGenericDList;
        friend class TThreadManager;    // the thread list links its nodes by hand
        friend class TFileManager;      // so does the file manager
        friend class TGenericEmitter;   // and the emitter walks its listeners
        TNode* m_pNext;     // +0
        TNode* m_pPrev;     // +4
    };

protected:
    TGenericDList() {}
    ~TGenericDList() { RemoveAll(); }
    void InsertSegmentAtTail(TNode* first, TNode* last);
    void InsertSegmentAtHead(TNode* first, TNode* last);
    static void __stdcall RemoveSegment(TNode* first, TNode* last);
    static void __stdcall InsertSegmentAfter(TNode* first, TNode* last, TNode* after);
    static void __stdcall InsertSegmentBefore(TNode* first, TNode* last, TNode* before);
    void RemoveAll();
    void RemoveTail();
    void RemoveHead();
    void InsertTail(TNode* n);
    void InsertHead(TNode* n);
    bool IsEmpty() const;
    const TNode* REnd() const;
    TNode* RBegin() const;
    const TNode* End() const;
    TNode* Begin() const;
    TNode* Tail() const;
    TNode* Head() const;

    friend class TGenericPriList;
    friend class TThreadManager;
    friend class TFileManager;
    friend class TGenericEmitter;
    TNode m_oRoot;
};

inline TGenericDList::TNode::TNode()
{
    m_pNext = this;
    m_pPrev = this;
}

// Priority list: nodes carry a priority and are kept sorted.
class __declspec(dllexport) TGenericPriList
{
public:
    class __declspec(dllexport) TNode
    {
    public:
        enum TUninitialised { UNINITIALISED };
        // operator= is the implicit member-wise copy (exported through the class).

    protected:
        void Remove()
        {
            m_pPrev->m_pNext = m_pNext;
            m_pNext->m_pPrev = m_pPrev;
            m_pNext = this;
            m_pPrev = this;
        }
        void SetPriority(int p);
        int GetPriority() const;
        bool IsLinked() const;
        TNode* Prev() const;
        TNode* Next() const;
        TNode(TUninitialised) {}
        TNode()
        {
            m_pNext = this;
            m_pPrev = this;
            m_iPriority = 0;
        }
        void Reset();

        friend class TGenericPriList;
        friend class TGenericEmitter;
        friend class TGenericListener;
        TNode* m_pNext;     // +0
        TNode* m_pPrev;     // +4
        int    m_iPriority; // +8
    };

public:
    TGenericPriList();
    ~TGenericPriList();

protected:
    void RemoveAll();
    void RemoveTail();
    void RemoveHead();
    void Insert(TNode* n, int priority);
    bool IsEmpty() const;
    const TNode* REnd() const;
    TNode* RBegin() const;
    const TNode* End() const;
    TNode* Begin() const;
    TNode* Tail() const;
    TNode* Head() const;
    void Insert(TNode* n);
    void InsertTail(TNode* n);
    void InsertHead(TNode* n);
    void SetPriority(TNode* n, int priority);

    friend class TGenericListener;
    TNode m_oRoot;
};

// Doubly linked list of polymorphic nodes with an owner pointer and a count.
class __declspec(dllexport) TGenericNodeList
{
public:
    class TNode
    {
    public:
        TNode& operator=(const TNode& o);
        TNode(const TNode& o);
        virtual ~TNode();
        TNode();
        TGenericNodeList* GetList() const;
        bool IsLinked() const;
        TNode* Prev() const;
        TNode* Next() const;

    protected:
        TGenericNodeList* SetList(TGenericNodeList* list);

        friend class TGenericNodeList;
        TGenericNodeList* m_pList;      // +4
        TNode* m_pNext;                 // +8
        TNode* m_pPrev;                 // +0xC
    };

    class Iterator
    {
    public:
        Iterator& operator=(const Iterator& o);
        Iterator(const Iterator& o);
        bool IsNull();
        bool operator!();
        bool operator!=(Iterator& o) const;
        bool operator==(Iterator& o) const;
        Iterator& operator--();
        Iterator operator++(int);
        Iterator& operator++();
        operator TNode*() const;
        TNode* operator->() const;
        TNode& operator*() const;
        ~Iterator();
        Iterator(TNode* n);
        Iterator();

        TNode* m_pNode;
    };

protected:
    TGenericNodeList();
    ~TGenericNodeList();
    void InsertBefore(TNode& ref, TNode& n);
    void InsertAfter(TNode& ref, TNode& n);
    TNode* Remove(TNode& n);
    void RemoveAll();
    void Delete(TNode& n);
    void DeleteHead();
    void DeleteTail();
    void DeleteAll();
    Iterator MakeIterator(TNode* n);
    Iterator REnd() const;
    Iterator RBegin() const;
    Iterator End() const;
    Iterator Begin() const;
    bool IsValid(const TNode* n) const;
    bool IsEmpty() const;
    int Count() const;
    void InsertTail(TNode& n);
    void InsertHead(TNode& n);
    TNode* RemoveTail();
    TNode* RemoveHead();
    TNode* Tail() const;
    TNode* Head() const;

private:
    TGenericNodeList(TGenericNodeList& other);
    TGenericNodeList& operator=(TGenericNodeList& other);

    TNode m_oRoot;      // +0
    int   m_iCount;     // +0x10
};

} // namespace Toshi
#endif
