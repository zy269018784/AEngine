#pragma once
#include <cmath>
#include <algorithm>
#include "BasicTypes.h"

namespace GMath {
    /**
     * @brief 2D tuple base class for vectors/points
     *
     * @tparam Child CRTP-derived child class (e.g., Vector2, Point2)
     * @tparam T Component type
     */
    template <template <typename> class Child, typename T>
    class GTuple2 {
    public:
        GTuple2() = default;

        /**
         * @brief Construct from x, y components
         * @param x X coordinate
         * @param y Y coordinate
         */
        GTuple2(T x, T y) : x(x), y(y) { }

        /**
         * @brief Check if any component is NaN
         * @return true if x or y is NaN
         */
        bool HasNaN() const { return IsNaN(x) || IsNaN(y); }

        /**
         * @brief Add another tuple component-wise
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return New tuple with summed components
         */
        template <typename U>
        auto operator+(Child<U> c) const -> Child<decltype(T{} + U{})> {
            return { x + c.x, y + c.y };
        }

        /**
         * @brief Add scalar to all components
         * @tparam U Scalar type
         * @param c Scalar to add
         * @return New tuple with added scalar
         */
        template <typename U>
        auto operator+(U c) const -> Child<decltype(T{} + U{})> {
            return { x + c, y + c };
        }

        /**
         * @brief Add another tuple and assign
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator+=(Child<U> c) {
            x += c.x; y += c.y;
            return static_cast<Child<T>&>(*this);
        }

        /**
         * @brief Add scalar to all components and assign
         * @tparam U Scalar type
         * @param c Scalar to add
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator+=(U c) {
            x += c; y += c;
            return static_cast<Child<T>&>(*this);
        }

        /**
         * @brief Subtract another tuple component-wise
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return New tuple with subtracted components
         */
        template <typename U>
        auto operator-(Child<U> c) const -> Child<decltype(T{} - U{})> {
            return { x - c.x, y - c.y };
        }

        /**
         * @brief Subtract scalar from all components
         * @tparam U Scalar type
         * @param c Scalar to subtract
         * @return New tuple with subtracted scalar
         */
        template <typename U>
        auto operator-(U c) const -> Child<decltype(T{} - U{})> {
            return { x - c, y - c };
        }

        /**
         * @brief Subtract another tuple and assign
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator-=(Child<U> c) {
            x -= c.x; y -= c.y;
            return static_cast<Child<T>&>(*this);
        }

        /**
         * @brief Subtract scalar from all components and assign
         * @tparam U Scalar type
         * @param c Scalar to subtract
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator-=(U c) {
            x -= c; y -= c;
            return static_cast<Child<T>&>(*this);
        }

        /**
         * @brief Multiply component-wise by another tuple
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return New tuple with multiplied components
         */
        template <typename U>
        auto operator*(Child<U> c) const -> Child<decltype(T{} * U{})> {
            return { x * c.x, y * c.y };
        }

        /**
         * @brief Multiply all components by scalar
         * @tparam U Scalar type
         * @param c Scalar multiplier
         * @return New tuple with scaled components
         */
        template <typename U>
        auto operator*(U c) const -> Child<decltype(T{} * U{})> {
            return { x * c, y * c };
        }

        /**
         * @brief Multiply component-wise by another tuple and assign
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator*=(Child<U> c) {
            x *= c.x; y *= c.y;
            return static_cast<Child<T>&>(*this);
        }

        /**
         * @brief Multiply all components by scalar and assign
         * @tparam U Scalar type
         * @param c Scalar multiplier
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator*=(U c) {
            x *= c; y *= c;
            return static_cast<Child<T>&>(*this);
        }

        /**
         * @brief Divide component-wise by another tuple
         * @tparam U Component type of RHS
         * @param c RHS tuple (divisor)
         * @return New tuple with divided components
         */
        template <typename U>
        auto operator/(Child<U> c) const -> Child<decltype(T{} / U{})> {
            return { x / c.x, y / c.y };
        }

        /**
         * @brief Divide all components by scalar
         * @tparam U Scalar type
         * @param c Scalar divisor
         * @return New tuple with divided components
         */
        template <typename U>
        auto operator/(U c) const -> Child<decltype(T{} / U{})> {
            return { x / c, y / c };
        }

        /**
         * @brief Divide component-wise by another tuple and assign
         * @tparam U Component type of RHS
         * @param c RHS tuple (divisor)
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator/=(Child<U> c) {
            x /= c.x; y /= c.y;
            return static_cast<Child<T>&>(*this);
        }

        /**
         * @brief Divide all components by scalar and assign
         * @tparam U Scalar type
         * @param c Scalar divisor
         * @return Reference to this tuple
         * @warning BUG: Current implementation assigns instead of divides
         */
        template <typename U>
        Child<T>& operator/=(U c) {
            x = c; y = c;  // FIXME: should be x/=c, y/=c
            return static_cast<Child<T>&>(*this);
        }

        /**
         * @brief Equality comparison
         * @param c RHS tuple
         * @return true if all components equal
         */
        bool operator==(Child<T> c) const { return x == c.x && y == c.y; }

        /**
         * @brief Inequality comparison
         * @param c RHS tuple
         * @return true if any component differs
         */
        bool operator!=(Child<T> c) const { return x != c.x || y != c.y; }

        /**
         * @brief Unary negation
         * @return Tuple with all components negated
         */
        Child<T> operator-() const { return { -x, -y }; }

        /**
         * @brief Indexed access (read-only)
         * @param i Index: 0 for x, 1 for y
         * @return Component value
         */
        T operator[](int i) const { return (i == 0) ? x : y; }

        /**
         * @brief Indexed access (mutable)
         * @param i Index: 0 for x, 1 for y
         * @return Reference to component
         */
        T& operator[](int i) { return (i == 0) ? x : y; }

        T x{};  ///< X component
        T y{};  ///< Y component
    };

    /**
     * @brief Compute squared length of a 2D tuple
     * @param n Input tuple
     * @return Sum of squares of components: x^2 + y^2
     */
    template <template <class> class C, typename T>
    inline auto LengthSquared(GTuple2<C, T> n) {
        return Sqr(n.x) + Sqr(n.y);
    }

    /**
     * @brief Compute length (magnitude) of a 2D tuple
     * @param v Input tuple
     * @return Euclidean distance from origin: sqrt(x^2 + y^2)
     */
    template <template <class> class C, typename T>
    inline auto Length(GTuple2<C, T> v) {
        using std::sqrt;
        return sqrt(LengthSquared(v));
    }

    /**
     * @brief Normalize a 2D tuple to unit length
     * @param v Input tuple
     * @return Unit vector pointing in same direction
     */
    template <template <class> class C, typename T>
    inline auto Normalize(GTuple2<C, T> v) {
        return v / Length(v);
    }

    /**
     * @brief Fused multiply-add: a * b + c (component-wise)
     * @param a Scalar multiplier
     * @param b Tuple to multiply
     * @param c Tuple to add
     * @return a*b + c
     */
    template <template <class> class C, typename T>
    inline C<T> FMA(Float a, GTuple2<C, T> b, GTuple2<C, T> c) {
        return { FMA(a, b.x, c.x), FMA(a, b.y, c.y) };
    }

    /**
     * @brief Fused multiply-add: a * b + c (component-wise, with tuple as first arg)
     * @param a First tuple
     * @param b Scalar multiplier
     * @param c Tuple to add
     * @return a*b + c
     */
    template <template <class> class C, typename T>
    inline C<T> FMA(GTuple2<C, T> a, Float b, GTuple2<C, T> c) {
        return FMA(b, a, c);
    }

    /**
     * @brief Component-wise absolute value
     * @param t Input tuple
     * @return Tuple with absolute values of each component
     */
    template <template <class> class C, typename T>
    inline C<T> Abs(GTuple2<C, T> t) {
        using std::abs;
        return { abs(t.x), abs(t.y) };
    }

    /**
     * @brief Component-wise minimum of two tuples
     * @param t1 First tuple
     * @param t2 Second tuple
     * @return Tuple containing min(t1.x, t2.x) and min(t1.y, t2.y)
     */
    template <template <class> class C, typename T>
    inline C<T> Min(GTuple2<C, T> t1, GTuple2<C, T> t2) {
        using std::min;
        return { min(t1.x, t2.x), min(t1.y, t2.y) };
    }

    /**
     * @brief Component-wise maximum of two tuples
     * @param t1 First tuple
     * @param t2 Second tuple
     * @return Tuple containing max(t1.x, t2.x) and max(t1.y, t2.y)
     */
    template <template <class> class C, typename T>
    inline C<T> Max(GTuple2<C, T> t1, GTuple2<C, T> t2) {
        using std::max;
        return { max(t1.x, t2.x), max(t1.y, t2.y) };
    }

    /**
     * @brief Get the minimum component value
     * @param t Input tuple
     * @return Smaller of x and y
     */
    template <template <class> class C, typename T>
    inline T MinComponentValue(GTuple2<C, T> t) {
        using std::min;
        return min({ t.x, t.y });
    }

    /**
     * @brief Get index of the minimum component
     * @param t Input tuple
     * @return 0 if x <= y, 1 otherwise
     */
    template <template <class> class C, typename T>
    inline int MinComponentIndex(GTuple2<C, T> t) {
        return (t.x < t.y) ? 0 : 1;
    }

    /**
     * @brief Get the maximum component value
     * @param t Input tuple
     * @return Larger of x and y
     */
    template <template <class> class C, typename T>
    inline T MaxComponentValue(GTuple2<C, T> t) {
        using std::max;
        return max({ t.x, t.y });
    }

    /**
     * @brief Get index of the maximum component
     * @param t Input tuple
     * @return 1 if x < y, 0 otherwise
     */
    template <template <class> class C, typename T>
    inline int MaxComponentIndex(GTuple2<C, T> t) {
        return (t.x < t.y) ? 1 : 0;
    }
} // namespace GMath