#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Ray.hpp"

namespace rt
{
	class Camera
	{
	public:
		struct Orientation
		{
			Orientation(const Vector3f& origin, const Vector3f& lookat, const Vector3f& world_up);

			const Vector3f origin;
			const Vector3f lookat;
			const Vector3f world_up;
		};

		struct ViewSettings
		{
			ViewSettings(const float& fov, const float& aspect, const float& aperture, const float& focus_dist);

			const float fov;
			const float aspect;
			const float aperture;
			const float focus_dist;
		};

	public:
		Camera(const Orientation& orientation, const ViewSettings& settings);

		Ray construct_ray(const float& x, const float& y) const;

	private:
		Vector3f origin_;
		Vector3f bottom_left_;
		Vector3f horizontal_;
		Vector3f vertical_;

		Vector3f u_;
		Vector3f v_;
		Vector3f w_;

		float lens_rad_;
	};
}

#endif // !CAMERA_HPP_