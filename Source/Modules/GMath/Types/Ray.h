#pragma once
#include <string>
#include <Types/Types.h>

namespace GMath {

    /**
     * @brief Ray defined by origin and direction
     * @note Represents a ray in 3D space: R(t) = o + d * t
     */
    class Ray {
    public:
        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Default constructor - creates an uninitialized ray
         */
        Ray() = default;

        /**
         * @brief Construct a ray from origin and direction
         * @param o Ray origin point
         * @param d Ray direction vector (should be normalized for consistent t values)
         */
        Ray(Point3f o, Vector3f d) : o(o), d(d) {}

        // ========================================================================
        // Accessors
        // ========================================================================

        /**
         * @brief Evaluate the ray at parameter t
         * @param t Parameter value along the ray
         * @return Point on the ray: o + d * t
         */
        Point3f operator()(Float t) const { return o + d * t; }

        // ========================================================================
        // Public Members
        // ========================================================================

        Point3f o;      ///< Ray origin point
        Vector3f d;     ///< Ray direction vector (typically normalized)
    };

} // namespace GMath