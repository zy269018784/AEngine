#pragma once
#include <Types/Tuple2.h>

namespace GMath {

    // Forward declaration for Vector2
    template <typename T>
    class Vector2;

    /**
     * @brief 2D point in space
     * @tparam T Component type (int, float, double, etc.)
     * @note Points represent positions, vectors represent directions.
     *       Points and vectors have different transformation behaviors.
     */
    template <typename T>
    class Point2 : public Tuple2<Point2, T> {
    public:
        // ========================================================================
        // Using declarations to bring base class members into scope
        // ========================================================================
        using Tuple2<Point2, T>::x;
        using Tuple2<Point2, T>::y;
        using Tuple2<Point2, T>::HasNaN;
        using Tuple2<Point2, T>::operator+;
        using Tuple2<Point2, T>::operator+=;
        using Tuple2<Point2, T>::operator-;
        using Tuple2<Point2, T>::operator-=;
        using Tuple2<Point2, T>::operator*;
        using Tuple2<Point2, T>::operator*=;
        using Tuple2<Point2, T>::operator/;
        using Tuple2<Point2, T>::operator/=;

        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Default constructor (zero-initialized)
         */
        Point2() = default;

        /**
         * @brief Construct from x, y components
         * @param x X coordinate
         * @param y Y coordinate
         */
        Point2(T x, T y) : Tuple2<Point2, T>(x, y) {}

        /**
         * @brief Construct from point of different type (with conversion)
         * @tparam U Source component type
         * @param p Source point
         */
        template <typename U>
        explicit Point2(Point2<U> p)
            : Tuple2<Point2, T>(T(p.x), T(p.y)) {}

        /**
         * @brief Construct from vector of different type (with conversion)
         * @tparam U Source component type
         * @param v Source vector
         * @note Explicit: prevents unintended vector-to-point conversion
         */
        template <typename U>
        explicit Point2(Vector2<U> v)
            : Tuple2<Point2, T>(T(v.x), T(v.y)) {}

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
        auto operator+(Vector2<U> v) const -> Point2<decltype(T{} + U{})> {
            return { x + v.x, y + v.y };
        }

        /**
         * @brief Point - Vector = Point (reverse translation)
         * @tparam U Vector component type
         * @param v Vector to subtract
         * @return Translated point
         */
        template <typename U>
        auto operator-(Vector2<U> v) const -> Point2<decltype(T{} - U{})> {
            return { x - v.x, y - v.y };
        }

        /**
         * @brief Point - Point = Vector (difference)
         * @tparam U Point component type
         * @param p Point to subtract
         * @return Vector from p to this point
         */
        template <typename U>
        auto operator-(Point2<U> p) const -> Vector2<decltype(T{} - U{})> {
            return { x - p.x, y - p.y };
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
        Point2<T>& operator+=(Vector2<U> v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        /**
         * @brief Point -= Vector (in-place reverse translation)
         * @tparam U Vector component type
         * @param v Vector to subtract
         * @return Reference to this point
         */
        template <typename U>
        Point2<T>& operator-=(Vector2<U> v) {
            x -= v.x;
            y -= v.y;
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
     * @return Point with components (u + pt.x, u + pt.y)
     */
    template <typename U, typename T>
    std::enable_if_t<std::is_fundamental_v<U>, Point2<decltype(T{} + U{})>>
    inline operator+(U u, Point2<T> pt) {
        return { u + pt.x, u + pt.y };
    }

    /**
     * @brief Scalar - Point (subtract point components from scalar)
     * @tparam U Scalar type (must be fundamental type)
     * @tparam T Point component type
     * @param u Scalar to subtract from
     * @param pt Point to subtract
     * @return Point with components (u - pt.x, u - pt.y)
     */
    template <typename U, typename T>
    std::enable_if_t<std::is_fundamental_v<U>, Point2<decltype(T{} - U{})>>
    inline operator-(U u, Point2<T> pt) {
        return { u - pt.x, u - pt.y };
    }

    /**
     * @brief Scalar * Point (scale point by scalar)
     * @tparam U Scalar type (must be fundamental type)
     * @tparam T Point component type
     * @param u Scalar multiplier
     * @param pt Point to scale
     * @return Point with components (u * pt.x, u * pt.y)
     */
    template <typename U, typename T>
    std::enable_if_t<std::is_fundamental_v<U>, Point2<decltype(T{} * U{})>>
    inline operator*(U u, Point2<T> pt) {
        return { u * pt.x, u * pt.y };
    }

    /**
     * @brief Scalar / Point (divide scalar by point components)
     * @tparam U Scalar type (must be fundamental type)
     * @tparam T Point component type
     * @param u Scalar dividend
     * @param pt Point divisor
     * @return Point with components (u / pt.x, u / pt.y)
     */
    template <typename U, typename T>
    std::enable_if_t<std::is_fundamental_v<U>, Point2<decltype(T{} - U{})>>
    inline operator/(U u, Point2<T> pt) {
        return { u / pt.x, u / pt.y };
    }

} // namespace GMath