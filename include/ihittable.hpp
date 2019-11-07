#ifndef IHITTABLE_HPP_
#define IHITTABLE_HPP_

#include "Ray.hpp"

namespace bs
{
	struct hit
	{
		float t;
		Vector3f point;
		Vector3f normal;
	};

	class IHittable
	{
	public:
		virtual bool hit(const Ray& r, float t_min, float t_max, bs::hit& hit) const = 0;
	};
}

#endif // !IHITTABLE_HPP_