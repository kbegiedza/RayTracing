#ifndef METALLIC_HPP_
#define METALLIC_HPP_

#include "Materials/Material.hpp"

namespace rt
{
namespace materials
{
	class Metallic : public Material
	{
	public:
		Metallic(const Vector3f& albedo, float fuzzy = 0)
			: albedo(albedo)
		{
			fuzziness = fuzzy > 1 ? 1 : fuzzy;
		}

		inline virtual bool scatter(const Ray& ray, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const
		{
			auto reflected = Vector3f::reflect(ray.direction().normalized(), hit.normal);

			scattered = Ray(hit.point, reflected + random::inside_unit_sphere() * fuzziness);
			attenuation = albedo;

			return (scattered.direction().dot(hit.normal) > 0);
		}

	public:
		Vector3f albedo;
		float fuzziness;
	};
}
}
#endif // !METALLIC_HPP_