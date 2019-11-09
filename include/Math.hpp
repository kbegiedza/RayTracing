#ifndef MATH_HPP_
#define MATH_HPP_

#include <functional>
#include <random>
#include "Vector3.hpp"

namespace bs
{
	template <typename T = double>
	inline T random_range(T minimum, T maximum)
	{
		static std::uniform_real_distribution<T> distribution(minimum, maximum);
		static std::mt19937 generator;
		static std::function<T()> random_generator = std::bind(distribution, generator);

		return random_generator();
	}

	inline double random()
	{
		return random_range(0.0, 1.0);
	}

	inline Vector3f random_in_shpere()
	{
		Vector3f point;
		do
		{
			point = Vector3f(random_range(-1.0, 1.0), random_range(-1.0, 1.0), random_range(-1.0, 1.0));
		} while (point.squard_magnitude() >= 1.0);

		return point;
	}

	inline Vector3f reflect(const Vector3f& vector, const Vector3f& normal)
	{
		return vector - (normal * 2 * vector.dot(normal));
	}
}

#endif // !MATH_HPP_