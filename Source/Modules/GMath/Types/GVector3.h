#pragma once
#include <GMath/Types/GTuple3.h>

namespace GMath {
    // GVector3 Definition
    template <typename T>
    class GVector3 : public GTuple3<GVector3, T> {
       public:
       // GVector3 Public Methods
       using GTuple3<GVector3, T>::x;
       using GTuple3<GVector3, T>::y;
       using GTuple3<GVector3, T>::z;

       GVector3() = default;

       GVector3(T x, T y, T z) : GTuple3<GVector3, T>(x, y, z) {}

       GVector3(T a) : GTuple3<GVector3, T>(a, a, a) {}

       template <typename U>
       explicit GVector3(GVector3<U> v) : GTuple3<GVector3, T>(T(v.x), T(v.y), T(v.z)) {}
       };
    // U + GVector3<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, GVector3<decltype(T{} + U{}) >>
           inline operator+(U u, GVector3<T> pt) { return { u + pt.x, u + pt.y, u + pt.z }; }

    // U - GVector3<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, GVector3<decltype(T{} - U{}) >>
           inline operator-(U u, GVector3<T> pt) { return { u - pt.x, u - pt.y, u - pt.z }; }

    // U * GVector3<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, GVector3<decltype(T{} *U{}) >>
           inline operator*(U u, GVector3<T> pt) { return { u * pt.x, u * pt.y, u * pt.z }; }

    // U / GVector3<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, GVector3<decltype(T{} - U{}) >>
           inline operator/(U u, GVector3<T> pt) { return { u / pt.x, u / pt.y, u / pt.z }; }
}