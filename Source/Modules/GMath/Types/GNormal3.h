#pragma once
#include <Types/GTuple3.h>

namespace GMath {

    // Forward declaration for Vector3
    template <typename T>
    class Vector3;

    /**
     * @brief 3D normal vector (surface normal, always unit length in practice)
     * @tparam T Component type (float, double, etc.)
     * @note  GNormal3 is distinct from Vector3 for semantic correctness
     *       Normals transform differently from vectors under non-uniform scaling
     */
    template <typename T>
    class  GNormal3 : public GTuple3<GNormal3, T> {
    public:
        // ========================================================================
        // Using declarations to bring base class members into scope
        // ========================================================================
        using GTuple3< GNormal3, T>::x;
        using GTuple3< GNormal3, T>::y;
        using GTuple3< GNormal3, T>::z;
        using GTuple3< GNormal3, T>::HasNaN;
        using GTuple3< GNormal3, T>::operator+;
        using GTuple3< GNormal3, T>::operator*;
        using GTuple3< GNormal3, T>::operator*=;

        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Default constructor (zero-initialized)
         */
         GNormal3() = default;

        /**
         * @brief Construct with all components set to same value
         * @param a Value for x, y, and z components
         */
         GNormal3(T a) : GTuple3<GNormal3, T>(a, a, a) {}

        /**
         * @brief Construct from x, y, z components
         * @param x X component
         * @param y Y component
         * @param z Z component
         */
         GNormal3(T x, T y, T z) : GTuple3<GNormal3, T>(x, y, z) {}

        /**
         * @brief Construct from normal of different type (with conversion)
         * @tparam U Source component type
         * @param v Source normal
         */
        template <typename U>
        explicit  GNormal3<T>( GNormal3<U> v)
            : GTuple3< GNormal3, T>(T(v.x), T(v.y), T(v.z)) {}

        /**
         * @brief Construct from vector of different type (with conversion)
         * @tparam U Source component type
         * @param v Source vector
         * @note Explicit: prevents unintended vector-to-normal conversion
         */
        template <typename U>
        explicit GNormal3<T>(GVector3<U> v)
            : GTuple3< GNormal3, T>(T(v.x), T(v.y), T(v.z)) {}

    };

#if 1
    // ========================================================================
    // Scalar Arithmetic Operators (U +  GNormal3)
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
    typename std::enable_if<!std::is_same< GNormal3<T>, U>::value,  GNormal3<T>>::type
    inline operator+(U s,  GNormal3<T> t) {
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
    typename std::enable_if<!std::is_same< GNormal3<T>, U>::value,  GNormal3<T>>::type
    inline operator-(U s,  GNormal3<T> t) {
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
    typename std::enable_if<!std::is_same< GNormal3<T>, U>::value,  GNormal3<T>>::type
    inline operator*(U s,  GNormal3<T> t) {
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
    typename std::enable_if<!std::is_same< GNormal3<T>, U>::value,  GNormal3<T>>::type
    inline operator/(U s,  GNormal3<T> t) {
        return { s / t.x, s / t.y, s / t.z };
    }
#endif

#if 0
    // ========================================================================
    //  GNormal3 Geometric Functions (Currently disabled)
    // ========================================================================

    /**
     * @brief Compute squared length of a 3D normal
     * @param n Input normal
     * @return Sum of squares of components
     */
    template <typename T>
    inline auto LengthSquared( GNormal3<T> n) -> typename Float {
        return Sqr(n.x) + Sqr(n.y) + Sqr(n.z);
    }

    /**
     * @brief Compute length (magnitude) of a 3D normal
     * @param n Input normal
     * @return Euclidean length
     */
    template <typename T>
    inline auto Length( GNormal3<T> n) -> typename Float {
        using std::sqrt;
        return sqrt(LengthSquared(n));
    }

    /**
     * @brief Normalize a 3D normal to unit length
     * @param n Input normal
     * @return Unit normal
     */
    template <typename T>
    inline auto Normalize( GNormal3<T> n) {
        return n / Length(n);
    }

    /**
     * @brief Dot product of two normals
     * @param v First normal
     * @param w Second normal
     * @return Dot product
     */
    template <typename T>
    inline T Dot( GNormal3<T> v,  GNormal3<T> w) {
        return v.x * w.x + v.y * w.y + v.z * w.z;
    }

    /**
     * @brief Dot product of a normal and a vector
     * @param v Normal
     * @param w Vector
     * @return Dot product
     */
    template <typename T>
    inline T Dot( GNormal3<T> v, Vector3<T> w) {
        return v.x * w.x + v.y * w.y + v.z * w.z;
    }
#endif

} // namespace GMath