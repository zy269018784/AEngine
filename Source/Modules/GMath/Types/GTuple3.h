#pragma once
#include <cmath>
#include <algorithm>
#include "BasicTypes.h"
#include <Float.h>
namespace GMath {

    /**
     * @brief 3D tuple base class for vectors/points/colors
     * 
     * @tparam Child CRTP-derived child class (e.g., Vector3, Point3, RGBColor)
     * @tparam T Component type (typically float or double)
     */
    template <template <typename> class Child, typename T>
    class GTuple3 {
    public:
        GTuple3() = default;

        /**
         * @brief Construct from x, y, z components
         * @param x X coordinate
         * @param y Y coordinate
         * @param z Z coordinate
         */
        GTuple3(T x, T y, T z) : x(x), y(y), z(z) { }

        /**
         * @brief Check if any component is NaN
         * @return true if x, y, or z is NaN
         */
        bool HasNaN() const { return IsNaN(x) || IsNaN(y) || IsNaN(z); }

        /**
         * @brief Add another tuple component-wise
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return New tuple with summed components
         */
        template <typename U>
        auto operator+(Child<U> c) const -> Child<decltype(T{} + U{})> {
            return { x + c.x, y + c.y, z + c.z };
        }

        /**
         * @brief Add scalar to all components
         * @tparam U Scalar type
         * @param c Scalar to add
         * @return New tuple with added scalar
         */
        template <typename U>
        auto operator+(U c) const -> Child<decltype(T{} + U{})> {
            return { x + c, y + c, z + c };
        }

        /**
         * @brief Add another tuple and assign
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator+=(Child<U> c) {
            x += c.x; y += c.y; z += c.z;
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
            x += c; y += c; z += c;
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
            return { x - c.x, y - c.y, z - c.z };
        }

        /**
         * @brief Subtract scalar from all components
         * @tparam U Scalar type
         * @param c Scalar to subtract
         * @return New tuple with subtracted scalar
         */
        template <typename U>
        auto operator-(U c) const -> Child<decltype(T{} - U{})> {
            return { x - c, y - c, z - c };
        }

        /**
         * @brief Subtract another tuple and assign
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator-=(Child<U> c) {
            x -= c.x; y -= c.y; z -= c.z;
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
            x -= c; y -= c; z -= c;
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
            return { x * c.x, y * c.y, z * c.z };
        }

        /**
         * @brief Multiply all components by scalar
         * @tparam U Scalar type
         * @param c Scalar multiplier
         * @return New tuple with scaled components
         */
        template <typename U>
        auto operator*(U c) const -> Child<decltype(T{} * U{})> {
            return { x * c, y * c, z * c };
        }

        /**
         * @brief Multiply component-wise by another tuple and assign
         * @tparam U Component type of RHS
         * @param c RHS tuple
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator*=(Child<U> c) {
            x *= c.x; y *= c.y; z *= c.z;
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
            x *= c; y *= c; z *= c;
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
            return { x / c.x, y / c.y, z / c.z };
        }

        /**
         * @brief Divide all components by scalar
         * @tparam U Scalar type
         * @param c Scalar divisor
         * @return New tuple with divided components
         */
        template <typename U>
        auto operator/(U c) const -> Child<decltype(T{} / U{})> {
            return { x / c, y / c, z / c };
        }

        /**
         * @brief Divide component-wise by another tuple and assign
         * @tparam U Component type of RHS
         * @param c RHS tuple (divisor)
         * @return Reference to this tuple
         */
        template <typename U>
        Child<T>& operator/=(Child<U> c) {
            x /= c.x; y /= c.y; z /= c.z;
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
            x = c; y = c; z = c;  // FIXME: should be x/=c, y/=c, z/=c
            return static_cast<Child<T>&>(*this);
        }

        /**
         * @brief Equality comparison
         * @param c RHS tuple
         * @return true if all components equal
         */
        bool operator==(Child<T> c) const { return x == c.x && y == c.y && z == c.z; }

        /**
         * @brief Inequality comparison
         * @param c RHS tuple
         * @return true if any component differs
         */
        bool operator!=(Child<T> c) const { return x != c.x || y != c.y || z != c.z; }

        /**
         * @brief Unary negation
         * @return Tuple with all components negated
         */
        Child<T> operator-() const { return { -x, -y, -z }; }

        /**
         * @brief Indexed access (read-only)
         * @param i Index: 0 for x, 1 for y, 2 for z
         * @return Component value
         */
        T operator[](int i) const {
            if (i == 0) return x;
            if (i == 1) return y;
            return z;
        }

        /**
         * @brief Indexed access (mutable)
         * @param i Index: 0 for x, 1 for y, 2 for z
         * @return Reference to component
         */
        T& operator[](int i) {
            if (i == 0) return x;
            if (i == 1) return y;
            return z;
        }

        T x{};  ///< X component
        T y{};  ///< Y component
        T z{};  ///< Z component
    };

    /**
     * @brief Compute squared length of a 3D tuple
     * @param n Input tuple
     * @return Sum of squares of components: x^2 + y^2 + z^2
     */
    template <template <class> class C, typename T>
    inline auto LengthSquared(GTuple3<C, T> n) {
        return Sqr(n.x) + Sqr(n.y) + Sqr(n.z);
    }

    /**
     * @brief Compute length (magnitude) of a 3D tuple
     * @param v Input tuple
     * @return Euclidean distance from origin: sqrt(x^2 + y^2 + z^2)
     */
    template <template <class> class C, typename T>
    inline auto Length(GTuple3<C, T> v) {
        using std::sqrt;
        return sqrt(LengthSquared(v));
    }

    /**
     * @brief Normalize a 3D tuple to unit length
     * @param v Input tuple
     * @return Unit vector pointing in same direction
     */
    template <template <class> class C, typename T>
    inline auto Normalize(GTuple3<C, T> v) {
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
    inline C<T> FMA(Float a, GTuple3<C, T> b, GTuple3<C, T> c) {
        return { FMA(a, b.x, c.x), FMA(a, b.y, c.y), FMA(a, b.z, c.z) };
    }

    /**
     * @brief Fused multiply-add: a * b + c (component-wise, with tuple as first arg)
     * @param a First tuple
     * @param b Scalar multiplier
     * @param c Tuple to add
     * @return a*b + c
     */
    template <template <class> class C, typename T>
    inline C<T> FMA(GTuple3<C, T> a, Float b, GTuple3<C, T> c) {
        return FMA(b, a, c);
    }

    /**
     * @brief Component-wise absolute value
     * @param t Input tuple
     * @return Tuple with absolute values of each component
     */
    template <template <class> class C, typename T>
    inline C<T> Abs(GTuple3<C, T> t) {
        using std::abs;
        return { abs(t.x), abs(t.y), abs(t.z) };
    }

    /**
     * @brief Component-wise minimum of two tuples
     * @param t1 First tuple
     * @param t2 Second tuple
     * @return Tuple containing min(t1.x, t2.x), min(t1.y, t2.y), min(t1.z, t2.z)
     */
    template <template <class> class C, typename T>
    inline C<T> Min(GTuple3<C, T> t1, GTuple3<C, T> t2) {
        using std::min;
        return { min(t1.x, t2.x), min(t1.y, t2.y), min(t1.z, t2.z) };
    }

    /**
     * @brief Component-wise maximum of two tuples
     * @param t1 First tuple
     * @param t2 Second tuple
     * @return Tuple containing max(t1.x, t2.x), max(t1.y, t2.y), max(t1.z, t2.z)
     */
    template <template <class> class C, typename T>
    inline C<T> Max(GTuple3<C, T> t1, GTuple3<C, T> t2) {
        using std::max;
        return { max(t1.x, t2.x), max(t1.y, t2.y), max(t1.z, t2.z) };
    }

    /**
     * @brief Get the minimum component value
     * @param t Input tuple
     * @return Smallest of x, y, z
     */
    template <template <class> class C, typename T>
    inline T MinComponentValue(GTuple3<C, T> t) {
        using std::min;
        return min({ t.x, t.y, t.z });
    }

    /**
     * @brief Get index of the minimum component
     * @param t Input tuple
     * @return 0 if x is smallest, 1 if y is smallest, 2 if z is smallest
     */
    template <template <class> class C, typename T>
    inline int MinComponentIndex(GTuple3<C, T> t) {
        return (t.x < t.y) ? ((t.x < t.z) ? 0 : 2) : ((t.y < t.z) ? 1 : 2);
    }

    /**
     * @brief Get the maximum component value
     * @param t Input tuple
     * @return Largest of x, y, z
     */
    template <template <class> class C, typename T>
    inline T MaxComponentValue(GTuple3<C, T> t) {
        using std::max;
        return max({ t.x, t.y, t.z });
    }

    /**
     * @brief Get index of the maximum component
     * @param t Input tuple
     * @return 0 if x is largest, 1 if y is largest, 2 if z is largest
     */
    template <template <class> class C, typename T>
    inline int MaxComponentIndex(GTuple3<C, T> t) {
        return (t.x > t.y) ? ((t.x > t.z) ? 0 : 2) : ((t.y > t.z) ? 1 : 2);
    }

} // namespace GMath