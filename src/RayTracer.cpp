#include "RayTracer.hpp"

namespace bs
{
	std::vector<Vector3f> RayTracer::render(const RenderSettings& settings, const std::vector<std::unique_ptr<Geometry>>& world)
	{
		const Camera& camera = settings.target_camera;

		std::vector<Vector3f> buffer(settings.width * settings.height);
		int buffer_index = 0;

		for (int y = settings.height - 1; y >= 0; y--)
		{
			for (int x = 0; x < settings.width; ++x)
			{
				bs::Vector3f color;

				for (int s = 0; s < settings.smooth_sampling; ++s)
				{
					float u = float(x + bs::random()) / float(settings.width);
					float v = float(y + bs::random()) / float(settings.height);

					color += cast_ray(camera.get_ray(u, v), 0, world);
				}

				color /= settings.smooth_sampling;
				buffer[buffer_index++] = bs::Vector3f(std::sqrt(color[0]), std::sqrt(color[1]), std::sqrt(color[2]));
			}
		}

		return buffer;
	}

	Vector3f RayTracer::cast_ray(const Ray& ray, int depth, const std::vector<std::unique_ptr<Geometry>>& world)
	{
		HitInfo hit;

		float current_max = std::numeric_limits<float>::max();
		const float minimum = 0.001;
		bool got_any_hit = false;
		HitInfo tempHit;

		for (int i = 0, elements = world.size(); i < elements; ++i)
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

			if (depth < 50 && hit.geometry->material().scatter(ray, hit, attenuation, scattered))
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
			float t = 0.5f * (norm_dir.y() + 1);
			return Vector3f(1.0, 1.0, 1.0) * (1 - t) + Vector3f(0.5, 0.7, 1.0) * t;
		}
	}
}