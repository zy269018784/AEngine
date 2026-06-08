#pragma once
#include <Types/GTuple3.h>
#include <Types/GPoint3.h>
#include <Types/GTypeDeclaration.h>
namespace GMath {
    // ========================================================================
    //  GBounds3 Class
    // ========================================================================

    /**
     * @brief 3D axis-aligned bounding box
     * @tparam T Component type (int, float, double, etc.)
     */
    template <typename T>
    class  GBounds3 {
    public:
        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Construct an empty bounding box (inverted bounds)
         * @note pMin set to max values, pMax set to min values
         */
         GBounds3() {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            pMin = GPoint3<T>(maxNum, maxNum, maxNum);
            pMax = GPoint3<T>(minNum, minNum, minNum);
        }

        /**
         * @brief Construct a degenerate box from a single point
         * @param p Point (pMin = pMax = p)
         */
        explicit  GBounds3(GPoint3<T> p) : pMin(p), pMax(p) {}

        /**
         * @brief Construct a box from two points (min and max computed automatically)
         * @param p1 First corner point
         * @param p2 Second corner point (opposite corner)
         */
         GBounds3(GPoint3<T> p1, GPoint3<T> p2) : pMin(Min(p1, p2)), pMax(Max(p1, p2)) {}

        /**
         * @brief Construct from bounds of different type (with conversion)
         * @tparam U Source component type
         * @param b Source bounds
         */
        template <typename U>
        explicit  GBounds3(const  GBounds3<U>& b) {
            if (b.IsEmpty())
                // Be careful about overflowing float->int conversions and the like
                    *this =  GBounds3<T>();
            else {
                pMin = GPoint3<T>(b.pMin);
                pMax = GPoint3<T>(b.pMax);
            }
        }

        /**
         * @brief Get the diagonal vector from pMin to pMax
         * @return Vector from min to max corner
         */
        GVector3<T> Diagonal() const { return pMax - pMin; }

        // ========================================================================
        // Geometric Properties
        // ========================================================================

        /**
         * @brief Compute the surface area of the bounding box
         * @return Surface area (sum of all 6 faces)
         */
        T Area() const {
            GVector3<T> d = Diagonal();
            return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
        }

        /**
         * @brief Compute the volume of the bounding box
         * @return Volume (width * height * depth)
         */
        T Volume() const {
            GVector3<T> d = Diagonal();
            return d.x * d.y * d.z;
        }

        /**
         * @brief Compute bounding sphere that contains the box
         * @param center Output: Center of the sphere
         * @param radius Output: Radius of the sphere
         */
        void BoundingSphere(GPoint3<T>* center, Float* radius) const {
            *center = (pMin + pMax) / 2;
            *radius = Inside(*center, *this) ? Distance(*center, pMax) : 0;
        }

        /**
 * @brief Check if the bounding box is empty (degenerate or inverted)
 * @return true if pMin.x >= pMax.x or pMin.y >= pMax.y or pMin.z >= pMax.z
 */
        bool IsEmpty() const { return pMin.x >= pMax.x || pMin.y >= pMax.y || pMin.z >= pMax.z; }

        /**
         * @brief Check if the bounding box is degenerate (strictly inverted)
         * @return true if pMin.x > pMax.x or pMin.y > pMax.y or pMin.z > pMax.z
         */
        bool IsDegenerate() const { return pMin.x > pMax.x || pMin.y > pMax.y || pMin.z > pMax.z; }

        /**
         * @brief Get the dimension with the largest extent
         * @return 0 for x-axis, 1 for y-axis, 2 for z-axis
         */
        int MaxDimension() const {
            GVector3<T> d = Diagonal();
            if (d.x > d.y && d.x > d.z)
                return 0;
            else if (d.y > d.z)
                return 1;
            else
                return 2;
        }

        // ========================================================================
        // Accessors
        // ========================================================================

        /**
         * @brief Indexed access to corners (read-only)
         * @param i 0 for pMin, 1 for pMax
         * @return The corner point
         */
        GPoint3<T> operator[](int i) const {
            return (i == 0) ? pMin : pMax;
        }

        /**
         * @brief Indexed access to corners (mutable)
         * @param i 0 for pMin, 1 for pMax
         * @return Reference to the corner point
         */
        GPoint3<T>& operator[](int i) {
            return (i == 0) ? pMin : pMax;
        }

        /**
         * @brief Get a specific corner of the bounding box (for 3D: 8 corners)
         * @param corner Corner index (0-7)
         * @return Corner point
         */
        GPoint3<T> Corner(int corner) const {
            // DCHECK(corner >= 0 && corner < 8);
            return GPoint3<T>((*this)[(corner & 1)].x,
                             (*this)[(corner & 2) ? 1 : 0].y,
                             (*this)[(corner & 4) ? 1 : 0].z);
        }

        // ========================================================================
        // Interpolation and Offset
        // ========================================================================

        /**
         * @brief Trilinear interpolation inside the bounding box
         * @param t Interpolation parameters (0-1 range)
         * @return Interpolated point
         */
        GPoint3<T> Lerp3(GPoint3f t) const {
            return GPoint3<T>((1 - t.x) * pMin.x + t.x * pMax.x,
                             (1 - t.y) * pMin.y + t.y * pMax.y,
                             (1 - t.z) * pMin.z + t.z * pMax.z);
        }

        /**
         * @brief Get normalized offset of a point within the bounding box
         * @param p Point inside the box
         * @return Offset vector with components in [0,1] range
         */
        GVector3<T> Offset(GPoint3<T> p) const {
            GVector3<T> o = p - pMin;
            if (pMax.x > pMin.x)
                o.x /= pMax.x - pMin.x;
            if (pMax.y > pMin.y)
                o.y /= pMax.y - pMin.y;
            if (pMax.z > pMin.z)
                o.z /= pMax.z - pMin.z;
            return o;
        }

        // ========================================================================
        // Comparison Operators
        // ========================================================================

        /**
         * @brief Equality comparison
         * @param b RHS bounding box
         * @return true if both pMin and pMax are equal
         */
        bool operator==(const  GBounds3<T>& b) const {
            return b.pMin == pMin && b.pMax == pMax;
        }

        /**
         * @brief Inequality comparison
         * @param b RHS bounding box
         * @return true if pMin or pMax differ
         */
        bool operator!=(const  GBounds3<T>& b) const {
            return b.pMin != pMin || b.pMax != pMax;
        }

        // ========================================================================
        // Ray Intersection
        // ========================================================================

        /**
         * @brief Test if a ray intersects the bounding box
         * @param o Ray origin
         * @param d Ray direction
         * @param tMax Maximum ray parameter
         * @param invDir Inverse of ray direction (1/d)
         * @param dirIsNeg Direction signs (1 if component negative, 0 otherwise)
         * @return true if ray intersects the bounding box
         */
        bool IntersectP(GPoint3<T> o, GVector3<T> d, Float raytMax, GVector3<T> invDir, const int dirIsNeg[3]) const;

        // ========================================================================
        // Public Members
        // ========================================================================

        GPoint3<T> pMin;  ///< Minimum corner (smallest x,y,z)
        GPoint3<T> pMax;  ///< Maximum corner (largest x,y,z)
    };

    // ========================================================================
    // Ray-Box Intersection Implementation
    // ========================================================================

    /**
     * @brief Ray-box intersection test using slabs method
     * @tparam T Component type
     * @param o Ray origin
     * @param d Ray direction
     * @param raytMax Maximum ray distance
     * @param invDir Inverse of ray direction (1/d)
     * @param dirIsNeg Direction signs: 1 if component negative, 0 otherwise
     * @return true if ray intersects the bounding box
     */
    template <typename T>
    inline bool  GBounds3<T>::IntersectP(GPoint3<T> o, GVector3<T> d, Float raytMax, GVector3<T> invDir, const int dirIsNeg[3]) const {
        const GBounds3f& bounds = *this;

        // Check for ray intersection against x and y slabs
        Float tMin = (bounds[dirIsNeg[0]].x - o.x) * invDir.x;
        Float tMax = (bounds[1 - dirIsNeg[0]].x - o.x) * invDir.x;
        Float tyMin = (bounds[dirIsNeg[1]].y - o.y) * invDir.y;
        Float tyMax = (bounds[1 - dirIsNeg[1]].y - o.y) * invDir.y;

        // Update tMax and tyMax to ensure robust bounds intersection
        tMax *= 1 + 2 * gamma(3);
        tyMax *= 1 + 2 * gamma(3);

        if (tMin > tyMax || tyMin > tMax)
            return false;
        if (tyMin > tMin)
            tMin = tyMin;
        if (tyMax < tMax)
            tMax = tyMax;

        // Check for ray intersection against z slab
        Float tzMin = (bounds[dirIsNeg[2]].z - o.z) * invDir.z;
        Float tzMax = (bounds[1 - dirIsNeg[2]].z - o.z) * invDir.z;

        // Update tzMax to ensure robust bounds intersection
        tzMax *= 1 + 2 * gamma(3);

        if (tMin > tzMax || tzMin > tMax)
            return false;
        if (tzMin > tMin)
            tMin = tzMin;
        if (tzMax < tMax)
            tMax = tzMax;

        return (tMin < raytMax) && (tMax > 0);
    }

} // namespace GMath