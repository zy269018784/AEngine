// GMultiHash.h
#pragma once

#include <vector>
#include <list>
#include <utility>
#include <stdexcept>
#include <iterator>
#include <functional>

template<typename Key, typename T>
class GMultiHash {
private:
    struct Node {
        Key First;
        T Second;
        Node* Next;

        Node(const Key& K, const T& V) : First(K), Second(V), Next(nullptr) {}
        Node(Key&& K, T&& V) : First(std::move(K)), Second(std::move(V)), Next(nullptr) {}
        Node(const Key& K, T&& V) : First(K), Second(std::move(V)), Next(nullptr) {}
        Node(Key&& K, const T& V) : First(std::move(K)), Second(V), Next(nullptr) {}
    };

    std::vector<Node*> Buckets;
    size_t Size_;
    size_t BucketCount;

    static constexpr size_t DEFAULT_BUCKET_COUNT = 16;
    static constexpr float LOAD_FACTOR = 0.75f;

    size_t Hash(const Key& K) const {
        return std::hash<Key>{}(K);
    }

    size_t GetBucketIndex(const Key& K) const {
        return Hash(K) % Buckets.size();
    }

    Node* FindNode(size_t Index, const Key& K) {
        Node* Current = Buckets[Index];
        while (Current) {
            if (Current->First == K) {
                return Current;
            }
            Current = Current->Next;
        }
        return nullptr;
    }

    const Node* FindNode(size_t Index, const Key& K) const {
        Node* Current = Buckets[Index];
        while (Current) {
            if (Current->First == K) {
                return Current;
            }
            Current = Current->Next;
        }
        return nullptr;
    }

    void Rehash(size_t NewBucketCount) {
        std::vector<Node*> OldBuckets = std::move(Buckets);
        Buckets.resize(NewBucketCount);
        BucketCount = NewBucketCount;

        for (size_t i = 0; i < Buckets.size(); ++i) {
            Buckets[i] = nullptr;
        }

        for (Node* NodePtr : OldBuckets) {
            while (NodePtr) {
                Node* Next = NodePtr->Next;
                size_t NewIndex = GetBucketIndex(NodePtr->First);
                NodePtr->Next = Buckets[NewIndex];
                Buckets[NewIndex] = NodePtr;
                NodePtr = Next;
            }
        }
    }

    void CheckRehash() {
        if (Size_ > Buckets.size() * LOAD_FACTOR) {
            Rehash(Buckets.size() * 2);
        }
    }

public:
    // ========== 迭代器 ==========
    class Iterator {
    private:
        Node* NodePtr;
        std::vector<Node*>* BucketPtr;
        size_t CurrentBucket;
        size_t TotalBuckets;

        void AdvanceToNextNode() {
            if (NodePtr && NodePtr->Next) {
                NodePtr = NodePtr->Next;
                return;
            }

            // 找下一个非空桶
            for (size_t i = CurrentBucket + 1; i < TotalBuckets; ++i) {
                if ((*BucketPtr)[i]) {
                    CurrentBucket = i;
                    NodePtr = (*BucketPtr)[i];
                    return;
                }
            }

            NodePtr = nullptr;
            CurrentBucket = TotalBuckets;
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const Key, T>;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator() : NodePtr(nullptr), BucketPtr(nullptr),
                     CurrentBucket(0), TotalBuckets(0) {}

        Iterator(Node* NodePtr, std::vector<Node*>* BucketPtr,
                 size_t CurrentBucket, size_t TotalBuckets)
            : NodePtr(NodePtr), BucketPtr(BucketPtr),
              CurrentBucket(CurrentBucket), TotalBuckets(TotalBuckets) {}

        // 返回键值对的引用（使用 std::pair 包装）
        std::pair<const Key&, T&> operator*() {
            return std::pair<const Key&, T&>(NodePtr->First, NodePtr->Second);
        }

        // const 版本
        std::pair<const Key&, const T&> operator*() const {
            return std::pair<const Key&, const T&>(NodePtr->First, NodePtr->Second);
        }

        Iterator& operator++() {
            AdvanceToNextNode();
            return *this;
        }

        Iterator operator++(int) {
            Iterator Tmp = *this;
            AdvanceToNextNode();
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
        const std::vector<Node*>* BucketPtr;
        size_t CurrentBucket;
        size_t TotalBuckets;

        void AdvanceToNextNode() {
            if (NodePtr && NodePtr->Next) {
                NodePtr = NodePtr->Next;
                return;
            }

            for (size_t i = CurrentBucket + 1; i < TotalBuckets; ++i) {
                if ((*BucketPtr)[i]) {
                    CurrentBucket = i;
                    NodePtr = (*BucketPtr)[i];
                    return;
                }
            }

            NodePtr = nullptr;
            CurrentBucket = TotalBuckets;
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const Key, T>;
        using difference_type = ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        ConstIterator() : NodePtr(nullptr), BucketPtr(nullptr),
                          CurrentBucket(0), TotalBuckets(0) {}

        ConstIterator(const Node* NodePtr, const std::vector<Node*>* BucketPtr,
                      size_t CurrentBucket, size_t TotalBuckets)
            : NodePtr(NodePtr), BucketPtr(BucketPtr),
              CurrentBucket(CurrentBucket), TotalBuckets(TotalBuckets) {}

        ConstIterator(const Iterator& It)
            : NodePtr(It.NodePtr), BucketPtr(It.BucketPtr),
              CurrentBucket(It.CurrentBucket), TotalBuckets(It.TotalBuckets) {}

        std::pair<const Key&, const T&> operator*() const {
            return std::pair<const Key&, const T&>(NodePtr->First, NodePtr->Second);
        }

        ConstIterator& operator++() {
            AdvanceToNextNode();
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator Tmp = *this;
            AdvanceToNextNode();
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
    GMultiHash() : Size_(0), BucketCount(DEFAULT_BUCKET_COUNT) {
        Buckets.resize(DEFAULT_BUCKET_COUNT);
        for (size_t i = 0; i < Buckets.size(); ++i) {
            Buckets[i] = nullptr;
        }
    }

    explicit GMultiHash(size_t InitialBucketCount)
        : Size_(0), BucketCount(InitialBucketCount) {
        Buckets.resize(InitialBucketCount);
        for (size_t i = 0; i < Buckets.size(); ++i) {
            Buckets[i] = nullptr;
        }
    }

    GMultiHash(std::initializer_list<std::pair<Key, T>> Init) : GMultiHash() {
        for (const auto& Item : Init) {
            Insert(Item.first, Item.second);
        }
    }

    GMultiHash(const GMultiHash& Other) : GMultiHash() {
        for (const auto& Item : Other) {
            Insert(Item.first, Item.second);
        }
    }

    GMultiHash(GMultiHash&& Other) noexcept
        : Buckets(std::move(Other.Buckets)),
          Size_(Other.Size_),
          BucketCount(Other.BucketCount) {
        Other.Size_ = 0;
        Other.BucketCount = 0;
    }

    ~GMultiHash() {
        Clear();
    }

    // ========== 赋值操作 ==========
    GMultiHash& operator=(const GMultiHash& Other) {
        if (this != &Other) {
            GMultiHash Tmp(Other);
            Swap(Tmp);
        }
        return *this;
    }

    GMultiHash& operator=(GMultiHash&& Other) noexcept {
        if (this != &Other) {
            Clear();
            Buckets = std::move(Other.Buckets);
            Size_ = Other.Size_;
            BucketCount = Other.BucketCount;
            Other.Size_ = 0;
            Other.BucketCount = 0;
        }
        return *this;
    }

    GMultiHash& operator=(std::initializer_list<std::pair<Key, T>> Init) {
        Clear();
        for (const auto& Item : Init) {
            Insert(Item.first, Item.second);
        }
        return *this;
    }

    // ========== 容量相关 ==========
    size_t GetSize() const { return Size_; }
    bool IsEmpty() const { return Size_ == 0; }
    size_t GetBucketCount() const { return BucketCount; }

    // ========== 插入操作 ==========
    void Insert(const Key& K, const T& V) {
        size_t Index = GetBucketIndex(K);
        Node* NewNode = new Node(K, V);
        NewNode->Next = Buckets[Index];
        Buckets[Index] = NewNode;
        ++Size_;
        CheckRehash();
    }

    void Insert(const Key& K, T&& V) {
        size_t Index = GetBucketIndex(K);
        Node* NewNode = new Node(K, std::move(V));
        NewNode->Next = Buckets[Index];
        Buckets[Index] = NewNode;
        ++Size_;
        CheckRehash();
    }

    void Insert(Key&& K, const T& V) {
        size_t Index = GetBucketIndex(K);
        Node* NewNode = new Node(std::move(K), V);
        NewNode->Next = Buckets[Index];
        Buckets[Index] = NewNode;
        ++Size_;
        CheckRehash();
    }

    void Insert(Key&& K, T&& V) {
        size_t Index = GetBucketIndex(K);
        Node* NewNode = new Node(std::move(K), std::move(V));
        NewNode->Next = Buckets[Index];
        Buckets[Index] = NewNode;
        ++Size_;
        CheckRehash();
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
        size_t Index = GetBucketIndex(K);
        Node* Current = Buckets[Index];
        while (Current) {
            if (Current->First == K) {
                Result.push_back(Current->Second);
            }
            Current = Current->Next;
        }
        return Result;
    }

    T Value(const Key& K, const T& DefaultValue = T()) const {
        size_t Index = GetBucketIndex(K);
        Node* Current = Buckets[Index];
        while (Current) {
            if (Current->First == K) {
                return Current->Second;
            }
            Current = Current->Next;
        }
        return DefaultValue;
    }

    size_t Count(const Key& K) const {
        size_t Count = 0;
        size_t Index = GetBucketIndex(K);
        Node* Current = Buckets[Index];
        while (Current) {
            if (Current->First == K) {
                ++Count;
            }
            Current = Current->Next;
        }
        return Count;
    }

    bool Contains(const Key& K) const {
        size_t Index = GetBucketIndex(K);
        return FindNode(Index, K) != nullptr;
    }

    bool Contains(const Key& K, const T& V) const {
        size_t Index = GetBucketIndex(K);
        Node* Current = Buckets[Index];
        while (Current) {
            if (Current->First == K && Current->Second == V) {
                return true;
            }
            Current = Current->Next;
        }
        return false;
    }

    // ========== 移除操作 ==========
    size_t Remove(const Key& K) {
        size_t RemovedCount = 0;
        size_t Index = GetBucketIndex(K);

        Node* Current = Buckets[Index];
        Node* Prev = nullptr;

        while (Current) {
            if (Current->First == K) {
                Node* ToRemove = Current;
                if (Prev) {
                    Prev->Next = Current->Next;
                } else {
                    Buckets[Index] = Current->Next;
                }
                Current = Current->Next;
                delete ToRemove;
                --Size_;
                ++RemovedCount;
            } else {
                Prev = Current;
                Current = Current->Next;
            }
        }

        return RemovedCount;
    }

    bool Remove(const Key& K, const T& V) {
        size_t Index = GetBucketIndex(K);

        Node* Current = Buckets[Index];
        Node* Prev = nullptr;

        while (Current) {
            if (Current->First == K && Current->Second == V) {
                if (Prev) {
                    Prev->Next = Current->Next;
                } else {
                    Buckets[Index] = Current->Next;
                }
                delete Current;
                --Size_;
                return true;
            }
            Prev = Current;
            Current = Current->Next;
        }

        return false;
    }

    void Clear() {
        for (size_t i = 0; i < Buckets.size(); ++i) {
            Node* Current = Buckets[i];
            while (Current) {
                Node* Next = Current->Next;
                delete Current;
                Current = Next;
            }
            Buckets[i] = nullptr;
        }
        Size_ = 0;
    }

    // ========== 其他操作 ==========
    void Reserve(size_t NewBucketCount) {
        if (NewBucketCount > Buckets.size()) {
            Rehash(NewBucketCount);
        }
    }

    void Swap(GMultiHash& Other) noexcept {
        std::swap(Buckets, Other.Buckets);
        std::swap(Size_, Other.Size_);
        std::swap(BucketCount, Other.BucketCount);
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
        for (size_t i = 0; i < Buckets.size(); ++i) {
            if (Buckets[i]) {
                return Iterator(Buckets[i], &Buckets, i, Buckets.size());
            }
        }
        return End();
    }

    Iterator End() {
        return Iterator(nullptr, &Buckets, Buckets.size(), Buckets.size());
    }

    ConstIterator Begin() const {
        for (size_t i = 0; i < Buckets.size(); ++i) {
            if (Buckets[i]) {
                return ConstIterator(Buckets[i], &Buckets, i, Buckets.size());
            }
        }
        return End();
    }

    ConstIterator End() const {
        return ConstIterator(nullptr, &Buckets, Buckets.size(), Buckets.size());
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
};