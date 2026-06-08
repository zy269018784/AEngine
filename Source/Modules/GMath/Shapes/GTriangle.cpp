#include <Shapes/GTriangle.h>
#include <Types/GTypes.h>
#include <Math.h>
namespace GMath
{
    GTriangle:: GTriangle(GAbstractShape *Parent) : GAbstractShape(Parent)
    {

    }

    GTriangle::GTriangle(const GPoint3f* p0,  const GPoint3f* p1,  const GPoint3f* p2,
                         const GPoint2f* uv0, const GPoint2f* uv1, const GPoint2f* uv2,
                         GAbstractShape *Parent)
        : GAbstractShape(Parent), p0(*p0), p1(*p1), p2(*p2) , uv0(GPoint2f(0, 0)), uv1(GPoint2f(1, 0)), uv2(GPoint2f(1, 1))
    {
        if (uv0)
            this->uv0 = *uv0;

        if (uv1)
            this->uv1 = *uv1;

        if (uv2)
            this->uv2 = *uv2;

        this->dp02 = this->p0 - this->p2;
        this->dp12 = this->p1 - this->p2;
        // 着色法线 = 几何法线
        this->s_n = this->g_n = GNormal3f(Normalize(Cross(dp02, dp12)));

        std::cout << "dp02 = (" << dp02.x << ", " << dp02.y << ", " << dp02.z << ")" << std::endl;
        std::cout << "dp12 = (" << dp12.x << ", " << dp12.y << ", " << dp12.z << ")" << std::endl;

        std::cout << "g_n = (" << g_n.x << ", " << g_n.y << ", " << g_n.z << ")" << std::endl;
        std::cout << "s_n = (" << s_n.x << ", " << s_n.y << ", " << s_n.z << ")" << std::endl;

        std::cout << "uv0 = (" << this->uv0.x << ", " << this->uv0.y << ")" << std::endl;
        std::cout << "uv1 = (" << this->uv1.x << ", " << this->uv1.y << ")" << std::endl;
        std::cout << "uv2 = (" << this->uv2.x << ", " << this->uv2.y << ")" << std::endl;
    }

    GTriangle::~ GTriangle()
    {

    }

    GBounds3f GTriangle::Bounds() const
    {
        return Union(GBounds3f(p0, p1), p2);
    }

    GOptional<GShapeIntersection> GTriangle::Intersect(const GRay& ray, Float tMax) const
    {
        GVector3f dp02 = p0 - p2, dp12 = p1 - p2;
        GPoint2f uv0 = GPoint2f(0, 0), uv1 = GPoint2f(1, 0), uv2 = GPoint2f(1, 1);
        // 打印 dp02
        std::cout << "dp02 = (" << dp02.x << ", " << dp02.y << ", " << dp02.z << ")" << std::endl;

        // 打印 dp12
        std::cout << "dp12 = (" << dp12.x << ", " << dp12.y << ", " << dp12.z << ")" << std::endl;
        return {};
    }
}