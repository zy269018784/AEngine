#pragma once
#include "GCore/GExport.h"
#include <GMath/Types/GTypes.h>
#include <GMath/Float.h>
void GEXPORT HelloMath();
namespace GMath
{
    // ========================================================================
    // GBounds2 Union Functions
    // ========================================================================

    /**
     * @brief Compute the union of a bounding box and a point
     * @tparam T Component type
     * @param b Input bounding box
     * @param p Input point
     * @return Smallest bounding box containing both b and p
     */
    template <typename T>
    inline GBounds2<T> Union(const GBounds2<T>& b, GPoint2<T> p) {
        GBounds2<T> ret;
        ret.pMin = Min(b.pMin, p);
        ret.pMax = Max(b.pMax, p);
        return ret;
    }

    /**
     * @brief Compute the union of two bounding boxes
     * @tparam T Component type
     * @param b1 First bounding box
     * @param b2 Second bounding box
     * @return Smallest bounding box containing both b1 and b2
     */
    template <typename T>
    inline GBounds2<T> Union(const GBounds2<T>& b1, const GBounds2<T>& b2) {
        GBounds2<T> ret;
        ret.pMin = Min(b1.pMin, b2.pMin);
        ret.pMax = Max(b1.pMax, b2.pMax);
        return ret;
    }

    /**
     * @brief Test if a point is inside a bounding box (inclusive)
     * @param pt Point to test
     * @param b Bounding box
     * @return true if point is within [pMin, pMax] inclusive
     */
    template <typename T>
    inline bool Inside(GPoint2<T> pt, const GBounds2<T>& b) {
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
    inline bool Inside(const GBounds2<T>& ba, const GBounds2<T>& bb) {
        return (ba.pMin.x >= bb.pMin.x && ba.pMax.x <= bb.pMax.x &&
                ba.pMin.y >= bb.pMin.y && ba.pMax.y <= bb.pMax.y);
    }

    /**
     * @brief Compute the intersection of two bounding boxes
     * @param b1 First bounding box
     * @param b2 Second bounding box
     * @return Intersection bounding box (empty if they don't overlap)
     */
    template <typename T>
    inline GBounds2<T> Intersect(const GBounds2<T>& b1, const GBounds2<T>& b2) {
        // Be careful to not run the two-point Bounds constructor
        GBounds2<T> b;
        b.pMin = Max(b1.pMin, b2.pMin);
        b.pMax = Min(b1.pMax, b2.pMax);
        return b;
    }

    /**
 * @brief Compute squared minimum distance from a point to a bounding box
 * @tparam T Point component type
 * @tparam U Bounds component type
 * @param p Input point
 * @param b Input bounding box
 * @return Squared distance (0 if point is inside the box)
 */
    template <typename T, typename U>
    inline auto DistanceSquared(GPoint2<T> p, const GBounds2<U>& b) {
        using TDist = decltype(T{} - U{});
        TDist dx = std::max<TDist>({0, b.pMin.x - p.x, p.x - b.pMax.x});
        TDist dy = std::max<TDist>({0, b.pMin.y - p.y, p.y - b.pMax.y});
        return Sqr(dx) + Sqr(dy);
    }

    /**
     * @brief Compute minimum distance from a point to a bounding box
     * @tparam T Point component type
     * @tparam U Bounds component type
     * @param p Input point
     * @param b Input bounding box
     * @return Distance (0 if point is inside the box)
     */
    template <typename T, typename U>
    inline auto Distance(GPoint2<T> p, const GBounds2<U>& b) {
        auto dist2 = DistanceSquared(p, b);
        return std::sqrt(dist2);
    }

    // ========================================================================
    // GBounds3 Union Functions
    // ========================================================================

    /**
     * @brief Compute the union of a bounding box and a point
     * @tparam T Component type
     * @param b Input bounding box
     * @param p Input point
     * @return Smallest bounding box containing both b and p
     */
    template <typename T>
    inline GBounds3<T> Union(const GBounds3<T>& b, GPoint3<T> p) {
        GBounds3<T> ret;
        ret.pMin = Min(b.pMin, p);
        ret.pMax = Max(b.pMax, p);
        return ret;
    }

    /**
     * @brief Compute the union of two bounding boxes
     * @tparam T Component type
     * @param b1 First bounding box
     * @param b2 Second bounding box
     * @return Smallest bounding box containing both b1 and b2
     */
    template <typename T>
    inline GBounds3<T> Union(const GBounds3<T>& b1, const GBounds3<T>& b2) {
        GBounds3<T> ret;
        ret.pMin = Min(b1.pMin, b2.pMin);
        ret.pMax = Max(b1.pMax, b2.pMax);
        return ret;
    }

    /**
     * @brief Test if a point is inside a bounding box (inclusive)
     * @param pt Point to test
     * @param b Bounding box
     * @return true if point is within [pMin, pMax] inclusive
     */
    template <typename T>
    inline bool Inside(GPoint3<T> pt, const GBounds3<T>& b) {
        return (pt.x >= b.pMin.x && pt.x <= b.pMax.x &&
                pt.y >= b.pMin.y && pt.y <= b.pMax.y &&
                pt.z >= b.pMin.z && pt.z <= b.pMax.z);
    }

    /**
     * @brief Test if bounding box a is completely inside bounding box b
     * @param ba Inner bounding box
     * @param bb Outer bounding box
     * @return true if ba is fully contained within bb
     */
    template <typename T>
    inline bool Inside(const GBounds3<T>& ba, const GBounds3<T>& bb) {
        return (ba.pMin.x >= bb.pMin.x && ba.pMax.x <= bb.pMax.x &&
                ba.pMin.y >= bb.pMin.y && ba.pMax.y <= bb.pMax.y &&
                ba.pMin.z >= bb.pMin.z && ba.pMax.z <= bb.pMax.z);
    }

    /**
     * @brief Compute the intersection of two bounding boxes
     * @param b1 First bounding box
     * @param b2 Second bounding box
     * @return Intersection bounding box (empty if they don't overlap)
     */
    template <typename T>
    inline GBounds3<T> Intersect(const GBounds3<T>& b1, const GBounds3<T>& b2) {
        // Be careful to not run the two-point Bounds constructor
        GBounds3<T> b;
        b.pMin = Max(b1.pMin, b2.pMin);
        b.pMax = Min(b1.pMax, b2.pMax);
        return b;
    }

    /**
 * @brief Compute squared minimum distance from a point to a bounding box
 * @tparam T Point component type
 * @tparam U Bounds component type
 * @param p Input point
 * @param b Input bounding box
 * @return Squared distance (0 if point is inside the box)
 */
    template <typename T, typename U>
    inline auto DistanceSquared(GPoint3<T> p, const GBounds3<U>& b) {
        using TDist = decltype(T{} - U{});
        TDist dx = std::max<TDist>({0, b.pMin.x - p.x, p.x - b.pMax.x});
        TDist dy = std::max<TDist>({0, b.pMin.y - p.y, p.y - b.pMax.y});
        TDist dz = std::max<TDist>({0, b.pMin.z - p.z, p.z - b.pMax.z});
        return Sqr(dx) + Sqr(dy) + Sqr(dz);
    }

    /**
     * @brief Compute minimum distance from a point to a bounding box
     * @tparam T Point component type
     * @tparam U Bounds component type
     * @param p Input point
     * @param b Input bounding box
     * @return Distance (0 if point is inside the box)
     */
    template <typename T, typename U>
    inline auto Distance(GPoint3<T> p, const GBounds3<U>& b) {
        auto dist2 = DistanceSquared(p, b);
        return std::sqrt(dist2);
    }
    
    //
    
    template <typename Float, typename C>
    inline constexpr Float EvaluatePolynomial(Float t, C c) {
        return c;
    }
    

    template <typename Float, typename C, typename... Args>
        inline constexpr Float EvaluatePolynomial(Float t, C c, Args... cRemaining) {
        return FMA(t, EvaluatePolynomial(t, cRemaining...), c);
    }
    
    template <typename Ta, typename Tb, typename Tc, typename Td>
    inline auto DifferenceOfProducts(Ta a, Tb b, Tc c, Td d) {
        auto cd = c * d;
        auto differenceOfProducts = FMA(a, b, -cd);
        auto error = FMA(-c, d, cd);
        return differenceOfProducts + error;
    }

    inline  GVector3f Cross(GVector3f v, GVector3f w)
    {
        return {
        DifferenceOfProducts(v.y, w.z, v.z, w.y),
        DifferenceOfProducts(v.z, w.x, v.x, w.z),
        DifferenceOfProducts(v.x, w.y, v.y, w.x)
        };
    }

    template <typename T>
       inline GVector3<T> Cross(GVector3<T> v, GVector3<T> w) {
        return { DifferenceOfProducts(v.y, w.z, v.z, w.y),
                DifferenceOfProducts(v.z, w.x, v.x, w.z),
                DifferenceOfProducts(v.x, w.y, v.y, w.x) };
    }
}