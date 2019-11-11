#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "Geometry.hpp"

namespace bs
{
	class Sphere : public Geometry
	{
	public:
		Sphere(std::shared_ptr<Material> material);
		Sphere(Vector3f center, float radius, std::shared_ptr<Material> material);

		virtual bool hit(const Ray& ray, const float& min_translation, const float& max_translation, HitInfo& hit) const override;

	public:
		Vector3f center_;
		float radius_;
	};
}

#endif // !SPHERE_HPP_