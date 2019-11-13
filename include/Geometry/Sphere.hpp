#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "Geometry/Geometry.hpp"

namespace rt
{
namespace geometry
{
	class Sphere : public Geometry
	{
	public:
		Sphere(Vector3f center, float radius, const Material& material);

		virtual bool hit(const Ray& ray, const float& min_translation, const float& max_translation, HitInfo& hit) const override;

	private:
		bool calculate_valid_hit(const float& translation, const float& min_translation, const float& max_translation, const rt::Ray& ray, rt::HitInfo& hit) const;

	private:
		Vector3f center_;
		float radius_;
	};
}
}

#endif // !SPHERE_HPP_