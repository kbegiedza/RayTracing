#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "IHittable.hpp"

namespace bs
{
	class Sphere : public HittableObject
	{
	public:
		Sphere(Material* material);
		Sphere(Vector3f center, float radius, Material* material);

		virtual bool hit(const Ray& r, float t_min, float t_max, bs::hit_info& hit) const override;

	public:
		Vector3f center_;
		float radius_;
	};
}

#endif // !SPHERE_HPP_