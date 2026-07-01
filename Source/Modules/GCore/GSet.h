// GSet.h
#pragma once

#include <vector>
#include <utility>
#include <stdexcept>
#include <iterator>
#include <functional>

template<typename T>
class GSet {
private:
    struct Node {
        T Data;
        Node* Next;
        
        Node(const T& Value) : Data(Value), Next(nullptr) {}
        Node(T&& Value) : Data(std::move(Value)), Next(nullptr) {}
    };
    
    std::vector<Node*> Buckets;
    size_t Size_;
    size_t BucketCount;
    
    static constexpr size_t DEFAULT_BUCKET_COUNT = 16;
    static constexpr float LOAD_FACTOR = 0.75f;
    
    size_t Hash(const T& Value) const {
        return std::hash<T>{}(Value);
    }
    
    size_t GetBucketIndex(const T& Value) const {
        return Hash(Value) % Buckets.size();
    }
    
    Node* FindNode(size_t Index, const T& Value) {
        Node* Current = Buckets[Index];
        while (Current) {
            if (Current->Data == Value) {
                return Current;
            }
            Current = Current->Next;
        }
        return nullptr;
    }
    
    const Node* FindNode(size_t Index, const T& Value) const {
        Node* Current = Buckets[Index];
        while (Current) {
            if (Current->Data == Value) {
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
                size_t NewIndex = GetBucketIndex(NodePtr->Data);
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
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        Iterator() : NodePtr(nullptr), BucketPtr(nullptr), 
                     CurrentBucket(0), TotalBuckets(0) {}
        
        Iterator(Node* NodePtr, std::vector<Node*>* BucketPtr,
                 size_t CurrentBucket, size_t TotalBuckets)
            : NodePtr(NodePtr), BucketPtr(BucketPtr),
              CurrentBucket(CurrentBucket), TotalBuckets(TotalBuckets) {}
        
        T& operator*() { return NodePtr->Data; }
        const T& operator*() const { return NodePtr->Data; }
        T* operator->() { return &NodePtr->Data; }
        const T* operator->() const { return &NodePtr->Data; }
        
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
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        ConstIterator() : NodePtr(nullptr), BucketPtr(nullptr),
                          CurrentBucket(0), TotalBuckets(0) {}
        
        ConstIterator(const Node* NodePtr, const std::vector<Node*>* BucketPtr,
                      size_t CurrentBucket, size_t TotalBuckets)
            : NodePtr(NodePtr), BucketPtr(BucketPtr),
              CurrentBucket(CurrentBucket), TotalBuckets(TotalBuckets) {}
        
        ConstIterator(const Iterator& It)
            : NodePtr(It.NodePtr), BucketPtr(It.BucketPtr),
              CurrentBucket(It.CurrentBucket), TotalBuckets(It.TotalBuckets) {}
        
        const T& operator*() const { return NodePtr->Data; }
        const T* operator->() const { return &NodePtr->Data; }
        
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
    GSet() : Size_(0), BucketCount(DEFAULT_BUCKET_COUNT) {
        Buckets.resize(DEFAULT_BUCKET_COUNT);
        for (size_t i = 0; i < Buckets.size(); ++i) {
            Buckets[i] = nullptr;
        }
    }
    
    explicit GSet(size_t InitialBucketCount)
        : Size_(0), BucketCount(InitialBucketCount) {
        Buckets.resize(InitialBucketCount);
        for (size_t i = 0; i < Buckets.size(); ++i) {
            Buckets[i] = nullptr;
        }
    }
    
    GSet(std::initializer_list<T> Init) : GSet() {
        for (const auto& Value : Init) {
            Insert(Value);
        }
    }
    
    GSet(const GSet& Other) : GSet() {
        for (const auto& Value : Other) {
            Insert(Value);
        }
    }
    
    GSet(GSet&& Other) noexcept
        : Buckets(std::move(Other.Buckets)),
          Size_(Other.Size_),
          BucketCount(Other.BucketCount) {
        Other.Size_ = 0;
        Other.BucketCount = 0;
    }
    
    ~GSet() {
        Clear();
    }
    
    // ========== 赋值操作 ==========
    GSet& operator=(const GSet& Other) {
        if (this != &Other) {
            GSet Tmp(Other);
            Swap(Tmp);
        }
        return *this;
    }
    
    GSet& operator=(GSet&& Other) noexcept {
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
    
    GSet& operator=(std::initializer_list<T> Init) {
        Clear();
        for (const auto& Value : Init) {
            Insert(Value);
        }
        return *this;
    }
    
    // ========== 容量相关 ==========
    size_t GetSize() const { return Size_; }
    bool IsEmpty() const { return Size_ == 0; }
    size_t GetBucketCount() const { return BucketCount; }
    
    // ========== 插入操作 ==========
    bool Insert(const T& Value) {
        size_t Index = GetBucketIndex(Value);
        if (FindNode(Index, Value)) {
            return false;  // 已存在
        }
        
        Node* NewNode = new Node(Value);
        NewNode->Next = Buckets[Index];
        Buckets[Index] = NewNode;
        ++Size_;
        CheckRehash();
        return true;
    }
    
    bool Insert(T&& Value) {
        size_t Index = GetBucketIndex(Value);
        if (FindNode(Index, Value)) {
            return false;  // 已存在
        }
        
        Node* NewNode = new Node(std::move(Value));
        NewNode->Next = Buckets[Index];
        Buckets[Index] = NewNode;
        ++Size_;
        CheckRehash();
        return true;
    }
    
    // ========== 查找操作 ==========
    bool Contains(const T& Value) const {
        size_t Index = GetBucketIndex(Value);
        return FindNode(Index, Value) != nullptr;
    }
    
    Iterator Find(const T& Value) {
        size_t Index = GetBucketIndex(Value);
        Node* Found = FindNode(Index, Value);
        if (Found) {
            // 需要找到该节点在迭代器中的位置
            for (size_t i = 0; i <= Index; ++i) {
                if (Buckets[i]) {
                    Node* Current = Buckets[i];
                    while (Current) {
                        if (Current == Found) {
                            return Iterator(Current, &Buckets, i, Buckets.size());
                        }
                        Current = Current->Next;
                    }
                }
            }
        }
        return End();
    }
    
    ConstIterator Find(const T& Value) const {
        size_t Index = GetBucketIndex(Value);
        Node* Found = FindNode(Index, Value);
        if (Found) {
            for (size_t i = 0; i <= Index; ++i) {
                if (Buckets[i]) {
                    Node* Current = Buckets[i];
                    while (Current) {
                        if (Current == Found) {
                            return ConstIterator(Current, &Buckets, i, Buckets.size());
                        }
                        Current = Current->Next;
                    }
                }
            }
        }
        return End();
    }
    
    // ========== 移除操作 ==========
    bool Remove(const T& Value) {
        size_t Index = GetBucketIndex(Value);
        
        Node* Current = Buckets[Index];
        Node* Prev = nullptr;
        
        while (Current) {
            if (Current->Data == Value) {
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
    
    // ========== 集合操作 ==========
    // 并集
    GSet Union(const GSet& Other) const {
        GSet Result(*this);
        for (const auto& Value : Other) {
            Result.Insert(Value);
        }
        return Result;
    }
    
    // 交集
    GSet Intersection(const GSet& Other) const {
        GSet Result;
        for (const auto& Value : *this) {
            if (Other.Contains(Value)) {
                Result.Insert(Value);
            }
        }
        return Result;
    }
    
    // 差集
    GSet Difference(const GSet& Other) const {
        GSet Result;
        for (const auto& Value : *this) {
            if (!Other.Contains(Value)) {
                Result.Insert(Value);
            }
        }
        return Result;
    }
    
    // 对称差集
    GSet SymmetricDifference(const GSet& Other) const {
        GSet Result;
        for (const auto& Value : *this) {
            if (!Other.Contains(Value)) {
                Result.Insert(Value);
            }
        }
        for (const auto& Value : Other) {
            if (!Contains(Value)) {
                Result.Insert(Value);
            }
        }
        return Result;
    }
    
    // 判断是否为子集
    bool IsSubsetOf(const GSet& Other) const {
        for (const auto& Value : *this) {
            if (!Other.Contains(Value)) {
                return false;
            }
        }
        return true;
    }
    
    // 判断是否为真子集
    bool IsProperSubsetOf(const GSet& Other) const {
        return GetSize() < Other.GetSize() && IsSubsetOf(Other);
    }
    
    // 判断是否相等
    bool IsEqual(const GSet& Other) const {
        if (GetSize() != Other.GetSize()) return false;
        for (const auto& Value : *this) {
            if (!Other.Contains(Value)) {
                return false;
            }
        }
        return true;
    }
    
    // ========== 其他操作 ==========
    void Reserve(size_t NewBucketCount) {
        if (NewBucketCount > Buckets.size()) {
            Rehash(NewBucketCount);
        }
    }
    
    void Swap(GSet& Other) noexcept {
        std::swap(Buckets, Other.Buckets);
        std::swap(Size_, Other.Size_);
        std::swap(BucketCount, Other.BucketCount);
    }
    
    std::vector<T> ToList() const {
        std::vector<T> Result;
        for (const auto& Value : *this) {
            Result.push_back(Value);
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