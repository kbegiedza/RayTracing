#include "Materials/Lambertian.hpp"

namespace rt
{
namespace materials
{
	Lambertian::Lambertian(const Vector3f& albedo)
		: albedo_(albedo)
	{
	}

	bool Lambertian::scatter(const Ray& ray, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const
	{
		const Vector3f target = hit.point + hit.normal + random::inside_unit_sphere();

		scattered = Ray(hit.point, target - hit.point);
		attenuation = albedo_;

		return true;
	}
}
}