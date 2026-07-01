// GQueue.h
#pragma once

#include <initializer_list>
#include <stdexcept>
#include <iterator>

template<typename T>
class GQueue {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& Value) : data(Value), next(nullptr) {}
        Node(T&& Value) : data(std::move(Value)), next(nullptr) {}
    };

    Node* Head_;
    Node* Tail_;
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
    GQueue() : Head_(nullptr), Tail_(nullptr), Size_(0) {}

    GQueue(std::initializer_list<T> Init) : GQueue() {
        for (const auto& Value : Init) {
            Enqueue(Value);
        }
    }

    GQueue(const GQueue& Other) : GQueue() {
        for (const auto& Value : Other) {
            Enqueue(Value);
        }
    }

    GQueue(GQueue&& Other) noexcept
        : Head_(Other.Head_), Tail_(Other.Tail_), Size_(Other.Size_) {
        Other.Head_ = nullptr;
        Other.Tail_ = nullptr;
        Other.Size_ = 0;
    }

    ~GQueue() {
        Clear();
    }

    // ========== 赋值操作 ==========
    GQueue& operator=(const GQueue& Other) {
        if (this != &Other) {
            GQueue Tmp(Other);
            Swap(Tmp);
        }
        return *this;
    }

    GQueue& operator=(GQueue&& Other) noexcept {
        if (this != &Other) {
            Clear();
            Head_ = Other.Head_;
            Tail_ = Other.Tail_;
            Size_ = Other.Size_;
            Other.Head_ = nullptr;
            Other.Tail_ = nullptr;
            Other.Size_ = 0;
        }
        return *this;
    }

    GQueue& operator=(std::initializer_list<T> Init) {
        Clear();
        for (const auto& Value : Init) {
            Enqueue(Value);
        }
        return *this;
    }

    // ========== 容量相关 ==========
    size_t GetSize() const { return Size_; }
    bool IsEmpty() const { return Size_ == 0; }

    // ========== 队列操作 ==========
    void Enqueue(const T& Value) {
        Node* NewNode = new Node(Value);
        if (IsEmpty()) {
            Head_ = Tail_ = NewNode;
        } else {
            Tail_->next = NewNode;
            Tail_ = NewNode;
        }
        ++Size_;
    }

    void Enqueue(T&& Value) {
        Node* NewNode = new Node(std::move(Value));
        if (IsEmpty()) {
            Head_ = Tail_ = NewNode;
        } else {
            Tail_->next = NewNode;
            Tail_ = NewNode;
        }
        ++Size_;
    }

    T Dequeue() {
        if (IsEmpty()) throw std::out_of_range("GQueue::Dequeue(): queue is empty");

        Node* NodeToRemove = Head_;
        T Value = std::move(NodeToRemove->data);
        Head_ = Head_->next;

        if (Head_ == nullptr) {
            Tail_ = nullptr;
        }

        delete NodeToRemove;
        --Size_;
        return Value;
    }

    T& Head() {
        if (IsEmpty()) throw std::out_of_range("GQueue::Head(): queue is empty");
        return Head_->data;
    }

    const T& Head() const {
        if (IsEmpty()) throw std::out_of_range("GQueue::Head(): queue is empty");
        return Head_->data;
    }

    T& Tail() {
        if (IsEmpty()) throw std::out_of_range("GQueue::Tail(): queue is empty");
        return Tail_->data;
    }

    const T& Tail() const {
        if (IsEmpty()) throw std::out_of_range("GQueue::Tail(): queue is empty");
        return Tail_->data;
    }

    // ========== 访问元素 ==========
    T& At(size_t Index) {
        if (Index >= Size_) throw std::out_of_range("GQueue::At(): index out of range");
        return NodeAt(Index)->data;
    }

    const T& At(size_t Index) const {
        if (Index >= Size_) throw std::out_of_range("GQueue::At(): index out of range");
        return NodeAt(Index)->data;
    }

    T& operator[](size_t Index) { return NodeAt(Index)->data; }
    const T& operator[](size_t Index) const { return NodeAt(Index)->data; }

    // ========== 查找 ==========
    Iterator Find(const T& Value) {
        Node* Current = Head_;
        while (Current) {
            if (Current->data == Value) {
                return Iterator(Current);
            }
            Current = Current->next;
        }
        return End();
    }

    ConstIterator Find(const T& Value) const {
        Node* Current = Head_;
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
        Node* Current = Head_;
        while (Current) {
            Node* Next = Current->next;
            delete Current;
            Current = Next;
        }
        Head_ = Tail_ = nullptr;
        Size_ = 0;
    }

    void Swap(GQueue& Other) noexcept {
        std::swap(Head_, Other.Head_);
        std::swap(Tail_, Other.Tail_);
        std::swap(Size_, Other.Size_);
    }

    // ========== 迭代器支持 ==========
    Iterator Begin() { return Iterator(Head_); }
    Iterator End() { return Iterator(nullptr); }
    ConstIterator Begin() const { return ConstIterator(Head_); }
    ConstIterator End() const { return ConstIterator(nullptr); }
    ConstIterator CBegin() const { return ConstIterator(Head_); }
    ConstIterator CEnd() const { return ConstIterator(nullptr); }

    Iterator begin() { return Iterator(Head_); }
    Iterator end() { return Iterator(nullptr); }
    ConstIterator begin() const { return ConstIterator(Head_); }
    ConstIterator end() const { return ConstIterator(nullptr); }
    ConstIterator cbegin() const { return ConstIterator(Head_); }
    ConstIterator cend() const { return ConstIterator(nullptr); }

private:
    Node* NodeAt(size_t Index) const {
        if (Index >= Size_) return nullptr;

        Node* Current = Head_;
        for (size_t i = 0; i < Index; ++i) {
            Current = Current->next;
        }
        return Current;
    }
};