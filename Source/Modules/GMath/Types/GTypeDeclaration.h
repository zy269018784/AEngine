#pragma once
#include <Types/BasicTypes.h>

namespace GMath
{
	template <typename T>
	class GVector2;
	template <typename T>
	class GVector3;
	template <typename T>
	class GPoint2;
	template <typename T>
	class GPoint3;
	template <typename T>
	class GBounds2;
	template <typename T>
	class GBounds3;
	template <typename T>
	class GNormal2;
	template <typename T>
	class GNormal3;
	using GPoint2f  = GPoint2<Float>;
	using GPoint2i  = GPoint2<int>;
	using GPoint2u  = GPoint2<unsigned int>;
	using GPoint3f  = GPoint3<Float>;
	using GPoint3i  = GPoint3<int>;
	using GPoint3u  = GPoint3<unsigned int>;
	using GVector2f = GVector2<Float>;
	using GVector2i = GVector2<int>;
	using GVector3f = GVector3<Float>;
	using GVector3i = GVector3<int>;
	using GVector3u = GVector3<unsigned int>;
	using GBounds2f = GBounds2<Float>;
	using GBounds2i = GBounds2<int>;
	using GBounds3f = GBounds3<Float>;
	using GBounds3i = GBounds3<int>;
	using GNormal2f = GNormal2<Float>;
	using GNormal2i = GNormal2<int>;
	using GNormal3f = GNormal3<Float>;
	using GNormal3i = GNormal3<int>;

	#define Pi		3.14159265358979323846f
	#define InvPi	0.31830988618379067154f
	#define Inv2Pi	0.15915494309189533577f
	#define Inv4Pi	0.07957747154594766788f
	#define PiOver2 1.57079632679489661923f
	#define PiOver4 0.78539816339744830961f
	#define Sqrt2	1.41421356237309504880f
	#define Infinity std::numeric_limits<Float>::infinity()
}