// GVector.h
#pragma once

#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <iterator>

template<typename T>
class GVector {
private:
    T* Data_;
    size_t Size_;
    size_t Capacity_;

    static constexpr size_t DEFAULT_CAPACITY = 4;

public:
    // ========== 迭代器 ==========
    class Iterator {
    private:
        T* Ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T* Ptr = nullptr) : Ptr(Ptr) {}

        reference operator*() const { return *Ptr; }
        pointer operator->() const { return Ptr; }

        Iterator& operator++() { ++Ptr; return *this; }
        Iterator operator++(int) { Iterator Tmp = *this; ++(*this); return Tmp; }
        Iterator& operator--() { --Ptr; return *this; }
        Iterator operator--(int) { Iterator Tmp = *this; --(*this); return Tmp; }

        Iterator& operator+=(difference_type N) { Ptr += N; return *this; }
        Iterator& operator-=(difference_type N) { Ptr -= N; return *this; }

        Iterator operator+(difference_type N) const { return Iterator(Ptr + N); }
        Iterator operator-(difference_type N) const { return Iterator(Ptr - N); }
        difference_type operator-(const Iterator& Other) const { return Ptr - Other.Ptr; }

        T& operator[](difference_type N) const { return Ptr[N]; }

        bool operator==(const Iterator& Other) const { return Ptr == Other.Ptr; }
        bool operator!=(const Iterator& Other) const { return Ptr != Other.Ptr; }
        bool operator<(const Iterator& Other) const { return Ptr < Other.Ptr; }
        bool operator>(const Iterator& Other) const { return Ptr > Other.Ptr; }
        bool operator<=(const Iterator& Other) const { return Ptr <= Other.Ptr; }
        bool operator>=(const Iterator& Other) const { return Ptr >= Other.Ptr; }
    };

    class ConstIterator {
    private:
        const T* Ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator(const T* Ptr = nullptr) : Ptr(Ptr) {}
        ConstIterator(const Iterator& It) : Ptr(It.Ptr) {}

        reference operator*() const { return *Ptr; }
        pointer operator->() const { return Ptr; }

        ConstIterator& operator++() { ++Ptr; return *this; }
        ConstIterator operator++(int) { ConstIterator Tmp = *this; ++(*this); return Tmp; }
        ConstIterator& operator--() { --Ptr; return *this; }
        ConstIterator operator--(int) { ConstIterator Tmp = *this; --(*this); return Tmp; }

        ConstIterator& operator+=(difference_type N) { Ptr += N; return *this; }
        ConstIterator& operator-=(difference_type N) { Ptr -= N; return *this; }

        ConstIterator operator+(difference_type N) const { return ConstIterator(Ptr + N); }
        ConstIterator operator-(difference_type N) const { return ConstIterator(Ptr - N); }
        difference_type operator-(const ConstIterator& Other) const { return Ptr - Other.Ptr; }

        const T& operator[](difference_type N) const { return Ptr[N]; }

        bool operator==(const ConstIterator& Other) const { return Ptr == Other.Ptr; }
        bool operator!=(const ConstIterator& Other) const { return Ptr != Other.Ptr; }
        bool operator<(const ConstIterator& Other) const { return Ptr < Other.Ptr; }
        bool operator>(const ConstIterator& Other) const { return Ptr > Other.Ptr; }
        bool operator<=(const ConstIterator& Other) const { return Ptr <= Other.Ptr; }
        bool operator>=(const ConstIterator& Other) const { return Ptr >= Other.Ptr; }
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using reverse_iterator = std::reverse_iterator<Iterator>;
    using const_reverse_iterator = std::reverse_iterator<ConstIterator>;

    // ========== 构造与析构 ==========
    GVector() : Data_(nullptr), Size_(0), Capacity_(0) {}

    explicit GVector(size_t Count) : GVector() {
        Reserve(Count);
        for (size_t i = 0; i < Count; ++i) {
            Append(T());
        }
    }

    GVector(size_t Count, const T& Value) : GVector() {
        Reserve(Count);
        for (size_t i = 0; i < Count; ++i) {
            Append(Value);
        }
    }

    GVector(std::initializer_list<T> Init) : GVector() {
        Reserve(Init.size());
        for (const auto& Value : Init) {
            Append(Value);
        }
    }

    GVector(const GVector& Other) : GVector() {
        Reserve(Other.Size_);
        for (const auto& Value : Other) {
            Append(Value);
        }
    }

    GVector(GVector&& Other) noexcept
        : Data_(Other.Data_), Size_(Other.Size_), Capacity_(Other.Capacity_) {
        Other.Data_ = nullptr;
        Other.Size_ = 0;
        Other.Capacity_ = 0;
    }

    ~GVector() {
        Clear();
    }

    // ========== 赋值操作 ==========
    GVector& operator=(const GVector& Other) {
        if (this != &Other) {
            GVector Tmp(Other);
            Swap(Tmp);
        }
        return *this;
    }

    GVector& operator=(GVector&& Other) noexcept {
        if (this != &Other) {
            Clear();
            Data_ = Other.Data_;
            Size_ = Other.Size_;
            Capacity_ = Other.Capacity_;
            Other.Data_ = nullptr;
            Other.Size_ = 0;
            Other.Capacity_ = 0;
        }
        return *this;
    }

    GVector& operator=(std::initializer_list<T> Init) {
        Clear();
        Reserve(Init.size());
        for (const auto& Value : Init) {
            Append(Value);
        }
        return *this;
    }

    // ========== 容量相关 ==========
    size_t GetSize() const { return Size_; }
    size_t GetCapacity() const { return Capacity_; }
    bool IsEmpty() const { return Size_ == 0; }

    // ========== 内存管理 ==========
    void Reserve(size_t NewCapacity) {
        if (NewCapacity <= Capacity_) return;

        T* NewData = static_cast<T*>(operator new(NewCapacity * sizeof(T)));

        for (size_t i = 0; i < Size_; ++i) {
            new (&NewData[i]) T(std::move(Data_[i]));
            Data_[i].~T();
        }

        operator delete(Data_);
        Data_ = NewData;
        Capacity_ = NewCapacity;
    }

    void Resize(size_t NewSize) {
        if (NewSize < Size_) {
            for (size_t i = NewSize; i < Size_; ++i) {
                Data_[i].~T();
            }
            Size_ = NewSize;
        } else if (NewSize > Size_) {
            if (NewSize > Capacity_) {
                Reserve(std::max(NewSize, Capacity_ * 2));
            }
            for (size_t i = Size_; i < NewSize; ++i) {
                new (&Data_[i]) T();
            }
            Size_ = NewSize;
        }
    }

    void Resize(size_t NewSize, const T& Value) {
        if (NewSize < Size_) {
            for (size_t i = NewSize; i < Size_; ++i) {
                Data_[i].~T();
            }
            Size_ = NewSize;
        } else if (NewSize > Size_) {
            if (NewSize > Capacity_) {
                Reserve(std::max(NewSize, Capacity_ * 2));
            }
            for (size_t i = Size_; i < NewSize; ++i) {
                new (&Data_[i]) T(Value);
            }
            Size_ = NewSize;
        }
    }

    void ShrinkToFit() {
        if (Size_ == 0) {
            Clear();
            return;
        }

        T* NewData = static_cast<T*>(operator new(Size_ * sizeof(T)));

        for (size_t i = 0; i < Size_; ++i) {
            new (&NewData[i]) T(std::move(Data_[i]));
            Data_[i].~T();
        }

        operator delete(Data_);
        Data_ = NewData;
        Capacity_ = Size_;
    }

    // ========== 访问元素 ==========
    T& First() {
        if (IsEmpty()) throw std::out_of_range("GVector::First(): vector is empty");
        return Data_[0];
    }
    const T& First() const {
        if (IsEmpty()) throw std::out_of_range("GVector::First(): vector is empty");
        return Data_[0];
    }

    T& Last() {
        if (IsEmpty()) throw std::out_of_range("GVector::Last(): vector is empty");
        return Data_[Size_ - 1];
    }
    const T& Last() const {
        if (IsEmpty()) throw std::out_of_range("GVector::Last(): vector is empty");
        return Data_[Size_ - 1];
    }

    T& At(size_t Index) {
        if (Index >= Size_) throw std::out_of_range("GVector::At(): index out of range");
        return Data_[Index];
    }
    const T& At(size_t Index) const {
        if (Index >= Size_) throw std::out_of_range("GVector::At(): index out of range");
        return Data_[Index];
    }

    T& operator[](size_t Index) { return Data_[Index]; }
    const T& operator[](size_t Index) const { return Data_[Index]; }

    // ========== 添加元素 ==========
    void Append(const T& Value) {
        if (Size_ == Capacity_) {
            Reserve(Capacity_ == 0 ? DEFAULT_CAPACITY : Capacity_ * 2);
        }
        new (&Data_[Size_]) T(Value);
        ++Size_;
    }

    void Append(T&& Value) {
        if (Size_ == Capacity_) {
            Reserve(Capacity_ == 0 ? DEFAULT_CAPACITY : Capacity_ * 2);
        }
        new (&Data_[Size_]) T(std::move(Value));
        ++Size_;
    }

    void Append(const GVector& Other) {
        Reserve(Size_ + Other.Size_);
        for (const auto& Value : Other) {
            Append(Value);
        }
    }

    void Prepend(const T& Value) {
        Insert(0, Value);
    }

    void Prepend(T&& Value) {
        Insert(0, std::move(Value));
    }

    void Insert(size_t Index, const T& Value) {
        if (Index > Size_) throw std::out_of_range("GVector::Insert(): index out of range");

        if (Size_ == Capacity_) {
            Reserve(Capacity_ == 0 ? DEFAULT_CAPACITY : Capacity_ * 2);
        }

        for (size_t i = Size_; i > Index; --i) {
            new (&Data_[i]) T(std::move(Data_[i - 1]));
            Data_[i - 1].~T();
        }

        new (&Data_[Index]) T(Value);
        ++Size_;
    }

    void Insert(size_t Index, T&& Value) {
        if (Index > Size_) throw std::out_of_range("GVector::Insert(): index out of range");

        if (Size_ == Capacity_) {
            Reserve(Capacity_ == 0 ? DEFAULT_CAPACITY : Capacity_ * 2);
        }

        for (size_t i = Size_; i > Index; --i) {
            new (&Data_[i]) T(std::move(Data_[i - 1]));
            Data_[i - 1].~T();
        }

        new (&Data_[Index]) T(std::move(Value));
        ++Size_;
    }

    void Insert(size_t Index, size_t Count, const T& Value) {
        if (Index > Size_) throw std::out_of_range("GVector::Insert(): index out of range");

        if (Size_ + Count > Capacity_) {
            Reserve(std::max(Size_ + Count, Capacity_ * 2));
        }

        for (size_t i = Size_ + Count - 1; i >= Index + Count; --i) {
            new (&Data_[i]) T(std::move(Data_[i - Count]));
            Data_[i - Count].~T();
        }

        for (size_t i = 0; i < Count; ++i) {
            new (&Data_[Index + i]) T(Value);
        }
        Size_ += Count;
    }

    // ========== 移除元素 ==========
    void RemoveAt(size_t Index) {
        if (Index >= Size_) throw std::out_of_range("GVector::RemoveAt(): index out of range");

        Data_[Index].~T();
        for (size_t i = Index + 1; i < Size_; ++i) {
            new (&Data_[i - 1]) T(std::move(Data_[i]));
            Data_[i].~T();
        }
        --Size_;
    }

    void RemoveAt(size_t Index, size_t Count) {
        if (Index + Count > Size_) throw std::out_of_range("GVector::RemoveAt(): index out of range");

        for (size_t i = Index; i < Index + Count; ++i) {
            Data_[i].~T();
        }

        for (size_t i = Index + Count; i < Size_; ++i) {
            new (&Data_[i - Count]) T(std::move(Data_[i]));
            Data_[i].~T();
        }
        Size_ -= Count;
    }

    bool Remove(const T& Value) {
        for (size_t i = 0; i < Size_; ++i) {
            if (Data_[i] == Value) {
                RemoveAt(i);
                return true;
            }
        }
        return false;
    }

    size_t RemoveAll(const T& Value) {
        size_t Count = 0;
        for (size_t i = 0; i < Size_; ) {
            if (Data_[i] == Value) {
                RemoveAt(i);
                ++Count;
            } else {
                ++i;
            }
        }
        return Count;
    }

    void Clear() {
        for (size_t i = 0; i < Size_; ++i) {
            Data_[i].~T();
        }
        operator delete(Data_);
        Data_ = nullptr;
        Size_ = 0;
        Capacity_ = 0;
    }

    // ========== 查找 ==========
    Iterator Find(const T& Value) {
        for (size_t i = 0; i < Size_; ++i) {
            if (Data_[i] == Value) {
                return Iterator(&Data_[i]);
            }
        }
        return End();
    }

    ConstIterator Find(const T& Value) const {
        for (size_t i = 0; i < Size_; ++i) {
            if (Data_[i] == Value) {
                return ConstIterator(&Data_[i]);
            }
        }
        return End();
    }

    size_t IndexOf(const T& Value, size_t From = 0) const {
        if (From >= Size_) return static_cast<size_t>(-1);

        for (size_t i = From; i < Size_; ++i) {
            if (Data_[i] == Value) {
                return i;
            }
        }
        return static_cast<size_t>(-1);
    }

    bool Contains(const T& Value) const {
        return Find(Value) != End();
    }

    // ========== 其他操作 ==========
    void Reverse() {
        for (size_t i = 0; i < Size_ / 2; ++i) {
            std::swap(Data_[i], Data_[Size_ - 1 - i]);
        }
    }

    void Swap(GVector& Other) noexcept {
        std::swap(Data_, Other.Data_);
        std::swap(Size_, Other.Size_);
        std::swap(Capacity_, Other.Capacity_);
    }

    // ========== 迭代器支持 ==========
    Iterator Begin() { return Iterator(Data_); }
    Iterator End() { return Iterator(Data_ + Size_); }
    ConstIterator Begin() const { return ConstIterator(Data_); }
    ConstIterator End() const { return ConstIterator(Data_ + Size_); }
    ConstIterator CBegin() const { return ConstIterator(Data_); }
    ConstIterator CEnd() const { return ConstIterator(Data_ + Size_); }

    Iterator begin() { return Iterator(Data_); }
    Iterator end() { return Iterator(Data_ + Size_); }
    ConstIterator begin() const { return ConstIterator(Data_); }
    ConstIterator end() const { return ConstIterator(Data_ + Size_); }
    ConstIterator cbegin() const { return ConstIterator(Data_); }
    ConstIterator cend() const { return ConstIterator(Data_ + Size_); }

    // 反向迭代器
    reverse_iterator RBegin() { return reverse_iterator(End()); }
    reverse_iterator REnd() { return reverse_iterator(Begin()); }
    const_reverse_iterator RBegin() const { return const_reverse_iterator(End()); }
    const_reverse_iterator REnd() const { return const_reverse_iterator(Begin()); }
};