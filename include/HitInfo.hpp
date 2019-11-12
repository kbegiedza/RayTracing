#ifndef HIT_INFO_HPP_
#define HIT_INFO_HPP_

#include "Core/Vector3.hpp"

namespace rt
{
	namespace geometry
	{
		class Geometry;
	}

	struct HitInfo
	{
		Vector3f point;
		Vector3f normal;
		const geometry::Geometry* geometry = nullptr;
		float translation = nanf("");
	};
}

#endif // !HITINFO_HPP_