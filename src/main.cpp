#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>

#include "Materials/Materials.hpp"
#include "Geometry/Sphere.hpp"
#include "RayTracer.hpp"
#include "PPMExporter.hpp"

namespace random = rt::random;
using namespace rt::materials;
using rt::geometry::Geometry;
using rt::geometry::Sphere;
using rt::Vector3f;

std::vector<std::unique_ptr<Geometry>> generate_random_world(std::vector<std::shared_ptr<Material>>& materials, const size_t elements)
{
	materials.reserve(elements);
	std::vector<std::unique_ptr<Geometry>> world(elements);

	size_t index = 0;
	materials.push_back(std::make_shared<Lambertian>(Vector3f(0.5f, 0.5f, 0.5f)));
	world[index] = std::make_unique<Sphere>(Vector3f(0.f, -1000.f, 0.f), 1000.f, *materials[index]);

	materials.push_back(std::make_shared<Dielectric>(1.5f));
	world[++index] = std::make_unique<Sphere>(Vector3f(0.f, 1.f, -3.f), 1.f, *materials[index]);

	materials.push_back(std::make_shared<Lambertian>(Vector3f(0.6f, 0.2f, 0.2f)));
	world[++index] = std::make_unique<Sphere>(Vector3f(1.f, 1.f, -4.5f), 1.f, *materials[index]);

	materials.push_back(std::make_shared<Metallic>(Vector3f(0.8f, 0.8f, 0.9f)));
	world[++index] = std::make_unique<Sphere>(Vector3f(2.f, 1.f, -3.f), 1.f, *materials[index]);

	for (size_t i = ++index; i < elements; ++i)
	{
		float material_type = random::real();

		// diffuse
		if (material_type < .6f)
		{
			materials.push_back(std::make_shared<Lambertian>(Vector3f(random::real() * random::real(), random::real() * random::real(), random::real()* random::real())));
		}
		// metallic
		else if (material_type < .95f)
		{
			materials.push_back(std::make_shared<Metallic>(Vector3f(1 + random::real(), 1 + random::real(), 1 + random::real()) * .5f, .5f * random::real()));
		}
		// glass
		else
		{
			float refractive_index_ = (random::real() + 3.f) * .5f;
			materials.push_back(std::make_shared<Dielectric>(refractive_index_));
		}
	}

	const float minimum_size = 0.1f;
	const float maximum_size = 0.25f;
	for (size_t i = index; i < elements; ++i)
	{
		float radius_rand = random::real();
		float radius = (1 - radius_rand) * minimum_size + radius_rand * maximum_size;

		auto pos = Vector3f(6 + random::range(0.f, 6.f), radius, random::range(-8.f, 0.f));

		world[i] = std::make_unique<Sphere>(pos, radius, *materials[i]);
	}

	return world;
}

int main()
{
	using namespace std::chrono;

	auto start_time = high_resolution_clock::now();

	const size_t width = 200;
	const size_t height = 100;

	//world
	const size_t world_elements = 150;
	std::vector<std::shared_ptr<Material>> mats;
	auto world = generate_random_world(mats, world_elements);


	// camera
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
	const float aspect = (float)width / (float)height;
	const float focus_distance = (camera_orientation.origin - camera_orientation.lookat).magnitude();
	const float aperture = 0.15f;
	
	const rt::Camera::ViewSettings camera_view
	{
		cameraFov,
		aspect,
		aperture,
		focus_distance
	};

	rt::Camera camera(camera_orientation, camera_view);

	//render
	const size_t smoothSamples = 2;
	const size_t max_depth = 50;
	const rt::RenderSettings render_settings(camera, width, height, max_depth, smoothSamples);

	rt::RayTracer ray_tracer(render_settings, world);
	auto render_data = ray_tracer.render();

	//output
	const std::string path = "./output.ppm";
	try
	{
		rt::PPMExporter::save_data(render_data, width, height, path);
	}
	catch (std::exception & e)
	{
		std::cout << "Error! " << e.what();
	}

	auto end_time = high_resolution_clock::now();

	auto elapsed_ms = duration_cast<milliseconds>(end_time - start_time);

	std::cout << "========================================\n"
		<< "Finished in: " << elapsed_ms.count() << " [ms].\n"
		<< "========================================\n"
		<< "Press any key to exit";

	std::cin.get();
}