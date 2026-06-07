#pragma once
#include <Types/Tuple2.h>
#include <Types/Point2.h>
#include <Types/TypeDeclaration.h>
namespace GMath {
    /**
     * @brief 2D axis-aligned bounding box
     * @tparam T Component type (int, float, double, etc.)
     */
    template <typename T>
    class Bounds2 {
    public:
        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Construct an empty bounding box (inverted bounds)
         * @note pMin set to max values, pMax set to min values
         */
        Bounds2() {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            pMin = Point2<T>(maxNum, maxNum);
            pMax = Point2<T>(minNum, minNum);
        }

        /**
         * @brief Construct a degenerate box from a single point
         * @param p Point (pMin = pMax = p)
         */
        explicit Bounds2(Point2<T> p) : pMin(p), pMax(p) {}

        /**
         * @brief Construct a box from two points (min and max computed automatically)
         * @param p1 First corner point
         * @param p2 Second corner point (opposite corner)
         */
        Bounds2(Point2<T> p1, Point2<T> p2) : pMin(Min(p1, p2)), pMax(Max(p1, p2)) {}

        /**
         * @brief Construct from bounds of different type (with conversion)
         * @tparam U Source component type
         * @param b Source bounds
         */
        template <typename U>
        explicit Bounds2(const Bounds2<U>& b) {
            if (b.IsEmpty())
                // Be careful about overflowing float->int conversions and the like
                *this = Bounds2<T>();
            else {
                pMin = Point2<T>(b.pMin);
                pMax = Point2<T>(b.pMax);
            }
        }

        // ========================================================================
        // Properties
        // ========================================================================

        /**
         * @brief Get the diagonal vector from pMin to pMax
         * @return Vector from min to max corner
         */
        Vector2<T> Diagonal() const { return pMax - pMin; }

        /**
         * @brief Compute the area of the bounding box
         * @return Area (width * height)
         */
        T Area() const {
            Vector2<T> d = pMax - pMin;
            return d.x * d.y;
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
            Vector2<T> diag = Diagonal();
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
        Point2<T> operator[](int i) const {
            // DCHECK(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }

        /**
         * @brief Indexed access to corners (mutable)
         * @param i 0 for pMin, 1 for pMax
         * @return Reference to the corner point
         */
        Point2<T>& operator[](int i) {
            // DCHECK(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }

        /**
         * @brief Get a specific corner of the bounding box (for 2D: 4 corners)
         * @param corner Corner index (0-3)
         * @return Corner point
         */
        Point2<T> Corner(int corner) const {
            // DCHECK(corner >= 0 && corner < 4);
            return Point2<T>((*this)[(corner & 1)].x,
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
        Point2<T> Lerp2(Point2f t) const {
            return Point2<T>((1 - t.x) * pMin.x + t.x * pMax.x,
                             (1 - t.y) * pMin.y + t.y * pMax.y);
        }

        /**
         * @brief Get normalized offset of a point within the bounding box
         * @param p Point inside the box
         * @return Offset vector with components in [0,1] range
         */
        Vector2<T> Offset(Point2<T> p) const {
            Vector2<T> o = p - pMin;
            if (pMax.x > pMin.x)
                o.x /= pMax.x - pMin.x;
            if (pMax.y > pMin.y)
                o.y /= pMax.y - pMin.y;
            return o;
        }

        /**
         * @brief Compute bounding sphere (circle) that contains the box
         * @param c Output: Center of the sphere
         * @param rad Output: Radius of the sphere
         */
        void BoundingSphere(Point2<T>* c, Float* rad) const {
            *c = (pMin + pMax) / 2;
            *rad = Inside(*c, *this) ? Distance(*c, pMax) : 0;
        }

        // ========================================================================
        // Comparison Operators
        // ========================================================================

        /**
         * @brief Equality comparison
         * @param b RHS bounding box
         * @return true if both pMin and pMax are equal
         */
        bool operator==(const Bounds2<T>& b) const {
            return b.pMin == pMin && b.pMax == pMax;
        }

        /**
         * @brief Inequality comparison
         * @param b RHS bounding box
         * @return true if pMin or pMax differ
         */
        bool operator!=(const Bounds2<T>& b) const {
            return b.pMin != pMin || b.pMax != pMax;
        }

        // ========================================================================
        // Public Members
        // ========================================================================

        Point2<T> pMin;  ///< Minimum corner (smallest x,y)
        Point2<T> pMax;  ///< Maximum corner (largest x,y)
    };

    // ========================================================================
    // Free Functions
    // ========================================================================

    /**
     * @brief Test if a point is inside a bounding box (inclusive)
     * @param pt Point to test
     * @param b Bounding box
     * @return true if point is within [pMin, pMax] inclusive
     */
    template <typename T>
    inline bool Inside(Point2<T> pt, const Bounds2<T>& b) {
        return (pt.x >= b.pMin.x && pt.x <= b.pMax.x &&
                pt.y >= b.pMin.y && pt.y <= b.pMax.y);
    }

    /**
     * @brief Test if bounding box a is completely inside bounding box b
     * @param ba Inner bounding box
     * @param bb Outer bounding box
     * @return true if ba is fully contained within bb
     */
    template <typename T>
    inline bool Inside(const Bounds2<T>& ba, const Bounds2<T>& bb) {
        return (ba.pMin.x >= bb.pMin.x && ba.pMax.x <= bb.pMax.x &&
                ba.pMin.y >= bb.pMin.y && ba.pMax.y <= bb.pMax.y);
    }

    /**
     * @brief Compute the union of two bounding boxes (smallest box containing both)
     * @param b1 First bounding box
     * @param b2 Second bounding box
     * @return Union bounding box
     */
    template <typename T>
    inline Bounds2<T> Union(const Bounds2<T>& b1, const Bounds2<T>& b2) {
        // Be careful to not run the two-point Bounds constructor
        Bounds2<T> ret;
        ret.pMin = Min(b1.pMin, b2.pMin);
        ret.pMax = Max(b1.pMax, b2.pMax);
        return ret;
    }

    /**
     * @brief Compute the intersection of two bounding boxes
     * @param b1 First bounding box
     * @param b2 Second bounding box
     * @return Intersection bounding box (empty if they don't overlap)
     */
    template <typename T>
    inline Bounds2<T> Intersect(const Bounds2<T>& b1, const Bounds2<T>& b2) {
        // Be careful to not run the two-point Bounds constructor
        Bounds2<T> b;
        b.pMin = Max(b1.pMin, b2.pMin);
        b.pMax = Min(b1.pMax, b2.pMax);
        return b;
    }

} // namespace GMath