#pragma once
#include <Types/Tuple2.h>

namespace GMath {
    // Vector2 Definition
    template <typename T>
    class Vector2 : public Tuple2<Vector2, T> {
    public:
       // Vector2 Public Methods
       using Tuple2<Vector2, T>::x;
       using Tuple2<Vector2, T>::y;

       Vector2() = default;

       Vector2(T x, T y) : Tuple2<Vector2, T>(x, y) {}
       Vector2(T a) : Tuple2<Vector2, T>(a, a) {}

       template <typename U>
       explicit Vector2(Vector2<U> v) : Tuple2<Vector2, T>(T(v.x), T(v.y)) {}
    };
    // U + Vector2<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, Vector2<decltype(T{} + U{}) >>
           inline operator+(U u, Vector2<T> pt) { return { u + pt.x, u + pt.y}; }

    // U - Vector2<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, Vector2<decltype(T{} - U{}) >>
           inline operator-(U u, Vector2<T> pt) { return { u - pt.x, u - pt.y }; }

    // U * Vector2<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, Vector2<decltype(T{} *U{}) >>
           inline operator*(U u, Vector2<T> pt) { return { u * pt.x, u * pt.y }; }

    // U / Vector2<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, Vector2<decltype(T{} - U{}) >>
           inline operator/(U u, Vector2<T> pt) { return { u / pt.x, u / pt.y }; }

}