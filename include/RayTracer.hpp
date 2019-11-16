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
		RayTracer(const RenderSettings& render_settings, const std::vector<std::unique_ptr<geometry::Geometry>>& world);

		std::vector<Color> render() const;
		void render(std::vector<Color>& buffer) const;
	
	private:
		Vector3f cast_ray(const Ray& ray, const size_t& depth) const;
		bool find_closest_hit(const rt::Ray& ray, rt::HitInfo& hit) const;

		Vector3f calculate_hit_color(const rt::Ray& ray, rt::HitInfo& hit, const size_t& depth) const;
		Vector3f skybox_fallback(const Ray& ray) const;

	private:
		const Camera& camera_;
		const RenderSettings settings_;
		const std::vector<std::unique_ptr<geometry::Geometry>>& world_;

		const Vector3f skybox_top_;
		const Vector3f skybox_bottom_;
	};
}

#endif // !RAYTRACER_HPP_