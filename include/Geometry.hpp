#ifndef IHITTABLE_HPP_
#define IHITTABLE_HPP_

#include <memory>

#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Material.hpp"

namespace bs
{
	class Geometry
	{
	public:
		Geometry(std::shared_ptr<Material> material);

		virtual bool hit(const Ray& r, float t_min, float t_max, bs::hit_info& hit) const = 0;
	public:
		std::shared_ptr<Material> material_;
	};
}

#endif // !IHITTABLE_HPP_