#ifndef MATHF_HPP_
#define MATHF_HPP_

#include "Core/Vector3.hpp"

namespace rt
{
namespace mathf
{
	static constexpr float PI = 3.14159265358979f;

	float clamp(const float& value, const float& min, const float& max);
	float clamp01(const float& value);

	float lerp(const float& a, const float& b, const float t);

	float schlick_approx(const float& n1, const float& n2, const float& cosine);
	
	/**
	* checks is value between minimum (exclusive) and maximum (exclusive)
	* @returns
	*/
	template<typename T>
	bool is_between(const T& value, const T& minimum, const T& maximum)
	{
		return value > minimum 
			&& value < maximum;
	}
}
}

#endif // !MATHF_HPP_