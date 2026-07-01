#pragma once
#include <string>
#include <GMath/Types/GTypes.h>

namespace GMath {

    /**
     * @brief GRay defined by origin and direction
     * @note Represents a ray in 3D space: R(t) = o + d * t
     */
    class GRay {
    public:
        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Default constructor - creates an uninitialized ray
         */
        GRay() = default;

        /**
         * @brief Construct a ray from origin and direction
         * @param o GRay origin point
         * @param d GRay direction vector (should be normalized for consistent t values)
         */
        GRay(GPoint3f o, GVector3f d) : o(o), d(d) {}

        // ========================================================================
        // Accessors
        // ========================================================================

        /**
         * @brief Evaluate the ray at parameter t
         * @param t Parameter value along the ray
         * @return Point on the ray: o + d * t
         */
        GPoint3f operator()(Float t) const { return o + d * t; }

        // ========================================================================
        // Public Members
        // ========================================================================

        GPoint3f  o;      ///< GRay origin point
        GVector3f d;     ///< GRay direction vector (typically normalized)
    };

} // namespace GMath