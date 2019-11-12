#include "Camera.hpp"
#include "Core/Mathf.hpp"
#include "Core/Random.hpp"

namespace rt
{
	Camera::Camera(Vector3f lookfrom, Vector3f lookat, Vector3f world_up, const float fov_v, const float aspect, const float aperture, const float focus_dist)
	{
		lens_rad_ = aperture / 2.f;

		float theta = fov_v * mathf::PI / 180.f;
		float half_height = std::tan(theta / 2);
		float half_width = half_height * aspect;

		origin_ = lookfrom;

		w_ = (lookfrom - lookat).normalized();
		u_ = (world_up.cross(w_));
		v_ = w_.cross(u_);

		bottom_left_ = origin_ - u_ * half_width * focus_dist - v_ * half_height * focus_dist - w_ * focus_dist;
		horizontal_ = u_ * 2 * half_width * focus_dist;
		vertical_ = v_ * 2 * half_height * focus_dist;
	}

	Ray Camera::get_ray(const float u, const float v) const
	{
		Vector3f rd = lens_rad_ * random::inside_unit_disk();
		Vector3f offset = u_ * rd.x() + v_ * rd.y();

		return rt::Ray(origin_ + offset, bottom_left_ + (horizontal_ * u) + (vertical_ * v) - origin_ - offset);
	}
}
