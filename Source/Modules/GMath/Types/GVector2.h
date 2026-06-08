#pragma once
#include <Types/GTuple2.h>

namespace GMath {
    // GVector2 Definition
    template <typename T>
    class GVector2 : public GTuple2<GVector2, T> {
    public:
       // GVector2 Public Methods
       using GTuple2<GVector2, T>::x;
       using GTuple2<GVector2, T>::y;

       GVector2() = default;

       GVector2(T x, T y) : GTuple2<GVector2, T>(x, y) {}
       GVector2(T a) : GTuple2<GVector2, T>(a, a) {}

       template <typename U>
       explicit GVector2(GVector2<U> v) : GTuple2<GVector2, T>(T(v.x), T(v.y)) {}
    };
    // U + GVector2<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, GVector2<decltype(T{} + U{}) >>
           inline operator+(U u, GVector2<T> pt) { return { u + pt.x, u + pt.y}; }

    // U - GVector2<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, GVector2<decltype(T{} - U{}) >>
           inline operator-(U u, GVector2<T> pt) { return { u - pt.x, u - pt.y }; }

    // U * GVector2<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, GVector2<decltype(T{} *U{}) >>
           inline operator*(U u, GVector2<T> pt) { return { u * pt.x, u * pt.y }; }

    // U / GVector2<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, GVector2<decltype(T{} - U{}) >>
           inline operator/(U u, GVector2<T> pt) { return { u / pt.x, u / pt.y }; }

}