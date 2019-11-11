#include <cmath>
#include "Geometry/Sphere.hpp"

namespace bs
{
	Sphere::Sphere(std::shared_ptr<Material> material)
		: Geometry(material),
		radius_(0)
	{
	}

	Sphere::Sphere(Vector3f center, float radius, std::shared_ptr<Material> material)
		: Geometry(material),
		center_(center),
		radius_(radius)
	{
	}

	bool Sphere::hit(const Ray& ray, const float& min_translation, const float& max_translation, HitInfo& hit) const
	{
		auto amc = ray.origin() - center_;

		float a = ray.direction().dot(ray.direction());
		float b = ray.direction().dot(amc);
		float c = amc.dot(amc) - (radius_ * radius_);

		float delta = b * b - a * c;
		if (delta > 0)
		{
			auto check_hit = [&](float t_in) -> bool {
				if (t_in < max_translation && t_in > min_translation)
				{
					hit.translation = t_in;
					hit.point = ray.travel(t_in);
					hit.normal = (hit.point - center_) / radius_;
					hit.geometry = this;

					return true;
				}

				return false;
			};

			float sqrtDelta = std::sqrt(delta);

			float ray_translation = (-b - sqrtDelta) / a;
			if (check_hit(ray_translation))
			{
				return true;
			}

			ray_translation = (-b + sqrtDelta) / a;
			if (check_hit(ray_translation))
			{
				return true;
			}
		}

		return false;
	}
}