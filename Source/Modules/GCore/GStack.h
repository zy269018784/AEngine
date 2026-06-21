// GStack.h
#pragma once

#include <initializer_list>
#include <stdexcept>
#include <iterator>

template<typename T>
class GStack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& Value) : data(Value), next(nullptr) {}
        Node(T&& Value) : data(std::move(Value)), next(nullptr) {}
    };

    Node* Top_;
    size_t Size_;

public:
    // ========== 迭代器 ==========
    class Iterator {
    private:
        Node* NodePtr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* Node = nullptr) : NodePtr(Node) {}

        reference operator*() const { return NodePtr->data; }
        pointer operator->() const { return &NodePtr->data; }

        Iterator& operator++() { NodePtr = NodePtr->next; return *this; }
        Iterator operator++(int) { Iterator Tmp = *this; ++(*this); return Tmp; }

        bool operator==(const Iterator& Other) const { return NodePtr == Other.NodePtr; }
        bool operator!=(const Iterator& Other) const { return NodePtr != Other.NodePtr; }
    };

    class ConstIterator {
    private:
        const Node* NodePtr;
    public:
        using iterator_category = std::forward_iterator_tag;
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

        bool operator==(const ConstIterator& Other) const { return NodePtr == Other.NodePtr; }
        bool operator!=(const ConstIterator& Other) const { return NodePtr != Other.NodePtr; }
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    // ========== 构造与析构 ==========
    GStack() : Top_(nullptr), Size_(0) {}

    GStack(std::initializer_list<T> Init) : GStack() {
        for (const auto& Value : Init) {
            Push(Value);
        }
    }

    GStack(const GStack& Other) : GStack() {
        // 需要从底部到顶部复制，以保持顺序
        GStack<T> Temp;
        for (const auto& Value : Other) {
            Temp.Push(Value);
        }
        // 反转顺序
        while (!Temp.IsEmpty()) {
            Push(Temp.Pop());
        }
    }

    GStack(GStack&& Other) noexcept
        : Top_(Other.Top_), Size_(Other.Size_) {
        Other.Top_ = nullptr;
        Other.Size_ = 0;
    }

    ~GStack() {
        Clear();
    }

    // ========== 赋值操作 ==========
    GStack& operator=(const GStack& Other) {
        if (this != &Other) {
            GStack Tmp(Other);
            Swap(Tmp);
        }
        return *this;
    }

    GStack& operator=(GStack&& Other) noexcept {
        if (this != &Other) {
            Clear();
            Top_ = Other.Top_;
            Size_ = Other.Size_;
            Other.Top_ = nullptr;
            Other.Size_ = 0;
        }
        return *this;
    }

    GStack& operator=(std::initializer_list<T> Init) {
        Clear();
        for (const auto& Value : Init) {
            Push(Value);
        }
        return *this;
    }

    // ========== 容量相关 ==========
    size_t GetSize() const { return Size_; }
    bool IsEmpty() const { return Size_ == 0; }

    // ========== 栈操作 ==========
    void Push(const T& Value) {
        Node* NewNode = new Node(Value);
        NewNode->next = Top_;
        Top_ = NewNode;
        ++Size_;
    }

    void Push(T&& Value) {
        Node* NewNode = new Node(std::move(Value));
        NewNode->next = Top_;
        Top_ = NewNode;
        ++Size_;
    }

    T Pop() {
        if (IsEmpty()) throw std::out_of_range("GStack::Pop(): stack is empty");

        Node* NodeToRemove = Top_;
        T Value = std::move(NodeToRemove->data);
        Top_ = Top_->next;

        delete NodeToRemove;
        --Size_;
        return Value;
    }

    T& Top() {
        if (IsEmpty()) throw std::out_of_range("GStack::Top(): stack is empty");
        return Top_->data;
    }

    const T& Top() const {
        if (IsEmpty()) throw std::out_of_range("GStack::Top(): stack is empty");
        return Top_->data;
    }

    // ========== 访问元素 ==========
    T& At(size_t Index) {
        if (Index >= Size_) throw std::out_of_range("GStack::At(): index out of range");
        return NodeAt(Index)->data;
    }

    const T& At(size_t Index) const {
        if (Index >= Size_) throw std::out_of_range("GStack::At(): index out of range");
        return NodeAt(Index)->data;
    }

    T& operator[](size_t Index) { return NodeAt(Index)->data; }
    const T& operator[](size_t Index) const { return NodeAt(Index)->data; }

    // ========== 查找 ==========
    Iterator Find(const T& Value) {
        Node* Current = Top_;
        while (Current) {
            if (Current->data == Value) {
                return Iterator(Current);
            }
            Current = Current->next;
        }
        return End();
    }

    ConstIterator Find(const T& Value) const {
        Node* Current = Top_;
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
    void Clear() {
        Node* Current = Top_;
        while (Current) {
            Node* Next = Current->next;
            delete Current;
            Current = Next;
        }
        Top_ = nullptr;
        Size_ = 0;
    }

    void Swap(GStack& Other) noexcept {
        std::swap(Top_, Other.Top_);
        std::swap(Size_, Other.Size_);
    }

    // ========== 迭代器支持 ==========
    Iterator Begin() { return Iterator(Top_); }
    Iterator End() { return Iterator(nullptr); }
    ConstIterator Begin() const { return ConstIterator(Top_); }
    ConstIterator End() const { return ConstIterator(nullptr); }
    ConstIterator CBegin() const { return ConstIterator(Top_); }
    ConstIterator CEnd() const { return ConstIterator(nullptr); }

    Iterator begin() { return Iterator(Top_); }
    Iterator end() { return Iterator(nullptr); }
    ConstIterator begin() const { return ConstIterator(Top_); }
    ConstIterator end() const { return ConstIterator(nullptr); }
    ConstIterator cbegin() const { return ConstIterator(Top_); }
    ConstIterator cend() const { return ConstIterator(nullptr); }

private:
    Node* NodeAt(size_t Index) const {
        if (Index >= Size_) return nullptr;

        Node* Current = Top_;
        for (size_t i = 0; i < Index; ++i) {
            Current = Current->next;
        }
        return Current;
    }
};