#ifndef MATH_HPP_
#define MATH_HPP_

#include <functional>
#include <random>

namespace bs
{
	template <typename T = double>
	T random(T minimum, T maximum)
	{
		static std::uniform_real_distribution<T> distribution(minimum, maximum);
		static std::mt19937 generator;
		static std::function<T()> random_generator = std::bind(distribution, generator);

		return random_generator();
	}
}

#endif // !MATH_HPP_