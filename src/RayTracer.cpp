#include "RayTracer.hpp"
#include <iostream>

namespace rt
{
	using geometry::Geometry;

	RayTracer::RayTracer(const RenderSettings& render_settings, const std::vector<std::unique_ptr<Geometry>>& world)
		: world_(world),
		settings_(render_settings),
		camera_ (render_settings.target_camera),
		skybox_top_(Vector3f(0.5f, 0.7f, 1.0f)),
		skybox_bottom_(Vector3f(1.f, 1.f, 1.f))
	{
	}

	std::vector<Color> RayTracer::render() const
	{
		std::vector<Color> buffer;

		render(buffer);

		return buffer;
	}

	void RayTracer::render(std::vector<Color>& buffer) const
	{
		const size_t required_size = settings_.width * settings_.height;

		if (buffer.capacity() < required_size)
		{
			buffer.resize(required_size);
		}

		size_t buffer_index = 0;
		for (int y = (int)settings_.height - 1; y >= 0; --y)
		{
			for (size_t x = 0; x < settings_.width; ++x)
			{
				Vector3f color_sum = Vector3f();

				for (int sample = 0; sample < settings_.smooth_sampling; ++sample)
				{
					float u = (x + random::real()) / static_cast<float>(settings_.width);
					float v = (y + random::real()) / static_cast<float>(settings_.height);

					color_sum += cast_ray(camera_.construct_ray(u, v), 0);
				}

				color_sum /= static_cast<float>(settings_.smooth_sampling);

				buffer[buffer_index++] = Color::correct_gamma(color_sum);
			}
		}
	}

	Vector3f RayTracer::cast_ray(const Ray& ray, const size_t& depth) const
	{
		HitInfo hit;

		if (find_closest_hit(ray, hit))
		{
			return calculate_hit_color(ray, hit, depth);
		}
		else
		{
			return skybox_fallback(ray);
		}
	}

	bool RayTracer::find_closest_hit(const rt::Ray& ray, rt::HitInfo& hit) const
	{
		bool got_any_hit = false;
		float current_max = std::numeric_limits<float>::max();

		HitInfo temp_hit;
		for (size_t i = 0, elements = world_.size(); i < elements; ++i)
		{
			if ((world_[i])->hit(ray, clip_minimum_, current_max, temp_hit))
			{
				got_any_hit = true;
				current_max = temp_hit.translation;
				hit = temp_hit;
			}
		}

		return got_any_hit;
	}

	Vector3f RayTracer::calculate_hit_color(const rt::Ray& ray, rt::HitInfo& hit, const size_t& depth) const
	{
		Ray scattered;
		Vector3f attenuation;

		if (depth < settings_.max_depth
			&& hit.geometry != nullptr
			&& hit.geometry->material().scatter(ray, hit, attenuation, scattered))
		{
			return attenuation.hadamard(cast_ray(scattered, depth + 1));
		}
		else
		{
			return Vector3f();
		}
	}

	Vector3f RayTracer::skybox_fallback(const Ray& ray) const
	{
		const Vector3f norm_dir = ray.direction().normalized();
		const float t = 0.5f * (norm_dir.y() + 1.f);

		return Vector3f::lerp(skybox_bottom_, skybox_top_, t);
	}
}