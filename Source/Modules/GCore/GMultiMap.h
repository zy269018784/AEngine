// GMultiMap.h
#pragma once

#include <utility>
#include <stdexcept>
#include <iterator>
#include <functional>

template<typename Key, typename T>
class GMultiMap {
private:
    struct Node {
        Key First;
        T Second;
        Node* Left;
        Node* Right;
        Node* Parent;
        bool IsRed;

        Node(const Key& K, const T& V)
            : First(K), Second(V), Left(nullptr), Right(nullptr),
              Parent(nullptr), IsRed(true) {}

        Node(Key&& K, T&& V)
            : First(std::move(K)), Second(std::move(V)), Left(nullptr),
              Right(nullptr), Parent(nullptr), IsRed(true) {}

        Node(const Key& K, T&& V)
            : First(K), Second(std::move(V)), Left(nullptr),
              Right(nullptr), Parent(nullptr), IsRed(true) {}

        Node(Key&& K, const T& V)
            : First(std::move(K)), Second(V), Left(nullptr),
              Right(nullptr), Parent(nullptr), IsRed(true) {}
    };

    Node* Root;
    size_t Size_;

    // ========== 红黑树辅助函数 ==========
    bool IsRed(Node* N) const {
        return N && N->IsRed;
    }

    void SetRed(Node* N) {
        if (N) N->IsRed = true;
    }

    void SetBlack(Node* N) {
        if (N) N->IsRed = false;
    }

    Node* RotateLeft(Node* H) {
        Node* X = H->Right;
        H->Right = X->Left;
        if (X->Left) {
            X->Left->Parent = H;
        }
        X->Parent = H->Parent;
        X->Left = H;
        H->Parent = X;
        return X;
    }

    Node* RotateRight(Node* H) {
        Node* X = H->Left;
        H->Left = X->Right;
        if (X->Right) {
            X->Right->Parent = H;
        }
        X->Parent = H->Parent;
        X->Right = H;
        H->Parent = X;
        return X;
    }

    void FlipColors(Node* H) {
        H->IsRed = !H->IsRed;
        if (H->Left) H->Left->IsRed = !H->Left->IsRed;
        if (H->Right) H->Right->IsRed = !H->Right->IsRed;
    }

    Node* InsertNode(Node* H, Node* NewNode) {
        if (!H) {
            NewNode->Parent = nullptr;
            return NewNode;
        }

        if (NewNode->First < H->First) {
            H->Left = InsertNode(H->Left, NewNode);
            H->Left->Parent = H;
        } else {
            H->Right = InsertNode(H->Right, NewNode);
            H->Right->Parent = H;
        }

        // 修复红黑树性质
        if (IsRed(H->Right) && !IsRed(H->Left)) {
            H = RotateLeft(H);
        }
        if (IsRed(H->Left) && IsRed(H->Left->Left)) {
            H = RotateRight(H);
        }
        if (IsRed(H->Left) && IsRed(H->Right)) {
            FlipColors(H);
        }

        return H;
    }

    Node* FindMin(Node* N) const {
        while (N && N->Left) {
            N = N->Left;
        }
        return N;
    }

    Node* FindMax(Node* N) const {
        while (N && N->Right) {
            N = N->Right;
        }
        return N;
    }

    Node* FindNode(const Key& K) const {
        Node* Current = Root;
        while (Current) {
            if (K < Current->First) {
                Current = Current->Left;
            } else if (Current->First < K) {
                Current = Current->Right;
            } else {
                return Current;
            }
        }
        return nullptr;
    }

    Node* FindFirstNode(const Key& K) const {
        Node* Current = Root;
        Node* Result = nullptr;
        while (Current) {
            if (K < Current->First) {
                Current = Current->Left;
            } else if (Current->First < K) {
                Current = Current->Right;
            } else {
                Result = Current;
                Current = Current->Left;
            }
        }
        return Result;
    }

    void DeleteNode(Node* N) {
        if (!N) return;

        // 找到替代节点
        Node* Replacement = nullptr;
        if (N->Left && N->Right) {
            Replacement = FindMin(N->Right);
            // 复制数据
            N->First = Replacement->First;
            N->Second = Replacement->Second;
            N = Replacement;
        }

        // 只有一个子节点或没有子节点
        Node* Child = N->Left ? N->Left : N->Right;

        if (Child) {
            // 用子节点替换
            Child->Parent = N->Parent;
            if (!N->Parent) {
                Root = Child;
            } else if (N == N->Parent->Left) {
                N->Parent->Left = Child;
            } else {
                N->Parent->Right = Child;
            }
            // 保持黑色
            if (!IsRed(N)) {
                SetBlack(Child);
            }
        } else if (!N->Parent) {
            Root = nullptr;
        } else {
            // 叶子节点
            if (!IsRed(N)) {
                // 需要修复
                FixDelete(N);
            }
            if (N == N->Parent->Left) {
                N->Parent->Left = nullptr;
            } else {
                N->Parent->Right = nullptr;
            }
        }

        delete N;
        --Size_;
    }

    void FixDelete(Node* N) {
        while (N != Root && !IsRed(N)) {
            if (N == N->Parent->Left) {
                Node* Sibling = N->Parent->Right;
                if (IsRed(Sibling)) {
                    SetBlack(Sibling);
                    SetRed(N->Parent);
                    RotateLeft(N->Parent);
                    Sibling = N->Parent->Right;
                }
                if ((!Sibling->Left || !IsRed(Sibling->Left)) &&
                    (!Sibling->Right || !IsRed(Sibling->Right))) {
                    SetRed(Sibling);
                    N = N->Parent;
                } else {
                    if (!Sibling->Right || !IsRed(Sibling->Right)) {
                        if (Sibling->Left) SetBlack(Sibling->Left);
                        SetRed(Sibling);
                        RotateRight(Sibling);
                        Sibling = N->Parent->Right;
                    }
                    Sibling->IsRed = N->Parent->IsRed;
                    SetBlack(N->Parent);
                    if (Sibling->Right) SetBlack(Sibling->Right);
                    RotateLeft(N->Parent);
                    N = Root;
                }
            } else {
                Node* Sibling = N->Parent->Left;
                if (IsRed(Sibling)) {
                    SetBlack(Sibling);
                    SetRed(N->Parent);
                    RotateRight(N->Parent);
                    Sibling = N->Parent->Left;
                }
                if ((!Sibling->Left || !IsRed(Sibling->Left)) &&
                    (!Sibling->Right || !IsRed(Sibling->Right))) {
                    SetRed(Sibling);
                    N = N->Parent;
                } else {
                    if (!Sibling->Left || !IsRed(Sibling->Left)) {
                        if (Sibling->Right) SetBlack(Sibling->Right);
                        SetRed(Sibling);
                        RotateLeft(Sibling);
                        Sibling = N->Parent->Left;
                    }
                    Sibling->IsRed = N->Parent->IsRed;
                    SetBlack(N->Parent);
                    if (Sibling->Left) SetBlack(Sibling->Left);
                    RotateRight(N->Parent);
                    N = Root;
                }
            }
        }
        if (N) SetBlack(N);
    }

    void ClearNode(Node* N) {
        if (!N) return;
        ClearNode(N->Left);
        ClearNode(N->Right);
        delete N;
    }

    void CopyTree(Node*& Dest, Node* Src, Node* Parent) {
        if (!Src) return;
        Dest = new Node(Src->First, Src->Second);
        Dest->IsRed = Src->IsRed;
        Dest->Parent = Parent;
        CopyTree(Dest->Left, Src->Left, Dest);
        CopyTree(Dest->Right, Src->Right, Dest);
    }

public:
    // ========== 迭代器 ==========
    class Iterator {
    private:
        Node* NodePtr;

        Node* GetNext(Node* N) const {
            if (!N) return nullptr;

            // 如果有右子树，找右子树的最小节点
            if (N->Right) {
                N = N->Right;
                while (N->Left) N = N->Left;
                return N;
            }

            // 否则向上找
            Node* Parent = N->Parent;
            while (Parent && N == Parent->Right) {
                N = Parent;
                Parent = Parent->Parent;
            }
            return Parent;
        }

        Node* GetPrev(Node* N) const {
            if (!N) return nullptr;

            // 如果有左子树，找左子树的最大节点
            if (N->Left) {
                N = N->Left;
                while (N->Right) N = N->Right;
                return N;
            }

            // 否则向上找
            Node* Parent = N->Parent;
            while (Parent && N == Parent->Left) {
                N = Parent;
                Parent = Parent->Parent;
            }
            return Parent;
        }

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::pair<const Key, T>;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator() : NodePtr(nullptr) {}
        Iterator(Node* NodePtr) : NodePtr(NodePtr) {}

        std::pair<const Key&, T&> operator*() {
            return std::pair<const Key&, T&>(NodePtr->First, NodePtr->Second);
        }

        std::pair<const Key&, const T&> operator*() const {
            return std::pair<const Key&, const T&>(NodePtr->First, NodePtr->Second);
        }

        Iterator& operator++() {
            NodePtr = GetNext(NodePtr);
            return *this;
        }

        Iterator operator++(int) {
            Iterator Tmp = *this;
            NodePtr = GetNext(NodePtr);
            return Tmp;
        }

        Iterator& operator--() {
            if (!NodePtr) {
                // 从 end() 退回到最后一个元素需要特殊处理
                // 这里简化处理，假设调用者知道自己在做什么
                return *this;
            }
            NodePtr = GetPrev(NodePtr);
            return *this;
        }

        Iterator operator--(int) {
            Iterator Tmp = *this;
            NodePtr = GetPrev(NodePtr);
            return Tmp;
        }

        bool operator==(const Iterator& Other) const {
            return NodePtr == Other.NodePtr;
        }

        bool operator!=(const Iterator& Other) const {
            return NodePtr != Other.NodePtr;
        }
    };

    class ConstIterator {
    private:
        const Node* NodePtr;

        const Node* GetNext(const Node* N) const {
            if (!N) return nullptr;

            if (N->Right) {
                N = N->Right;
                while (N->Left) N = N->Left;
                return N;
            }

            const Node* Parent = N->Parent;
            while (Parent && N == Parent->Right) {
                N = Parent;
                Parent = Parent->Parent;
            }
            return Parent;
        }

        const Node* GetPrev(const Node* N) const {
            if (!N) return nullptr;

            if (N->Left) {
                N = N->Left;
                while (N->Right) N = N->Right;
                return N;
            }

            const Node* Parent = N->Parent;
            while (Parent && N == Parent->Left) {
                N = Parent;
                Parent = Parent->Parent;
            }
            return Parent;
        }

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::pair<const Key, T>;
        using difference_type = ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        ConstIterator() : NodePtr(nullptr) {}
        ConstIterator(const Node* NodePtr) : NodePtr(NodePtr) {}
        ConstIterator(const Iterator& It) : NodePtr(It.NodePtr) {}

        std::pair<const Key&, const T&> operator*() const {
            return std::pair<const Key&, const T&>(NodePtr->First, NodePtr->Second);
        }

        ConstIterator& operator++() {
            NodePtr = GetNext(NodePtr);
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator Tmp = *this;
            NodePtr = GetNext(NodePtr);
            return Tmp;
        }

        ConstIterator& operator--() {
            if (!NodePtr) {
                return *this;
            }
            NodePtr = GetPrev(NodePtr);
            return *this;
        }

        ConstIterator operator--(int) {
            ConstIterator Tmp = *this;
            NodePtr = GetPrev(NodePtr);
            return Tmp;
        }

        bool operator==(const ConstIterator& Other) const {
            return NodePtr == Other.NodePtr;
        }

        bool operator!=(const ConstIterator& Other) const {
            return NodePtr != Other.NodePtr;
        }
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    // ========== 构造与析构 ==========
    GMultiMap() : Root(nullptr), Size_(0) {}

    GMultiMap(std::initializer_list<std::pair<Key, T>> Init) : GMultiMap() {
        for (const auto& Item : Init) {
            Insert(Item.first, Item.second);
        }
    }

    GMultiMap(const GMultiMap& Other) : GMultiMap() {
        CopyTree(Root, Other.Root, nullptr);
        Size_ = Other.Size_;
    }

    GMultiMap(GMultiMap&& Other) noexcept
        : Root(Other.Root), Size_(Other.Size_) {
        Other.Root = nullptr;
        Other.Size_ = 0;
    }

    ~GMultiMap() {
        Clear();
    }

    // ========== 赋值操作 ==========
    GMultiMap& operator=(const GMultiMap& Other) {
        if (this != &Other) {
            GMultiMap Tmp(Other);
            Swap(Tmp);
        }
        return *this;
    }

    GMultiMap& operator=(GMultiMap&& Other) noexcept {
        if (this != &Other) {
            Clear();
            Root = Other.Root;
            Size_ = Other.Size_;
            Other.Root = nullptr;
            Other.Size_ = 0;
        }
        return *this;
    }

    GMultiMap& operator=(std::initializer_list<std::pair<Key, T>> Init) {
        Clear();
        for (const auto& Item : Init) {
            Insert(Item.first, Item.second);
        }
        return *this;
    }

    // ========== 容量相关 ==========
    size_t GetSize() const { return Size_; }
    bool IsEmpty() const { return Size_ == 0; }

    // ========== 插入操作 ==========
    void Insert(const Key& K, const T& V) {
        Node* NewNode = new Node(K, V);
        Root = InsertNode(Root, NewNode);
        if (Root) {
            Root->Parent = nullptr;
            SetBlack(Root);
        }
        ++Size_;
    }

    void Insert(const Key& K, T&& V) {
        Node* NewNode = new Node(K, std::move(V));
        Root = InsertNode(Root, NewNode);
        if (Root) {
            Root->Parent = nullptr;
            SetBlack(Root);
        }
        ++Size_;
    }

    void Insert(Key&& K, const T& V) {
        Node* NewNode = new Node(std::move(K), V);
        Root = InsertNode(Root, NewNode);
        if (Root) {
            Root->Parent = nullptr;
            SetBlack(Root);
        }
        ++Size_;
    }

    void Insert(Key&& K, T&& V) {
        Node* NewNode = new Node(std::move(K), std::move(V));
        Root = InsertNode(Root, NewNode);
        if (Root) {
            Root->Parent = nullptr;
            SetBlack(Root);
        }
        ++Size_;
    }

    void Insert(const std::pair<Key, T>& Pair) {
        Insert(Pair.first, Pair.second);
    }

    void Insert(std::pair<Key, T>&& Pair) {
        Insert(std::move(Pair.first), std::move(Pair.second));
    }

    // ========== 查找操作 ==========
    std::vector<T> Values(const Key& K) const {
        std::vector<T> Result;
        Node* Current = FindFirstNode(K);
        while (Current && Current->First == K) {
            Result.push_back(Current->Second);
            Current = GetNext(Current);
        }
        return Result;
    }

    T Value(const Key& K, const T& DefaultValue = T()) const {
        Node* Node = FindNode(K);
        if (Node) return Node->Second;
        return DefaultValue;
    }

    size_t Count(const Key& K) const {
        size_t Count = 0;
        Node* Current = FindFirstNode(K);
        while (Current && Current->First == K) {
            ++Count;
            Current = GetNext(Current);
        }
        return Count;
    }

    bool Contains(const Key& K) const {
        return FindNode(K) != nullptr;
    }

    bool Contains(const Key& K, const T& V) const {
        Node* Current = FindFirstNode(K);
        while (Current && Current->First == K) {
            if (Current->Second == V) {
                return true;
            }
            Current = GetNext(Current);
        }
        return false;
    }

    // ========== 移除操作 ==========
    size_t Remove(const Key& K) {
        size_t RemovedCount = 0;
        Node* Current = FindFirstNode(K);
        while (Current && Current->First == K) {
            Node* Next = GetNext(Current);
            DeleteNode(Current);
            ++RemovedCount;
            Current = Next;
        }
        return RemovedCount;
    }

    bool Remove(const Key& K, const T& V) {
        Node* Current = FindFirstNode(K);
        while (Current && Current->First == K) {
            if (Current->Second == V) {
                DeleteNode(Current);
                return true;
            }
            Current = GetNext(Current);
        }
        return false;
    }

    void Clear() {
        ClearNode(Root);
        Root = nullptr;
        Size_ = 0;
    }

    // ========== 其他操作 ==========
    void Swap(GMultiMap& Other) noexcept {
        std::swap(Root, Other.Root);
        std::swap(Size_, Other.Size_);
    }

    std::vector<Key> Keys() const {
        std::vector<Key> Result;
        for (const auto& Item : *this) {
            Result.push_back(Item.first);
        }
        return Result;
    }

    std::vector<T> AllValues() const {
        std::vector<T> Result;
        for (const auto& Item : *this) {
            Result.push_back(Item.second);
        }
        return Result;
    }

    // ========== 迭代器支持 ==========
    Iterator Begin() {
        Node* Min = FindMin(Root);
        return Iterator(Min);
    }

    Iterator End() {
        return Iterator(nullptr);
    }

    ConstIterator Begin() const {
        Node* Min = FindMin(Root);
        return ConstIterator(Min);
    }

    ConstIterator End() const {
        return ConstIterator(nullptr);
    }

    ConstIterator CBegin() const {
        return Begin();
    }

    ConstIterator CEnd() const {
        return End();
    }

    Iterator begin() { return Begin(); }
    Iterator end() { return End(); }
    ConstIterator begin() const { return Begin(); }
    ConstIterator end() const { return End(); }
    ConstIterator cbegin() const { return CBegin(); }
    ConstIterator cend() const { return CEnd(); }

private:
    // ========== 辅助函数 ==========
    Node* GetNext(Node* N) const {
        if (!N) return nullptr;

        if (N->Right) {
            N = N->Right;
            while (N->Left) N = N->Left;
            return N;
        }

        Node* Parent = N->Parent;
        while (Parent && N == Parent->Right) {
            N = Parent;
            Parent = Parent->Parent;
        }
        return Parent;
    }
};