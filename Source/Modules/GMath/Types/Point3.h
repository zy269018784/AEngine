#pragma once
#include <Types/Tuple3.h>

namespace GMath {

    // Forward declaration for Vector3
    template <typename T>
    class Vector3;

    /**
     * @brief 3D point in space
     * @tparam T Component type (int, float, double, etc.)
     * @note Points represent positions, vectors represent directions.
     *       Points and vectors have different transformation behaviors.
     */
    template <typename T>
    class Point3 : public Tuple3<Point3, T> {
    public:
        // ========================================================================
        // Using declarations to bring base class members into scope
        // ========================================================================
        using Tuple3<Point3, T>::x;
        using Tuple3<Point3, T>::y;
        using Tuple3<Point3, T>::z;
        using Tuple3<Point3, T>::HasNaN;
        using Tuple3<Point3, T>::operator+;
        using Tuple3<Point3, T>::operator+=;
        using Tuple3<Point3, T>::operator-;
        using Tuple3<Point3, T>::operator-=;
        using Tuple3<Point3, T>::operator*;
        using Tuple3<Point3, T>::operator*=;
        using Tuple3<Point3, T>::operator/;
        using Tuple3<Point3, T>::operator/=;

        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Default constructor (zero-initialized)
         */
        Point3() = default;

        /**
         * @brief Construct from x, y, z components
         * @param x X coordinate
         * @param y Y coordinate
         * @param z Z coordinate
         */
        Point3(T x, T y, T z) : Tuple3<Point3, T>(x, y, z) {}

        /**
         * @brief Construct from point of different type (with conversion)
         * @tparam U Source component type
         * @param p Source point
         */
        template <typename U>
        explicit Point3(Point3<U> p)
            : Tuple3<Point3, T>(T(p.x), T(p.y), T(p.z)) {}

        /**
         * @brief Construct from vector of different type (with conversion)
         * @tparam U Source component type
         * @param v Source vector
         * @note Explicit: prevents unintended vector-to-point conversion
         */
        template <typename U>
        explicit Point3(Vector3<U> v)
            : Tuple3<Point3, T>(T(v.x), T(v.y), T(v.z)) {}

        // ========================================================================
        // Point-Vector Arithmetic
        // ========================================================================

        /**
         * @brief Point + Vector = Point (translation)
         * @tparam U Vector component type
         * @param v Vector to add
         * @return Translated point
         */
        template <typename U>
        auto operator+(Vector3<U> v) const -> Point3<decltype(T{} + U{})> {
            return { x + v.x, y + v.y, z + v.z };
        }

        /**
         * @brief Point - Vector = Point (reverse translation)
         * @tparam U Vector component type
         * @param v Vector to subtract
         * @return Translated point
         */
        template <typename U>
        auto operator-(Vector3<U> v) const -> Point3<decltype(T{} - U{})> {
            return { x - v.x, y - v.y, z - v.z };
        }

        /**
         * @brief Point - Point = Vector (difference)
         * @tparam U Point component type
         * @param p Point to subtract
         * @return Vector from p to this point
         */
        template <typename U>
        auto operator-(Point3<U> p) const -> Vector3<decltype(T{} - U{})> {
            return { x - p.x, y - p.y, z - p.z };
        }

        // ========================================================================
        // Compound Assignment
        // ========================================================================

        /**
         * @brief Point += Vector (in-place translation)
         * @tparam U Vector component type
         * @param v Vector to add
         * @return Reference to this point
         */
        template <typename U>
        Point3<T>& operator+=(Vector3<U> v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        /**
         * @brief Point -= Vector (in-place reverse translation)
         * @tparam U Vector component type
         * @param v Vector to subtract
         * @return Reference to this point
         */
        template <typename U>
        Point3<T>& operator-=(Vector3<U> v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
    };

    // ========================================================================
    // Scalar-Point Arithmetic Operators
    // ========================================================================

    /**
     * @brief Scalar + Point (add scalar to each component)
     * @tparam U Scalar type (must be fundamental type)
     * @tparam T Point component type
     * @param u Scalar to add
     * @param pt Point to add to
     * @return Point with components (u + pt.x, u + pt.y, u + pt.z)
     */
    template <typename U, typename T>
    std::enable_if_t<std::is_fundamental_v<U>, Point3<decltype(T{} + U{})>>
    operator+(U u, Point3<T> pt) {
        return { u + pt.x, u + pt.y, u + pt.z };
    }

    /**
     * @brief Scalar - Point (subtract point components from scalar)
     * @tparam U Scalar type (must be fundamental type)
     * @tparam T Point component type
     * @param u Scalar to subtract from
     * @param pt Point to subtract
     * @return Point with components (u - pt.x, u - pt.y, u - pt.z)
     */
    template <typename U, typename T>
    std::enable_if_t<std::is_fundamental_v<U>, Point3<decltype(T{} - U{})>>
    operator-(U u, Point3<T> pt) {
        return { u - pt.x, u - pt.y, u - pt.z };
    }

    /**
     * @brief Scalar * Point (scale point by scalar)
     * @tparam U Scalar type (must be fundamental type)
     * @tparam T Point component type
     * @param u Scalar multiplier
     * @param pt Point to scale
     * @return Point with components (u * pt.x, u * pt.y, u * pt.z)
     */
    template <typename U, typename T>
    std::enable_if_t<std::is_fundamental_v<U>, Point3<decltype(T{} * U{})>>
    operator*(U u, Point3<T> pt) {
        return { u * pt.x, u * pt.y, u * pt.z };
    }

    /**
     * @brief Scalar / Point (divide scalar by point components)
     * @tparam U Scalar type (must be fundamental type)
     * @tparam T Point component type
     * @param u Scalar dividend
     * @param pt Point divisor
     * @return Point with components (u / pt.x, u / pt.y, u / pt.z)
     */
    template <typename U, typename T>
    std::enable_if_t<std::is_fundamental_v<U>, Point3<decltype(T{} - U{})>>
    operator/(U u, Point3<T> pt) {
        return { u / pt.x, u / pt.y, u / pt.z };
    }

} // namespace GMath