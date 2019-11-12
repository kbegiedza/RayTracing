#ifndef MATHF_HPP_
#define MATHF_HPP_

#include "Core/Vector3.hpp"

namespace rt
{
namespace mathf
{
	constexpr float PI = 3.14159265358979f;

	float clamp(const float& value, const float& min, const float& max);
	float clamp01(const float& value);
}
}

#endif // !MATHF_HPP_