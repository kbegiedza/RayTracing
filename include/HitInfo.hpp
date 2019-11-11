#ifndef HIT_INFO_HPP_
#define HIT_INFO_HPP_

#include "Vector3.hpp"

namespace bs
{
	class Geometry;

	struct HitInfo
	{
		Vector3f point;
		Vector3f normal;
		const Geometry* geometry = nullptr;
		float translation = std::numeric_limits<float>().max();
	};
}

#endif // !HITINFO_HPP_