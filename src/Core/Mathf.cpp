#include "Core/Mathf.hpp"

namespace rt
{
namespace mathf
{
	float clamp(const float& value, const float& min, const float& max)
	{
		if (value >= max)
		{
			return max;
		}
		
		if (value < min)
		{
			return min;
		}

		return value;
	}

	float clamp01(const float& value)
	{
		const int minimum = 0;
		const int maximum = 1;

		return clamp(value, minimum, maximum);
	}

	float schlick_approx(const float& n1, const float& n2, const float& cosine)
	{
		constexpr int power = 5;
		constexpr float one = 1.f;

		float r0 = (n1 - n2) / (n1 + n2);
		r0 *= r0;

		return r0 + (one - r0) * pow((one - cosine), power);
	}
}
}