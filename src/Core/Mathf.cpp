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
}
}