#ifndef IHITTABLE_HPP_
#define IHITTABLE_HPP_

#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Material.hpp"

namespace bs
{
	class IHittable
	{
	public:
		virtual ~IHittable() {}
		virtual bool hit(const Ray& r, float t_min, float t_max, bs::hit_info& hit) const = 0;
	};

	class HittableObject : public IHittable
	{
	public:
		HittableObject(Material* material)
			: material(material)
		{
		}

		virtual ~HittableObject()
		{
			material = nullptr;
		}

	public:
		Material* material;
	};
}

#endif // !IHITTABLE_HPP_