#include <cmath>
#include "Geometry/Sphere.hpp"

namespace rt
{
namespace geometry
{
	Sphere::Sphere(Vector3f center, float radius, const Material& material)
		: Geometry(material),
		center_(center),
		radius_(radius)
	{
	}

	bool Sphere::hit(const Ray& ray, const float& min_translation, const float& max_translation, HitInfo& hit) const
	{
		static auto calculate_valid_hit = [&](const float& translation)
		{
			if (mathf::is_between(translation, min_translation, max_translation))
			{
				hit.translation = translation;
				hit.point = ray.travel(translation);
				hit.normal = (hit.point - center_) / radius_;
				hit.geometry = this;

				return true;
			}
		};

		Vector3f ray_to_center = ray.origin() - center_;
		Vector3f ray_dir = ray.direction();

		float a = ray_dir.dot(ray_dir);
		float b = ray_dir.dot(ray_to_center);
		float c = ray_to_center.dot(ray_to_center) - (radius_ * radius_);

		float delta = b * b - a * c;

		if (delta == 0.f)
		{
			float root = -b / a;

			return calculate_valid_hit(root);
		}
		else if (delta > 0.f)
		{
			float sqrt_delta = std::sqrt(delta);

			float first_root = (-b - sqrt_delta) / a;
			float second_root = (-b + sqrt_delta) / a;

			return calculate_valid_hit(first_root)
				|| calculate_valid_hit(second_root);
		}

		return false;
	}

	bool Sphere::calculate_valid_hit(const float& translation, const float& min_translation, const float& max_translation, const rt::Ray& ray, rt::HitInfo& hit) const
	{
		if (mathf::is_between(translation, min_translation, max_translation))
		{
			hit.translation = translation;
			hit.point = ray.travel(translation);
			hit.normal = (hit.point - center_) / radius_;
			hit.geometry = this;

			return true;
		}

		return false;
	}
}
}