#include "Materials/Dielectic.hpp"

namespace rt
{
namespace materials
{
	Dielectric::Dielectric(const float& refractive_index)
		: refractive_index_(refractive_index),
		albedo_(Vector3f(1.f, 1.f, 1.f))
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
		const Vector3f direction = r_in.direction();
		const refract_data data = calculate_refract_data(direction, hit.normal);

		Vector3f scatter_direction;
		const bool use_refraction = mathf::schlick_approx(1, refractive_index_, data.cosine) < random::real()
								&& refract(r_in.direction(), data.normal, data.index, scatter_direction);

		if (!use_refraction)
		{
			scatter_direction = Vector3f::reflect(direction, hit.normal);
		}

		attenuation = albedo_;
		scattered = Ray(hit.point, scatter_direction);

		return true;
	}

	Dielectric::refract_data Dielectric::calculate_refract_data(Vector3f direction, Vector3f normal) const
	{
		const float dot = Vector3f::dot(direction, normal);
		const float cosine = dot / direction.magnitude();

		if (dot > 0)
		{
			return refract_data
			{
				-normal,
				refractive_index_,
				refractive_index_ * cosine
			};
		}

		return refract_data
		{
			normal,
			1.f / refractive_index_,
			-cosine
		};
	}
}
}