#include "Core/Random.hpp"

namespace rt
{
namespace random
{
	float real()
	{
		constexpr double minimum = 0.0;
		constexpr double maximum = 1.0;

		return static_cast<float>(range(minimum, maximum));
	}

	Vector3f unit_vector()
	{
		constexpr double minimum = -1.f;
		constexpr double maximum = 1.f;

		return Vector3f(static_cast<float>(range(minimum, maximum)),
						static_cast<float>(range(minimum, maximum)),
						static_cast<float>(range(minimum, maximum)));
	}

	Vector3f inside_unit_sphere()
	{
		Vector3f point;
		do
		{
			point = unit_vector();
		} while (point.squared_magnitude() >= 1.0f);

		return point;
	}

	Vector3f inside_unit_disk()
	{
		Vector3f point;
		do
		{
			point = unit_vector();
			point.set_z(0);
		} while (point.dot(point) >= 1.0f);

		return point;
	}
}
}