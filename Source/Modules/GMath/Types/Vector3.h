#pragma once
#include <Types/Tuple3.h>

namespace GMath {
    // Vector3 Definition
    template <typename T>
    class Vector3 : public Tuple3<Vector3, T> {
       public:
       // Vector3 Public Methods
       using Tuple3<Vector3, T>::x;
       using Tuple3<Vector3, T>::y;
       using Tuple3<Vector3, T>::z;

       Vector3() = default;

       Vector3(T x, T y, T z) : Tuple3<Vector3, T>(x, y, z) {}

       Vector3(T a) : Tuple3<Vector3, T>(a, a, a) {}

       template <typename U>
       explicit Vector3(Vector3<U> v) : Tuple3<Vector3, T>(T(v.x), T(v.y), T(v.z)) {}
       };
    // U + Vector3<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, Vector3<decltype(T{} + U{}) >>
           inline operator+(U u, Vector3<T> pt) { return { u + pt.x, u + pt.y, u + pt.z }; }

    // U - Vector3<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, Vector3<decltype(T{} - U{}) >>
           inline operator-(U u, Vector3<T> pt) { return { u - pt.x, u - pt.y, u - pt.z }; }

    // U * Vector3<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, Vector3<decltype(T{} *U{}) >>
           inline operator*(U u, Vector3<T> pt) { return { u * pt.x, u * pt.y, u * pt.z }; }

    // U / Vector3<T>
    template <typename U, typename T>
    std::enable_if_t < std::is_fundamental_v<U>, Vector3<decltype(T{} - U{}) >>
           inline operator/(U u, Vector3<T> pt) { return { u / pt.x, u / pt.y, u / pt.z }; }
}