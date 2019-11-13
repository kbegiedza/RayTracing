#include "Materials/Metallic.hpp"

#include "Core/Mathf.hpp"

namespace rt
{
namespace materials
{
	using mathf::clamp01;

	Metallic::Metallic(const Vector3f& albedo_, float fuzzy)
		: albedo_(albedo_),
		fuzziness_(clamp01(fuzzy))
	{
	}

	bool Metallic::scatter(const Ray& ray, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const
	{
		const Vector3f reflected = Vector3f::reflect(ray.direction().normalized(), hit.normal);

		scattered = Ray(hit.point, reflected + random::inside_unit_sphere() * fuzziness_);
		attenuation = albedo_;

		const float scatter_factor = Vector3f::dot(scattered.direction(), hit.normal);
		return scatter_factor > 0.f;
	}
}
}