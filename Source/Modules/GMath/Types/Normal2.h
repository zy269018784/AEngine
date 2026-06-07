#pragma once
#include <Types/Tuple2.h>

namespace GMath {

    // Forward declaration for Vector2
    template <typename T>
    class Vector2;

    /**
     * @brief 2D normal vector (surface normal, always unit length in practice)
     * @tparam T Component type (float, double, etc.)
     * @note Normal2 is distinct from Vector2 for semantic correctness
     *       Normals transform differently from vectors under non-uniform scaling
     */
    template <typename T>
    class Normal2 : public Tuple2<Normal2, T> {
    public:
        // ========================================================================
        // Using declarations to bring base class members into scope
        // ========================================================================
        using Tuple2<Normal2, T>::x;
        using Tuple2<Normal2, T>::y;
        using Tuple2<Normal2, T>::HasNaN;
        using Tuple2<Normal2, T>::operator+;
        using Tuple2<Normal2, T>::operator*;
        using Tuple2<Normal2, T>::operator*=;

        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Default constructor (zero-initialized)
         */
        Normal2() = default;

        /**
         * @brief Construct from x, y components
         * @param x X component
         * @param y Y component
         */
        Normal2(T x, T y) : Tuple2<Normal2, T>(x, y) {}

        /**
         * @brief Construct from normal of different type (with conversion)
         * @tparam U Source component type
         * @param v Source normal
         */
        template <typename U>
        explicit Normal2<T>(Normal2<U> v)
            : Tuple2<Normal2, T>(T(v.x), T(v.y)) {}

        /**
         * @brief Construct from vector of different type (with conversion)
         * @tparam U Source component type
         * @param v Source vector
         * @note Explicit: prevents unintended vector-to-normal conversion
         */
        template <typename U>
        explicit Normal2<T>(Vector2<U> v)
            : Tuple2<Normal2, T>(T(v.x), T(v.y)) {}
    };

#if 1
    // ========================================================================
    // Scalar Arithmetic Operators (U + Normal2)
    // ========================================================================

    /**
     * @brief Scalar addition: s + normal
     * @tparam T Normal component type
     * @tparam U Scalar type
     * @param s Left-hand side scalar
     * @param t Right-hand side normal
     * @return Normal with components (s + t.x, s + t.y)
     */
    template <typename T, typename U>
    typename std::enable_if<!std::is_same<Normal2<T>, U>::value, Normal2<T>>::type
    inline operator+(U s, Normal2<T> t) {
        return { s + t.x, s + t.y };
    }

    /**
     * @brief Scalar subtraction: s - normal
     * @tparam T Normal component type
     * @tparam U Scalar type
     * @param s Left-hand side scalar
     * @param t Right-hand side normal
     * @return Normal with components (s - t.x, s - t.y)
     */
    template <typename T, typename U>
    typename std::enable_if<!std::is_same<Normal2<T>, U>::value, Normal2<T>>::type
    inline operator-(U s, Normal2<T> t) {
        return { s - t.x, s - t.y };
    }

    /**
     * @brief Scalar multiplication: s * normal
     * @tparam T Normal component type
     * @tparam U Scalar type
     * @param s Left-hand side scalar multiplier
     * @param t Right-hand side normal
     * @return Normal with components (s * t.x, s * t.y)
     */
    template <typename T, typename U>
    typename std::enable_if<!std::is_same<Normal2<T>, U>::value, Normal2<T>>::type
    inline operator*(U s, Normal2<T> t) {
        return { s * t.x, s * t.y };
    }

    /**
     * @brief Scalar division: s / normal (component-wise)
     * @tparam T Normal component type
     * @tparam U Scalar type
     * @param s Left-hand side scalar dividend
     * @param t Right-hand side normal divisor
     * @return Normal with components (s / t.x, s / t.y)
     */
    template <typename T, typename U>
    typename std::enable_if<!std::is_same<Normal2<T>, U>::value, Normal2<T>>::type
    inline operator/(U s, Normal2<T> t) {
        return { s / t.x, s / t.y };
    }
#endif

#if 0
    // ========================================================================
    // Normal2 Geometric Functions (Currently disabled)
    // ========================================================================

    /**
     * @brief Compute squared length of a 2D normal
     * @param n Input normal
     * @return Sum of squares of components
     */
    template <typename T>
    inline auto LengthSquared(Normal2<T> n) -> typename Float {
        return Sqr(n.x) + Sqr(n.y);
    }

    /**
     * @brief Compute length (magnitude) of a 2D normal
     * @param n Input normal
     * @return Euclidean length
     */
    template <typename T>
    inline auto Length(Normal2<T> n) -> typename Float {
        using std::sqrt;
        return sqrt(LengthSquared(n));
    }

    /**
     * @brief Normalize a 2D normal to unit length
     * @param n Input normal
     * @return Unit normal
     */
    template <typename T>
    inline auto Normalize(Normal2<T> n) {
        return n / Length(n);
    }

    /**
     * @brief Dot product of two normals
     * @param v First normal
     * @param w Second normal
     * @return Dot product
     */
    template <typename T>
    inline T Dot(Normal2<T> v, Normal2<T> w) {
        return v.x * w.x + v.y * w.y;
    }

    /**
     * @brief Dot product of a normal and a vector
     * @param v Normal
     * @param w Vector
     * @return Dot product
     */
    template <typename T>
    inline T Dot(Normal2<T> v, Vector2<T> w) {
        return v.x * w.x + v.y * w.y;
    }
#endif

} // namespace GMath