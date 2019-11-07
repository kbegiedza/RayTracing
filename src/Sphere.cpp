#include <cmath>
#include "Sphere.hpp"

namespace bs
{
	Sphere::Sphere()
		: radius_(0)
	{
	}

	Sphere::Sphere(Vector3f center, float radius)
		: center_(center),
		radius_(radius)
	{
	}

	bool Sphere::hit(const Ray& r, float t_min, float t_max, bs::hit& hit) const
	{
		auto amc = r.origin() - center_;

		float a = r.direction().dot(r.direction());
		float b = r.direction().dot(amc);
		float c = amc.dot(amc) - (radius_ * radius_);

		float delta = b * b - a * c;
		if (delta > 0)
		{
			auto check_hit = [&](float t_in) -> bool {
				if (t_in < t_max && t_in > t_min)
				{
					hit.t = t_in;
					hit.point = r.travel(t_in);
					hit.normal = (hit.point - center_) / radius_;
					return true;
				}

				return false;
			};

			float sqrtDelta = std::sqrt(delta);

			float t = (-b - sqrtDelta) / a;
			if (check_hit(t))
			{
				return true;
			}

			t = (-b + sqrtDelta) / a;
			if (check_hit(t))
			{
				return true;
			}
		}

		return false;
	}
}