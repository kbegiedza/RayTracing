#include "Materials/Dielectic.hpp"

namespace rt
{
namespace materials
{
	Dielectric::Dielectric(const float& refractive_index)
		:refractive_index_(refractive_index)
	{
	}

	bool Dielectric::refract(const Vector3f& vector, const Vector3f& normal, const float& refractive_index, Vector3f& refracted) const
	{
		const Vector3f direction = vector.normalized();
		const float dt = Vector3f::dot(direction, normal);

		const float delta = 1 - refractive_index * refractive_index * (1 - dt * dt);
		if (delta > 0)
		{
			refracted = (direction - normal * dt) * refractive_index - normal * std::sqrt(delta);

			return true;
		}

		return false;
	}

	bool Dielectric::scatter(const Ray& r_in, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const
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
			ni_over_nt = refractive_index_;
			cosine = refractive_index_ * dot / r_in.direction().magnitude();
		}
		else
		{
			outward_normal = hit.normal;
			ni_over_nt = 1.0f / refractive_index_;
			cosine = -dot / r_in.direction().magnitude();
		}

		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			reflect_prob = mathf::schlick_approx(1, refractive_index_, cosine);
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
}
}