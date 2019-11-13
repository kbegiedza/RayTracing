#ifndef DIELECTIC_HPP_
#define DIELECTIC_HPP_

#include "Materials/Material.hpp"

namespace rt
{
namespace materials
{
	class Dielectric : public Material
	{
	public:
		Dielectric(float ref)
			: refractive_index(ref)
		{
		}

		inline float schlick(float cosine, float refractive_index) const
		{
			float r0 = (1 - refractive_index) / (1 + refractive_index);
			r0 = r0 * r0;
			return r0 + (1 - r0) * pow((1 - cosine), 5);
		}

		inline bool refract(const Vector3f& vector, const Vector3f& normal, float ni_over_nt, Vector3f& refracted) const
		{
			Vector3f normalized_vector = vector.normalized();
			float dt = normalized_vector.dot(normal);

			float delta = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt);
			if (delta > 0)
			{
				refracted = (normalized_vector - normal * dt) * ni_over_nt - normal * std::sqrt(delta);

				return true;
			}

			return false;
		}

		virtual bool scatter(const Ray& r_in, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const
		{
			Vector3f outward_normal;
			Vector3f reflected = Vector3f::reflect(r_in.direction(), hit.normal);

			float ni_over_nt;

			attenuation = Vector3f(1, 1, 1);

			Vector3f refracted;

			float reflect_prob;
			float cosine;

			float dot = r_in.direction().dot(hit.normal);
			if (dot > 0)
			{
				outward_normal = -hit.normal;
				ni_over_nt = refractive_index;
				cosine = refractive_index * dot / r_in.direction().magnitude();
			}
			else
			{
				outward_normal = hit.normal;
				ni_over_nt = 1.0f / refractive_index;
				cosine = -dot / r_in.direction().magnitude();
			}

			if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
			{
				reflect_prob = schlick(cosine, refractive_index);
			}
			else
			{
				reflect_prob = 1.0;
			}

			if (random::real() < reflect_prob)
			{
				scattered = Ray(hit.point, reflected);
			}
			else
			{
				scattered = Ray(hit.point, refracted);
			}

			return true;
		}
	public:
		float refractive_index;
	};
}
}

#endif // !DIELECTIC_HPP_