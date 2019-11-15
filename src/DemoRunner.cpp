#include "DemoRunner.hpp"

namespace rt
{
	using namespace rt::materials;
	using namespace rt::geometry;

	DemoRunner::DemoRunner(const Arguments& arguments, const size_t& world_elements)
		: width_(arguments.width()),
		height_(arguments.height()),
		aperture_(arguments.aperture()),
		smoothing_samples_(arguments.smoothing())
	{
		create_demo_camera();
		generate_world(world_elements);
	}

	std::vector<Color> DemoRunner::render() const
	{
		const size_t max_depth = 50;
		const rt::RenderSettings render_settings(*camera_, width_, height_, max_depth, smoothing_samples_);

		rt::RayTracer ray_tracer(render_settings, world_);

		return ray_tracer.render();
	}

	void DemoRunner::generate_world(const size_t& size)
	{
		add_predefined_world_elements();

		materials_.reserve(materials_.size() + size);
		world_.reserve(world_.size() + size);

		const float minimum_size = 0.1f;
		const float maximum_size = 0.25f;

		for (size_t i = world_.size(); i < size; ++i)
		{
			const float radius = rt::mathf::lerp(minimum_size, maximum_size, rt::random::real());

			Vector3f pos = Vector3f(6 + rt::random::range(0.f, 6.f), radius, rt::random::range(-8.f, 0.f));

			materials_.push_back(get_random_material());
			world_.push_back(std::make_unique<Sphere>(pos, radius, *materials_.back()));
		}
	}

	void DemoRunner::create_demo_camera()
	{
		const Vector3f camera_origin = Vector3f(0, 2, 1);
		const Vector3f camera_target = Vector3f(2, 0, -3);
		const Vector3f world_up = Vector3f(0, 1, 0);
		const rt::Camera::Orientation camera_orientation
		{
			camera_origin,
			camera_target,
			world_up
		};

		const float cameraFov = 60;
		const float aspect = (float)width_ / (float)height_;
		const float focus_distance = (camera_orientation.origin - camera_orientation.lookat).magnitude();

		const rt::Camera::ViewSettings camera_view
		{
			cameraFov,
			aspect,
			aperture_,
			focus_distance
		};

		camera_ = std::make_shared<Camera>(camera_orientation, camera_view);
	}

	void DemoRunner::add_predefined_world_elements()
	{
		materials_.push_back(std::make_shared<Lambertian>(Vector3f(0.5f, 0.5f, 0.5f)));
		world_.push_back(std::make_unique<Sphere>(Vector3f(0.f, -1000.f, 0.f), 1000.f, *materials_.back()));

		materials_.push_back(std::make_shared<Dielectric>(1.5f));
		world_.push_back(std::make_unique<Sphere>(Vector3f(0.f, 1.f, -3.f), 1.f, *materials_.back()));

		materials_.push_back(std::make_shared<Lambertian>(Vector3f(0.6f, 0.2f, 0.2f)));
		world_.push_back(std::make_unique<Sphere>(Vector3f(1.f, 1.f, -4.5f), 1.f, *materials_.back()));

		materials_.push_back(std::make_shared<Metallic>(Vector3f(0.8f, 0.8f, 0.9f)));
		world_.push_back(std::make_unique<Sphere>(Vector3f(2.f, 1.f, -3.f), 1.f, *materials_.back()));
	}

	std::shared_ptr<Material> DemoRunner::get_random_material() const
	{
		const float material_type = rt::random::real();

		if (material_type < .6f)
		{
			return std::make_shared<Lambertian>(Vector3f(rt::random::real() * rt::random::real(), rt::random::real() * rt::random::real(), rt::random::real() * rt::random::real()));
		}
		else if (material_type < .95f)
		{
			return std::make_shared<Metallic>(Vector3f(1 + rt::random::real(), 1 + rt::random::real(), 1 + rt::random::real()) * .5f, .5f * rt::random::real());
		}
		else
		{
			float refractive_index_ = (rt::random::real() + 3.f) * .5f;
			return std::make_shared<Dielectric>(refractive_index_);
		}
	}
}