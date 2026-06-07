#pragma once
#include <cmath>
#include <algorithm>
#include "BasicTypes.h"
namespace GMath {
    using Float = float;
    // Tuple2 Definition
    template <template <typename> class Child, typename T>
    class Tuple2 {
    public:
        Tuple2() = default;

        Tuple2(T x, T y) : x(x), y(y) {  }


        bool HasNaN() const { return IsNaN(x) || IsNaN(y); }

        // Tuple2<T> + Child<U>
        template <typename U>
          auto operator+(Child<U> c) const->Child<decltype(T{} + U{}) > {
            return { x + c.x, y + c.y };
        }

        // Tuple2<T> + U
        template <typename U>
          auto operator+(U c) const->Child<decltype(T{} + U{}) > {
            return { x + c, y + c };
        }

        // Tuple2<T> += Child<U>
        template <typename U>
          Child<T>& operator+=(Child<U> c) {
            x += c.x;
            y += c.y;
            return static_cast<Child<T> &>(*this);
        }

        // Tuple2<T> += U
        template <typename U>
          Child<T>& operator+=(U c) {
            x += c;
            y += c;
            return static_cast<Child<T> &>(*this);
        }

        // Tuple2<T> - Child<U>
        template <typename U>
          auto operator-(Child<U> c) const->Child<decltype(T{} - U{}) > {
            return { x - c.x, y - c.y };
        }

        // Tuple2<T> - U
        template <typename U>
          auto operator-(U c) const->Child<decltype(T{} - U{}) > {
            return { x - c, y - c };
        }

        // Tuple2<T> -= Child<U>
        template <typename U>
          Child<T>& operator-=(Child<U> c) {
            x -= c.x;
            y -= c.y;
            return static_cast<Child<T> &>(*this);
        }

        // Tuple2<T> -= U
        template <typename U>
          Child<T>& operator-=(U c) {
            x -= c;
            y -= c;
            return static_cast<Child<T> &>(*this);
        }

        // Tuple2<T> * Child<U>
        template <typename U>
          auto operator*(Child<U> c) const->Child<decltype(T{} *U{}) > {
            return { x * c.x, y * c.y };
        }

        // Tuple2<T> * U
        template <typename U>
          auto operator*(U c) const->Child<decltype(T{} *U{}) > {
            return { x * c, y * c };
        }

        // Tuple2<T> *= Child<U>
        template <typename U>
          Child<T>& operator*=(Child<U> c) {
            x *= c.x;
            y *= c.y;
            return static_cast<Child<T> &>(*this);
        }

        // Tuple2<T> *= U
        template <typename U>
          Child<T>& operator*=(U c) {
            x *= c;
            y *= c;
            return static_cast<Child<T> &>(*this);
        }

        // Tuple2<T> / Child<U>
        template <typename U>
          auto operator/(Child<U> c) const->Child<decltype(T{} / U{}) > {
            return { x / c.x, y / c.y };
        }

        // Tuple2<T> / U
        template <typename U>
          auto operator/(U c) const->Child<decltype(T{} / U{}) > {
            return { x / c, y / c };
        }

        // Tuple2<T> /= Child<U>
        template <typename U>
          Child<T>& operator/=(Child<U> c) {
            x /= c.x;
            y /= c.y;
            return static_cast<Child<T> &>(*this);
        }

        // Tuple2<T> /= U
        template <typename U>
          Child<T>& operator/=(U c) {
            x = c;
            y = c;
            return static_cast<Child<T> &>(*this);
        }


        // Tuple2<T> == Child<T>

            bool operator==(Child<T> c) const { return x == c.x && y == c.y; }

        // Tuple2<T> != Child<T>

            bool operator!=(Child<T> c) const { return x != c.x || y != c.y; }

        // -Tuple2<T>

            Child<T> operator-() const { return { -x, -y }; }

        // Tuple2<T>[]

            T operator[](int i) const {
            return (i == 0) ? x : y;
        }

        // Tuple2<T>[]

            T& operator[](int i) {
            return (i == 0) ? x : y;
        }

        // Tuple2 Public Members
        T x{}, y{};
    };
#if 0
    // U + Tuple2<C, T>
    template <template <class> class C, typename T, typename U>
      inline auto operator+(U s, Tuple2<C, T> t)->C<decltype(T{} *U{}) > {
        return t + s;
    }

    // U - Tuple2<C, T>
    template <template <class> class C, typename T, typename U>
      inline auto operator-(U s, Tuple2<C, T> t)->C<decltype(T{} *U{}) > {
        return t + s;
    }

    // U * Tuple2<C, T>
    template <template <class> class C, typename T, typename U>
      inline auto operator*(U s, Tuple2<C, T> t)->C<decltype(T{} *U{}) > {
        return t * s;
    }

    // U / Tuple2<C, T>
    template <template <class> class C, typename T, typename U>
      inline auto operator/(U s, Tuple2<C, T> t)->C<decltype(T{} *U{}) > {
        return t / s;
    }
#endif
    template <template <class> class C, typename T>
      inline auto LengthSquared(Tuple2<C, T> n) {
        return Sqr(n.x) + Sqr(n.y);
    }

    template <template <class> class C, typename T>
      inline auto Length(Tuple2<C, T> v) {
        using std::sqrt;
        return sqrt(LengthSquared(v));
    }

    template <template <class> class C, typename T>
      inline auto Normalize(Tuple2<C, T> v) {
        return v / Length(v);
    }

    template <template <class> class C, typename T>
      inline C<T> FMA(Float a, Tuple2<C, T> b, Tuple2<C, T> c) {
        return { FMA(a, b.x, c.x), FMA(a, b.y, c.y) };
    }

    template <template <class> class C, typename T>
      inline C<T> FMA(Tuple2<C, T> a, Float b, Tuple2<C, T> c) {
        return FMA(b, a, c);
    }

    template <template <class> class C, typename T>
      inline C<T> Abs(Tuple2<C, T> t) {
        using std::abs;
        return { abs(t.x), abs(t.y) };
    }

    template <template <class> class C, typename T>
      inline C<T> Min(Tuple2<C, T> t1, Tuple2<C, T> t2) {
        using std::min;
        return { min(t1.x, t2.x), min(t1.y, t2.y) };
    }

    template <template <class> class C, typename T>
      inline C<T> Max(Tuple2<C, T> t1, Tuple2<C, T> t2) {
        using std::max;
        return { max(t1.x, t2.x), max(t1.y, t2.y) };
    }

    template <template <class> class C, typename T>
      inline T MinComponentValue(Tuple2<C, T> t) {
        using std::min;
        return min({ t.x, t.y });
    }

    template <template <class> class C, typename T>
      inline int MinComponentIndex(Tuple2<C, T> t) {
        return (t.x < t.y) ? 0 : 1;
    }

    template <template <class> class C, typename T>
      inline T MaxComponentValue(Tuple2<C, T> t) {
        using std::max;
        return max({ t.x, t.y });
    }

    template <template <class> class C, typename T>
      inline int MaxComponentIndex(Tuple2<C, T> t) {
        return (t.x < t.y) ? 1 : 0;
    }
}