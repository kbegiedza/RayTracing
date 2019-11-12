#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Ray.hpp"

namespace rt
{
	class Camera
	{
	public:
		Camera(Vector3f lookfrom, Vector3f lookat, Vector3f world_up, const float fov_v, const float aspect, const float aperture, const float focus_dist);

		Ray get_ray(const float u, const float v) const;

		Vector3f origin_;
		Vector3f bottom_left_;
		Vector3f horizontal_;
		Vector3f vertical_;

		Vector3f u_, v_, w_;
		float lens_rad_;
	};
}

#endif // !CAMERA_HPP_