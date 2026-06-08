#pragma once
#include <Types/GTuple2.h>
#include <Types/GPoint2.h>
#include <Types/GTypeDeclaration.h>
namespace GMath {
    /**
     * @brief 2D axis-aligned bounding box
     * @tparam T Component type (int, float, double, etc.)
     */
    template <typename T>
    class  GBounds2 {
    public:
        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Construct an empty bounding box (inverted bounds)
         * @note pMin set to max values, pMax set to min values
         */
         GBounds2() {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            pMin = GPoint2<T>(maxNum, maxNum);
            pMax = GPoint2<T>(minNum, minNum);
        }

        /**
         * @brief Construct a degenerate box from a single point
         * @param p Point (pMin = pMax = p)
         */
        explicit  GBounds2(GPoint2<T> p) : pMin(p), pMax(p) {}

        /**
         * @brief Construct a box from two points (min and max computed automatically)
         * @param p1 First corner point
         * @param p2 Second corner point (opposite corner)
         */
         GBounds2(GPoint2<T> p1, GPoint2<T> p2) : pMin(Min(p1, p2)), pMax(Max(p1, p2)) {}

        /**
         * @brief Construct from bounds of different type (with conversion)
         * @tparam U Source component type
         * @param b Source bounds
         */
        template <typename U>
        explicit  GBounds2(const  GBounds2<U>& b) {
            if (b.IsEmpty())
                // Be careful about overflowing float->int conversions and the like
                *this =  GBounds2<T>();
            else {
                pMin = GPoint2<T>(b.pMin);
                pMax = GPoint2<T>(b.pMax);
            }
        }

        // ========================================================================
        // Properties
        // ========================================================================

        /**
         * @brief Get the diagonal vector from pMin to pMax
         * @return Vector from min to max corner
         */
        GVector2<T> Diagonal() const { return pMax - pMin; }

        /**
         * @brief Compute the area of the bounding box
         * @return Area (width * height)
         */
        T Area() const {
            GVector2<T> d = pMax - pMin;
            return d.x * d.y;
        }

        /**
         * @brief Compute bounding circle that contains the box
         * @param center Output: Center of the circle
         * @param radius Output: Radius of the circle
         */
        void BoundingCircle(GPoint2<T>* center, Float* radius) const {
            *center = (pMin + pMax) / 2;
            *radius = Inside(*center, *this) ? Distance(*center, pMax) : 0;
        }

        /**
         * @brief Check if the bounding box is empty (degenerate or inverted)
         * @return true if pMin.x >= pMax.x or pMin.y >= pMax.y
         */
        bool IsEmpty() const { return pMin.x >= pMax.x || pMin.y >= pMax.y; }

        /**
         * @brief Check if the bounding box is degenerate (strictly inverted)
         * @return true if pMin.x > pMax.x or pMin.y > pMax.y
         */
        bool IsDegenerate() const { return pMin.x > pMax.x || pMin.y > pMax.y; }

        /**
         * @brief Get the dimension with the largest extent
         * @return 0 for x-axis, 1 for y-axis
         */
        int MaxDimension() const {
            GVector2<T> diag = Diagonal();
            if (diag.x > diag.y)
                return 0;
            else
                return 1;
        }

        // ========================================================================
        // Accessors
        // ========================================================================

        /**
         * @brief Indexed access to corners (read-only)
         * @param i 0 for pMin, 1 for pMax
         * @return The corner point
         */
        GPoint2<T> operator[](int i) const {
            // DCHECK(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }

        /**
         * @brief Indexed access to corners (mutable)
         * @param i 0 for pMin, 1 for pMax
         * @return Reference to the corner point
         */
        GPoint2<T>& operator[](int i) {
            // DCHECK(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }

        /**
         * @brief Get a specific corner of the bounding box (for 2D: 4 corners)
         * @param corner Corner index (0-3)
         * @return Corner point
         */
        GPoint2<T> Corner(int corner) const {
            // DCHECK(corner >= 0 && corner < 4);
            return GPoint2<T>((*this)[(corner & 1)].x,
                             (*this)[(corner & 2) ? 1 : 0].y);
        }

        // ========================================================================
        // Interpolation and Offset
        // ========================================================================

        /**
         * @brief Bilinear interpolation inside the bounding box
         * @param t Interpolation parameters (0-1 range)
         * @return Interpolated point
         */
        GPoint2<T> Lerp2(GPoint2f t) const {
            return GPoint2<T>((1 - t.x) * pMin.x + t.x * pMax.x,
                             (1 - t.y) * pMin.y + t.y * pMax.y);
        }

        /**
         * @brief Get normalized offset of a point within the bounding box
         * @param p Point inside the box
         * @return Offset vector with components in [0,1] range
         */
        GVector2<T> Offset(GPoint2<T> p) const {
            GVector2<T> o = p - pMin;
            if (pMax.x > pMin.x)
                o.x /= pMax.x - pMin.x;
            if (pMax.y > pMin.y)
                o.y /= pMax.y - pMin.y;
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
        bool operator==(const  GBounds2<T>& b) const {
            return b.pMin == pMin && b.pMax == pMax;
        }

        /**
         * @brief Inequality comparison
         * @param b RHS bounding box
         * @return true if pMin or pMax differ
         */
        bool operator!=(const  GBounds2<T>& b) const {
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
        bool IntersectP(GPoint2<T> o, GVector2<T> d, Float raytMax, GVector2<T> invDir, const int dirIsNeg[2]) const;

        // ========================================================================
        // Public Members
        // ========================================================================

        GPoint2<T> pMin;  ///< Minimum corner (smallest x,y)
        GPoint2<T> pMax;  ///< Maximum corner (largest x,y)
    };

    // ========================================================================
    // Free Functions
    // ========================================================================



    // ========================================================================
    // Ray-Box Intersection Implementation (2D)
    // ========================================================================

    /**
     * @brief Ray-box intersection test using slabs method (2D)
     * @tparam T Component type
     * @param o Ray origin
     * @param d Ray direction
     * @param raytMax Maximum ray distance
     * @param invDir Inverse of ray direction (1/d)
     * @param dirIsNeg Direction signs: 1 if component negative, 0 otherwise
     * @return true if ray intersects the bounding box
     */
    template <typename T>
    inline bool  GBounds2<T>::IntersectP(GPoint2<T> o, GVector2<T> d, Float raytMax, GVector2<T> invDir, const int dirIsNeg[2]) const {
        const GBounds2f& bounds = *this;

        // Check for ray intersection against x slab
        Float tMin = (bounds[dirIsNeg[0]].x - o.x) * invDir.x;
        Float tMax = (bounds[1 - dirIsNeg[0]].x - o.x) * invDir.x;

        // Check for ray intersection against y slab
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

        return (tMin < raytMax) && (tMax > 0);
    }
} // namespace GMath