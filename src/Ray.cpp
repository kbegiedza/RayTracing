#include "Ray.hpp"

namespace bs
{
	Ray::Ray()
	{
	}

	Ray::Ray(const Vector3f& origin, const Vector3f& direction)
		: origin_(origin),
		direction_(direction)
	{
	}

	Vector3f Ray::origin() const
	{
		return origin_;
	}

	Vector3f Ray::direction() const
	{
		return direction_;
	}

	Vector3f Ray::travelse(const float time) const
	{
		return origin_ + (direction_ * time);
	}
}