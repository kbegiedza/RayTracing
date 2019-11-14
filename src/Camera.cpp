#include "Camera.hpp"
#include "Core/Mathf.hpp"
#include "Core/Random.hpp"

namespace rt
{
	Camera::Orientation::Orientation(const Vector3f& origin, const Vector3f& lookat, const Vector3f& world_up)
		: origin(origin),
		lookat(lookat),
		world_up(world_up)
	{
	}

	Camera::ViewSettings::ViewSettings(const float& fov, const float& aspect, const float& aperture, const float& focus_dist)
		: fov(fov),
		aspect(aspect),
		aperture(aperture),
		focus_dist(focus_dist)
	{
	}

	Camera::Camera(const Orientation& orientation, const ViewSettings& settings)
		: lens_rad_(settings.aperture / 2.f),
		origin_(orientation.origin)
	{
		const float angle = settings.fov * mathf::PI / 180.f;
		const float half_height = std::tan(angle / 2);
		const float half_width = half_height * settings.aspect;

		w_ = (origin_- orientation.lookat).normalized();
		u_ = Vector3f::cross(orientation.world_up, w_);
		v_ = Vector3f::cross(w_, u_);

		const Vector3f focused_horizontal_half = u_ * half_width * settings.focus_dist;
		const Vector3f focused_verical_half = v_ * half_height * settings.focus_dist;
		const Vector3f focused_w = w_ * settings.focus_dist;

		bottom_left_ = origin_ - focused_horizontal_half - focused_verical_half - focused_w;
		horizontal_ = 2.f * focused_horizontal_half;
		vertical_ = 2.f * focused_verical_half;
	}

	Ray Camera::construct_ray(const float& x, const float& y) const
	{
		const Vector3f random_disk = lens_rad_ * random::inside_unit_disk();
		const Vector3f random_offset = u_ * random_disk.x() + v_ * random_disk.y();
		const Vector3f new_origin = origin_ + random_offset;

		return rt::Ray(new_origin, bottom_left_ + (horizontal_ * x) + (vertical_ * y) - new_origin);
	}
}