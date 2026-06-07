#pragma once
#include <Types/Tuple3.h>

namespace GMath {

    // Forward declaration for Vector3
    template <typename T>
    class Vector3;

    /**
     * @brief 3D normal vector (surface normal, always unit length in practice)
     * @tparam T Component type (float, double, etc.)
     * @note Normal3 is distinct from Vector3 for semantic correctness
     *       Normals transform differently from vectors under non-uniform scaling
     */
    template <typename T>
    class Normal3 : public Tuple3<Normal3, T> {
    public:
        // ========================================================================
        // Using declarations to bring base class members into scope
        // ========================================================================
        using Tuple3<Normal3, T>::x;
        using Tuple3<Normal3, T>::y;
        using Tuple3<Normal3, T>::z;
        using Tuple3<Normal3, T>::HasNaN;
        using Tuple3<Normal3, T>::operator+;
        using Tuple3<Normal3, T>::operator*;
        using Tuple3<Normal3, T>::operator*=;

        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Default constructor (zero-initialized)
         */
        Normal3() = default;

        /**
         * @brief Construct with all components set to same value
         * @param a Value for x, y, and z components
         */
        Normal3(T a) : Tuple3<Normal3, T>(a, a, a) {}

        /**
         * @brief Construct from x, y, z components
         * @param x X component
         * @param y Y component
         * @param z Z component
         */
        Normal3(T x, T y, T z) : Tuple3<Normal3, T>(x, y, z) {}

        /**
         * @brief Construct from normal of different type (with conversion)
         * @tparam U Source component type
         * @param v Source normal
         */
        template <typename U>
        explicit Normal3<T>(Normal3<U> v)
            : Tuple3<Normal3, T>(T(v.x), T(v.y), T(v.z)) {}

        /**
         * @brief Construct from vector of different type (with conversion)
         * @tparam U Source component type
         * @param v Source vector
         * @note Explicit: prevents unintended vector-to-normal conversion
         */
        template <typename U>
        explicit Normal3<T>(Vector3<U> v)
            : Tuple3<Normal3, T>(T(v.x), T(v.y), T(v.z)) {}
    };

#if 1
    // ========================================================================
    // Scalar Arithmetic Operators (U + Normal3)
    // ========================================================================

    /**
     * @brief Scalar addition: s + normal
     * @tparam T Normal component type
     * @tparam U Scalar type
     * @param s Left-hand side scalar
     * @param t Right-hand side normal
     * @return Normal with components (s + t.x, s + t.y, s + t.z)
     */
    template <typename T, typename U>
    typename std::enable_if<!std::is_same<Normal3<T>, U>::value, Normal3<T>>::type
    inline operator+(U s, Normal3<T> t) {
        return { s + t.x, s + t.y, s + t.z };
    }

    /**
     * @brief Scalar subtraction: s - normal
     * @tparam T Normal component type
     * @tparam U Scalar type
     * @param s Left-hand side scalar
     * @param t Right-hand side normal
     * @return Normal with components (s - t.x, s - t.y, s - t.z)
     */
    template <typename T, typename U>
    typename std::enable_if<!std::is_same<Normal3<T>, U>::value, Normal3<T>>::type
    inline operator-(U s, Normal3<T> t) {
        return { s - t.x, s - t.y, s - t.z };
    }

    /**
     * @brief Scalar multiplication: s * normal
     * @tparam T Normal component type
     * @tparam U Scalar type
     * @param s Left-hand side scalar multiplier
     * @param t Right-hand side normal
     * @return Normal with components (s * t.x, s * t.y, s * t.z)
     */
    template <typename T, typename U>
    typename std::enable_if<!std::is_same<Normal3<T>, U>::value, Normal3<T>>::type
    inline operator*(U s, Normal3<T> t) {
        return { s * t.x, s * t.y, s * t.z };
    }

    /**
     * @brief Scalar division: s / normal (component-wise)
     * @tparam T Normal component type
     * @tparam U Scalar type
     * @param s Left-hand side scalar dividend
     * @param t Right-hand side normal divisor
     * @return Normal with components (s / t.x, s / t.y, s / t.z)
     */
    template <typename T, typename U>
    typename std::enable_if<!std::is_same<Normal3<T>, U>::value, Normal3<T>>::type
    inline operator/(U s, Normal3<T> t) {
        return { s / t.x, s / t.y, s / t.z };
    }
#endif

#if 0
    // ========================================================================
    // Normal3 Geometric Functions (Currently disabled)
    // ========================================================================

    /**
     * @brief Compute squared length of a 3D normal
     * @param n Input normal
     * @return Sum of squares of components
     */
    template <typename T>
    inline auto LengthSquared(Normal3<T> n) -> typename Float {
        return Sqr(n.x) + Sqr(n.y) + Sqr(n.z);
    }

    /**
     * @brief Compute length (magnitude) of a 3D normal
     * @param n Input normal
     * @return Euclidean length
     */
    template <typename T>
    inline auto Length(Normal3<T> n) -> typename Float {
        using std::sqrt;
        return sqrt(LengthSquared(n));
    }

    /**
     * @brief Normalize a 3D normal to unit length
     * @param n Input normal
     * @return Unit normal
     */
    template <typename T>
    inline auto Normalize(Normal3<T> n) {
        return n / Length(n);
    }

    /**
     * @brief Dot product of two normals
     * @param v First normal
     * @param w Second normal
     * @return Dot product
     */
    template <typename T>
    inline T Dot(Normal3<T> v, Normal3<T> w) {
        return v.x * w.x + v.y * w.y + v.z * w.z;
    }

    /**
     * @brief Dot product of a normal and a vector
     * @param v Normal
     * @param w Vector
     * @return Dot product
     */
    template <typename T>
    inline T Dot(Normal3<T> v, Vector3<T> w) {
        return v.x * w.x + v.y * w.y + v.z * w.z;
    }
#endif

} // namespace GMath