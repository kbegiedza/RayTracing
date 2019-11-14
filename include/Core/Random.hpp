#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <functional>
#include <random>

#include "Core/Vector3.hpp"

namespace rt
{
namespace random
{
	/**
	* Returns random number with uniform distribution
	* @return random number [minimum, maximum]
	*/
	template <typename T = double>
	inline T range(const T & minimum, const T & maximum)
	{
		static const std::uniform_real_distribution<T> distribution(minimum, std::nextafter(maximum, std::numeric_limits<T>::max()));
		static const std::mt19937 generator { 5489u };
		static const std::function<T()> random_generator = std::bind(distribution, generator);

		return random_generator();
	}

	/**
	* Returns random number [0;1] with uniform distribution
	* @return real number [0;1]
	*/
	float real();

	Vector3f inside_unit_sphere();

	Vector3f inside_unit_disk();
}
}

#endif // !RANDOM_HPP_