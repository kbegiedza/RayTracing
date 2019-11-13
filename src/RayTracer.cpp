#include "RayTracer.hpp"
#include <iostream>

namespace rt
{
	using geometry::Geometry;

	std::vector<Color> RayTracer::render(const RenderSettings& settings, const std::vector<std::unique_ptr<Geometry>>& world)
	{
		const Camera& camera = settings.target_camera;

		std::vector<Color> buffer(settings.width * settings.height);
		int buffer_index = 0;

		Vector3f color_sum;
		for (int y = (int)settings.height - 1; y >= 0; --y)
		{
			for (size_t x = 0; x < settings.width; ++x)
			{
				color_sum = Vector3f();

				for (int s = 0; s < settings.smooth_sampling; ++s)
				{
					float u = float(x + random::real()) / float(settings.width);
					float v = float(y + random::real()) / float(settings.height);

					color_sum += cast_ray(camera.get_ray(u, v), 0, world);
				}

				color_sum /= static_cast<float>(settings.smooth_sampling);
				buffer[buffer_index++] = Color(std::sqrt(color_sum[0]), std::sqrt(color_sum[1]), std::sqrt(color_sum[2]));
			}
		}

		return buffer;
	}

	Vector3f RayTracer::cast_ray(const Ray& ray, int depth, const std::vector<std::unique_ptr<Geometry>>& world)
	{
		HitInfo hit;

		float current_max = std::numeric_limits<float>::max();
		const float minimum = 0.001f;
		bool got_any_hit = false;
		HitInfo tempHit;

		for (size_t i = 0, elements = world.size(); i < elements; ++i)
		{
			if ((world[i])->hit(ray, minimum, current_max, tempHit))
			{
				got_any_hit = true;
				current_max = tempHit.translation;
				hit = tempHit;
			}
		}

		if (got_any_hit)
		{
			Ray scattered;
			Vector3f attenuation;

			if (depth < 50
				&& hit.geometry != nullptr
				&& hit.geometry->material().scatter(ray, hit, attenuation, scattered))
			{
				return attenuation.hadamard(cast_ray(scattered, depth + 1, world));
			}
			else
			{
				return Vector3f();
			}
		}
		else
		{
			auto norm_dir = ray.direction().normalized();
			float t = 0.5f * (norm_dir.y() + 1.f);
			return Vector3f(1.0f, 1.0f, 1.0f) * (1.f - t) + Vector3f(0.5f, 0.7f, 1.0f) * t;
		}
	}
}