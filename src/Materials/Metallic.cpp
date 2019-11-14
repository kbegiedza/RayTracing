#include "Materials/Metallic.hpp"

#include "Core/Mathf.hpp"

namespace rt
{
namespace materials
{
	using mathf::clamp01;

	Metallic::Metallic(const Vector3f& albedo, const float& fuzzy)
		: albedo_(albedo),
		fuzziness_(clamp01(fuzzy))
	{
	}

	bool Metallic::scatter(const Ray& ray, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const
	{
		const Vector3f normalized_direction = ray.direction().normalized();
		const Vector3f reflected = Vector3f::reflect(normalized_direction, hit.normal);

		scattered = Ray(hit.point, reflected + random::inside_unit_sphere() * fuzziness_);
		attenuation = albedo_;

		const float scatter_factor = Vector3f::dot(scattered.direction(), hit.normal);
		return scatter_factor > 0.f;
	}
}
}