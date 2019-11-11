#ifndef HIT_INFO_HPP_
#define HIT_INFO_HPP_

#include "Vector3.hpp"

namespace bs
{
	class Geometry;

	struct hit_info
	{
		Vector3f point;
		Vector3f normal;
		float t = std::nanf("");
		const Geometry* object = nullptr;
	};
}

#endif // !HITINFO_HPP_