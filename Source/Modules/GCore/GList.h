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

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        Node(T&& value) : data(std::move(value)), next(nullptr), prev(nullptr) {}
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

        Iterator(Node* node = nullptr) : NodePtr(node) {}

        reference operator*() const { return NodePtr->data; }
        pointer operator->() const { return &NodePtr->data; }

        Iterator& operator++() { NodePtr = NodePtr->next; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() { NodePtr = NodePtr->prev; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

        bool operator==(const Iterator& other) const { return NodePtr == other.NodePtr; }
        bool operator!=(const Iterator& other) const { return NodePtr != other.NodePtr; }
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

        ConstIterator(const Node* node = nullptr) : NodePtr(node) {}
        ConstIterator(const Iterator& it) : NodePtr(it.NodePtr) {}

        reference operator*() const { return NodePtr->data; }
        pointer operator->() const { return &NodePtr->data; }

        ConstIterator& operator++() { NodePtr = NodePtr->next; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }
        ConstIterator& operator--() { NodePtr = NodePtr->prev; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp = *this; --(*this); return tmp; }

        bool operator==(const ConstIterator& other) const { return NodePtr == other.NodePtr; }
        bool operator!=(const ConstIterator& other) const { return NodePtr != other.NodePtr; }
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    // ========== 构造与析构 ==========
    GList() : Head(nullptr), Tail(nullptr), Size(0) {}

    GList(std::initializer_list<T> init) : GList() {
        for (const auto& value : init) {
            Append(value);
        }
    }

    GList(const GList& other) : GList() {
        for (const auto& value : other) {
            Append(value);
        }
    }

    GList(GList&& other) noexcept
        : Head(other.Head), Tail(other.Tail), Size(other.Size) {
        other.Head = nullptr;
        other.Tail = nullptr;
        other.Size = 0;
    }

    ~GList() {
        Clear();
    }

    // ========== 赋值操作 ==========
    GList& operator=(const GList& other) {
        if (this != &other) {
            GList tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    GList& operator=(GList&& other) noexcept {
        if (this != &other) {
            Clear();
            Head = other.Head;
            Tail = other.Tail;
            Size = other.Size;
            other.Head = nullptr;
            other.Tail = nullptr;
            other.Size = 0;
        }
        return *this;
    }

    GList& operator=(std::initializer_list<T> init) {
        Clear();
        for (const auto& value : init) {
            Append(value);
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

    T& At(size_t index) {
        if (index >= Size) throw std::out_of_range("GList::At(): index out of range");
        return NodeAt(index)->data;
    }
    const T& At(size_t index) const {
        if (index >= Size) throw std::out_of_range("GList::At(): index out of range");
        return NodeAt(index)->data;
    }

    T& operator[](size_t index) { return NodeAt(index)->data; }
    const T& operator[](size_t index) const { return NodeAt(index)->data; }

    // ========== 添加元素 ==========
    void Append(const T& value) {
        Node* newNode = new Node(value);
        if (IsEmpty()) {
            Head = Tail = newNode;
        } else {
            Tail->next = newNode;
            newNode->prev = Tail;
            Tail = newNode;
        }
        ++Size;
    }

    void Append(T&& value) {
        Node* newNode = new Node(std::move(value));
        if (IsEmpty()) {
            Head = Tail = newNode;
        } else {
            Tail->next = newNode;
            newNode->prev = Tail;
            Tail = newNode;
        }
        ++Size;
    }

    void Prepend(const T& value) {
        Node* newNode = new Node(value);
        if (IsEmpty()) {
            Head = Tail = newNode;
        } else {
            newNode->next = Head;
            Head->prev = newNode;
            Head = newNode;
        }
        ++Size;
    }

    void Prepend(T&& value) {
        Node* newNode = new Node(std::move(value));
        if (IsEmpty()) {
            Head = Tail = newNode;
        } else {
            newNode->next = Head;
            Head->prev = newNode;
            Head = newNode;
        }
        ++Size;
    }

    void Insert(size_t index, const T& value) {
        if (index == 0) {
            Prepend(value);
        } else if (index >= Size) {
            Append(value);
        } else {
            Node* current = NodeAt(index);
            Node* newNode = new Node(value);
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
            ++Size;
        }
    }

    void Insert(size_t index, T&& value) {
        if (index == 0) {
            Prepend(std::move(value));
        } else if (index >= Size) {
            Append(std::move(value));
        } else {
            Node* current = NodeAt(index);
            Node* newNode = new Node(std::move(value));
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
            ++Size;
        }
    }

    // ========== 移除元素 ==========
    void RemoveAt(size_t index) {
        if (index >= Size) throw std::out_of_range("GList::RemoveAt(): index out of range");
        Node* nodeToRemove = NodeAt(index);
        RemoveNode(nodeToRemove);
        delete nodeToRemove;
    }

    bool Remove(const T& value) {
        Node* node = FindNode(value);
        if (!node) return false;
        RemoveNode(node);
        delete node;
        return true;
    }

    size_t RemoveAll(const T& value) {
        size_t count = 0;
        Node* current = Head;
        while (current) {
            Node* next = current->next;
            if (current->data == value) {
                RemoveNode(current);
                delete current;
                ++count;
            }
            current = next;
        }
        return count;
    }

    void Clear() {
        Node* current = Head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        Head = Tail = nullptr;
        Size = 0;
    }

    // ========== 查找 ==========
    Iterator Find(const T& value) {
        Node* current = Head;
        while (current) {
            if (current->data == value) {
                return Iterator(current);
            }
            current = current->next;
        }
        return End();
    }

    ConstIterator Find(const T& value) const {
        Node* current = Head;
        while (current) {
            if (current->data == value) {
                return ConstIterator(current);
            }
            current = current->next;
        }
        return End();
    }

    size_t IndexOf(const T& value, size_t from = 0) const {
        Node* current = NodeAt(from);
        size_t index = from;
        while (current) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            ++index;
        }
        return static_cast<size_t>(-1);
    }

    bool Contains(const T& value) const {
        return Find(value) != End();
    }

    // ========== 其他操作 ==========
    void Reverse() {
        Node* current = Head;
        Node* temp = nullptr;
        Tail = Head;

        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp) {
            Head = temp->prev;
        }
    }

    void Swap(GList& other) noexcept {
        std::swap(Head, other.Head);
        std::swap(Tail, other.Tail);
        std::swap(Size, other.Size);
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
    Node* NodeAt(size_t index) const {
        if (index >= Size) return nullptr;

        // 选择从头还是从尾遍历（优化）
        if (index < Size / 2) {
            Node* current = Head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current;
        } else {
            Node* current = Tail;
            for (size_t i = Size - 1; i > index; --i) {
                current = current->prev;
            }
            return current;
        }
    }

    Node* FindNode(const T& value) const {
        Node* current = Head;
        while (current) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void RemoveNode(Node* node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            Head = node->next;
        }

        if (node->next) {
            node->next->prev = node->prev;
        } else {
            Tail = node->prev;
        }

        --Size;
    }
};