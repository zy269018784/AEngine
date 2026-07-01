#pragma once

#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <iterator>

template<typename T>
class GList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& Value) : data(Value), next(nullptr), prev(nullptr) {}
        Node(T&& Value) : data(std::move(Value)), next(nullptr), prev(nullptr) {}
    };

    Node* Head;
    Node* Tail;
    size_t Size;

public:
    // ========== 迭代器 ==========
    class Iterator {
    private:
        Node* NodePtr;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* Node = nullptr) : NodePtr(Node) {}

        reference operator*() const { return NodePtr->data; }
        pointer operator->() const { return &NodePtr->data; }

        Iterator& operator++() { NodePtr = NodePtr->next; return *this; }
        Iterator operator++(int) { Iterator Tmp = *this; ++(*this); return Tmp; }
        Iterator& operator--() { NodePtr = NodePtr->prev; return *this; }
        Iterator operator--(int) { Iterator Tmp = *this; --(*this); return Tmp; }

        bool operator==(const Iterator& Other) const { return NodePtr == Other.NodePtr; }
        bool operator!=(const Iterator& Other) const { return NodePtr != Other.NodePtr; }
    };

    class ConstIterator {
    private:
        const Node* NodePtr;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator(const Node* Node = nullptr) : NodePtr(Node) {}
        ConstIterator(const Iterator& It) : NodePtr(It.NodePtr) {}

        reference operator*() const { return NodePtr->data; }
        pointer operator->() const { return &NodePtr->data; }

        ConstIterator& operator++() { NodePtr = NodePtr->next; return *this; }
        ConstIterator operator++(int) { ConstIterator Tmp = *this; ++(*this); return Tmp; }
        ConstIterator& operator--() { NodePtr = NodePtr->prev; return *this; }
        ConstIterator operator--(int) { ConstIterator Tmp = *this; --(*this); return Tmp; }

        bool operator==(const ConstIterator& Other) const { return NodePtr == Other.NodePtr; }
        bool operator!=(const ConstIterator& Other) const { return NodePtr != Other.NodePtr; }
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    // ========== 构造与析构 ==========
    GList() : Head(nullptr), Tail(nullptr), Size(0) {}

    GList(std::initializer_list<T> Init) : GList() {
        for (const auto& Value : Init) {
            Append(Value);
        }
    }

    GList(const GList& Other) : GList() {
        for (const auto& Value : Other) {
            Append(Value);
        }
    }

    GList(GList&& Other) noexcept
        : Head(Other.Head), Tail(Other.Tail), Size(Other.Size) {
        Other.Head = nullptr;
        Other.Tail = nullptr;
        Other.Size = 0;
    }

    ~GList() {
        Clear();
    }

    // ========== 赋值操作 ==========
    GList& operator=(const GList& Other) {
        if (this != &Other) {
            GList Tmp(Other);
            Swap(Tmp);
        }
        return *this;
    }

    GList& operator=(GList&& Other) noexcept {
        if (this != &Other) {
            Clear();
            Head = Other.Head;
            Tail = Other.Tail;
            Size = Other.Size;
            Other.Head = nullptr;
            Other.Tail = nullptr;
            Other.Size = 0;
        }
        return *this;
    }

    GList& operator=(std::initializer_list<T> Init) {
        Clear();
        for (const auto& Value : Init) {
            Append(Value);
        }
        return *this;
    }

    // ========== 容量相关 ==========
    size_t GetSize() const { return Size; }
    bool IsEmpty() const { return Size == 0; }

    // ========== 访问元素 ==========
    T& First() {
        if (IsEmpty()) throw std::out_of_range("GList::First(): list is empty");
        return Head->data;
    }
    const T& First() const {
        if (IsEmpty()) throw std::out_of_range("GList::First(): list is empty");
        return Head->data;
    }

    T& Last() {
        if (IsEmpty()) throw std::out_of_range("GList::Last(): list is empty");
        return Tail->data;
    }
    const T& Last() const {
        if (IsEmpty()) throw std::out_of_range("GList::Last(): list is empty");
        return Tail->data;
    }

    T& At(size_t Index) {
        if (Index >= Size) throw std::out_of_range("GList::At(): index out of range");
        return NodeAt(Index)->data;
    }
    const T& At(size_t Index) const {
        if (Index >= Size) throw std::out_of_range("GList::At(): index out of range");
        return NodeAt(Index)->data;
    }

    T& operator[](size_t Index) { return NodeAt(Index)->data; }
    const T& operator[](size_t Index) const { return NodeAt(Index)->data; }

    // ========== 添加元素 ==========
    void Append(const T& Value) {
        Node* NewNode = new Node(Value);
        if (IsEmpty()) {
            Head = Tail = NewNode;
        } else {
            Tail->next = NewNode;
            NewNode->prev = Tail;
            Tail = NewNode;
        }
        ++Size;
    }

    void Append(T&& Value) {
        Node* NewNode = new Node(std::move(Value));
        if (IsEmpty()) {
            Head = Tail = NewNode;
        } else {
            Tail->next = NewNode;
            NewNode->prev = Tail;
            Tail = NewNode;
        }
        ++Size;
    }

    void Prepend(const T& Value) {
        Node* NewNode = new Node(Value);
        if (IsEmpty()) {
            Head = Tail = NewNode;
        } else {
            NewNode->next = Head;
            Head->prev = NewNode;
            Head = NewNode;
        }
        ++Size;
    }

    void Prepend(T&& Value) {
        Node* NewNode = new Node(std::move(Value));
        if (IsEmpty()) {
            Head = Tail = NewNode;
        } else {
            NewNode->next = Head;
            Head->prev = NewNode;
            Head = NewNode;
        }
        ++Size;
    }

    void Insert(size_t Index, const T& Value) {
        if (Index == 0) {
            Prepend(Value);
        } else if (Index >= Size) {
            Append(Value);
        } else {
            Node* Current = NodeAt(Index);
            Node* NewNode = new Node(Value);
            NewNode->prev = Current->prev;
            NewNode->next = Current;
            Current->prev->next = NewNode;
            Current->prev = NewNode;
            ++Size;
        }
    }

    void Insert(size_t Index, T&& Value) {
        if (Index == 0) {
            Prepend(std::move(Value));
        } else if (Index >= Size) {
            Append(std::move(Value));
        } else {
            Node* Current = NodeAt(Index);
            Node* NewNode = new Node(std::move(Value));
            NewNode->prev = Current->prev;
            NewNode->next = Current;
            Current->prev->next = NewNode;
            Current->prev = NewNode;
            ++Size;
        }
    }

    // ========== 移除元素 ==========
    void RemoveAt(size_t Index) {
        if (Index >= Size) throw std::out_of_range("GList::RemoveAt(): index out of range");
        Node* NodeToRemove = NodeAt(Index);
        RemoveNode(NodeToRemove);
        delete NodeToRemove;
    }

    bool Remove(const T& Value) {
        Node* FoundNode = FindNode(Value);
        if (!FoundNode) return false;
        RemoveNode(FoundNode);
        delete FoundNode;
        return true;
    }

    size_t RemoveAll(const T& Value) {
        size_t Count = 0;
        Node* Current = Head;
        while (Current) {
            Node* Next = Current->next;
            if (Current->data == Value) {
                RemoveNode(Current);
                delete Current;
                ++Count;
            }
            Current = Next;
        }
        return Count;
    }

    void Clear() {
        Node* Current = Head;
        while (Current) {
            Node* Next = Current->next;
            delete Current;
            Current = Next;
        }
        Head = Tail = nullptr;
        Size = 0;
    }

    // ========== 查找 ==========
    Iterator Find(const T& Value) {
        Node* Current = Head;
        while (Current) {
            if (Current->data == Value) {
                return Iterator(Current);
            }
            Current = Current->next;
        }
        return End();
    }

    ConstIterator Find(const T& Value) const {
        Node* Current = Head;
        while (Current) {
            if (Current->data == Value) {
                return ConstIterator(Current);
            }
            Current = Current->next;
        }
        return End();
    }

    size_t IndexOf(const T& Value, size_t From = 0) const {
        Node* Current = NodeAt(From);
        size_t Index = From;
        while (Current) {
            if (Current->data == Value) {
                return Index;
            }
            Current = Current->next;
            ++Index;
        }
        return static_cast<size_t>(-1);
    }

    bool Contains(const T& Value) const {
        return Find(Value) != End();
    }

    // ========== 其他操作 ==========
    void Reverse() {
        Node* Current = Head;
        Node* Temp = nullptr;
        Tail = Head;

        while (Current) {
            Temp = Current->prev;
            Current->prev = Current->next;
            Current->next = Temp;
            Current = Current->prev;
        }

        if (Temp) {
            Head = Temp->prev;
        }
    }

    void Swap(GList& Other) noexcept {
        std::swap(Head, Other.Head);
        std::swap(Tail, Other.Tail);
        std::swap(Size, Other.Size);
    }

    // ========== 迭代器支持 ==========
    Iterator Begin() { return Iterator(Head); }
    Iterator End() { return Iterator(nullptr); }
    ConstIterator Begin() const { return ConstIterator(Head); }
    ConstIterator End() const { return ConstIterator(nullptr); }
    ConstIterator CBegin() const { return ConstIterator(Head); }
    ConstIterator CEnd() const { return ConstIterator(nullptr); }

    Iterator begin() { return Iterator(Head); }
    Iterator end() { return Iterator(nullptr); }
    ConstIterator begin() const { return ConstIterator(Head); }
    ConstIterator end() const { return ConstIterator(nullptr); }
    ConstIterator cbegin() const { return ConstIterator(Head); }
    ConstIterator cend() const { return ConstIterator(nullptr); }

private:
    Node* NodeAt(size_t Index) const {
        if (Index >= Size) return nullptr;

        // 选择从头还是从尾遍历（优化）
        if (Index < Size / 2) {
            Node* Current = Head;
            for (size_t i = 0; i < Index; ++i) {
                Current = Current->next;
            }
            return Current;
        } else {
            Node* Current = Tail;
            for (size_t i = Size - 1; i > Index; --i) {
                Current = Current->prev;
            }
            return Current;
        }
    }

    Node* FindNode(const T& Value) const {
        Node* Current = Head;
        while (Current) {
            if (Current->data == Value) {
                return Current;
            }
            Current = Current->next;
        }
        return nullptr;
    }

    void RemoveNode(Node* NodeToRemove) {
        if (NodeToRemove->prev) {
            NodeToRemove->prev->next = NodeToRemove->next;
        } else {
            Head = NodeToRemove->next;
        }

        if (NodeToRemove->next) {
            NodeToRemove->next->prev = NodeToRemove->prev;
        } else {
            Tail = NodeToRemove->prev;
        }

        --Size;
    }
};