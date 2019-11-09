#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Ray.hpp"

namespace bs
{
	class Camera
	{
	public:
		Camera(Vector3f origin, Vector3f bottom_left, Vector3f horizontal, Vector3f vertical);

		Ray get_ray(const float u, const float v) const;

		Vector3f origin_;
		Vector3f bottom_left_;
		Vector3f horizontal_;
		Vector3f vertical_;
	};
}

#endif // !CAMERA_HPP_