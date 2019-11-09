#include "Camera.hpp"

namespace bs
{
	Camera::Camera(Vector3f origin, Vector3f bottom_left, Vector3f horizontal, Vector3f vertical)
		: origin_(origin),
		bottom_left_(bottom_left),
		horizontal_(horizontal),
		vertical_(vertical)
	{
	}

	Ray Camera::get_ray(const float u, const float v) const
	{
		return bs::Ray(origin_, bottom_left_ + (horizontal_ * u) + (vertical_ * v) - origin_);
	}
}
