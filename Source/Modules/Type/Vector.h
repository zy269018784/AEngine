template <typename T>
class Vector2
{
public:
    Vector2(T R, T G) : X(R), Y(G) {}
public:
    T X;
    T Y;
};

template <typename T>
class Vector3
{
public:
    Vector3(T R, T G, T B) : X(R), Y(G), Z(B) {}
public:
    T X;
    T Y;
    T Z;
};

template <typename T>
class Vector4
{
public:
    Vector4(T R, T G, T B, T A) : X(R), Y(G), Z(B), W(A) {}
public:
    T X;
    T Y;
    T Z;
    T W;
};

using Vector2f = Vector2<float>;
using Vector3f = Vector3<float>;
using Vector4f = Vector4<float>;

using Vector2i = Vector2<int>;
using Vector3i = Vector3<int>;
using Vector4i = Vector4<int>;

using Vector2u = Vector2<unsigned int>;
using Vector3u = Vector3<unsigned int>;
using Vector4u = Vector4<unsigned int>;
