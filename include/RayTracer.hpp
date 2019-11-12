#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_

#include <memory>
#include <vector>

#include "Core/Color.hpp"
#include "Materials/Material.hpp"
#include "Geometry/Geometry.hpp"
#include "RenderSettings.hpp"

namespace rt
{
	class RayTracer
	{
	public:
		static std::vector<Color> render(const RenderSettings& render_settings, const std::vector<std::unique_ptr<geometry::Geometry>>& world);
	
	private:
		static Vector3f cast_ray(const Ray& ray, int depth, const std::vector<std::unique_ptr<geometry::Geometry>>& world);
	};
}

#endif // !RAYTRACER_HPP_