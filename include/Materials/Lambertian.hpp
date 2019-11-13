#ifndef LAMBERTIAN_HPP_
#define LAMBERTIAN_HPP_

#include "Materials/Material.hpp"

namespace rt
{
namespace materials
{
	class Lambertian : public Material
	{
	public:
		Lambertian(const Vector3f& albedo)
			: albedo(albedo)
		{
		}

		inline virtual bool scatter(const Ray& ray, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const
		{
			auto target = hit.point + hit.normal + random::inside_unit_sphere();
			scattered = Ray(hit.point, target - hit.point);
			attenuation = albedo;

			return true;
		}

	public:
		Vector3f albedo;
	};
}
}

#endif // !LAMBERTIAN_HPP_