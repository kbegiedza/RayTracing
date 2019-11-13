#ifndef RENDERSETTINGS_HPP_
#define RENDERSETTINGS_HPP_

#include "Camera.hpp"

namespace rt
{
	struct RenderSettings
	{
		RenderSettings(const Camera& camera, const size_t& width, const size_t& height, const size_t& smooth_sampling)
			: target_camera(camera),
			width(width),
			height(height),
			smooth_sampling(smooth_sampling)
		{
		}

		const Camera& target_camera;

		const size_t width;
		const size_t height;
		const size_t smooth_sampling;
	};
}
#endif // !RENDERSETTINGS_HPP_