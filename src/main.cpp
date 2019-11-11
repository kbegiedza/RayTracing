#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>

#include "Core/Vector3.hpp"
#include "Ray.hpp"
#include "Geometry/Sphere.hpp"
#include "Camera.hpp"
#include "RayTracer.hpp"
#include "PPMExporter.hpp"

std::vector<std::unique_ptr<bs::Geometry>> generate_random_world(std::vector<std::shared_ptr<bs::Material>>& materials, const size_t elements)
{
	materials.reserve(elements);
	std::vector<std::unique_ptr<bs::Geometry>> world(elements);

	size_t index = 0;
	materials.push_back(std::make_shared<bs::Lambertian>(bs::Vector3f(0.5f, 0.5f, 0.5f)));
	world[index] = std::make_unique<bs::Sphere>(bs::Vector3f(0.f, -1000.f, 0.f), 1000.f, materials[index]);

	index++;
	materials.push_back(std::make_shared<bs::Dielectric>(1.5f));
	world[index] = std::make_unique<bs::Sphere>(bs::Vector3f(0.f, 1.f, -3.f), 1.f, materials[index]);

	index++;
	materials.push_back(std::make_shared<bs::Lambertian>(bs::Vector3f(0.6f, 0.2f, 0.2f)));
	world[index] = std::make_unique<bs::Sphere>(bs::Vector3f(1.f, 1.f, -4.5f), 1.f, materials[index]);

	index++;
	materials.push_back(std::make_shared<bs::Metallic>(bs::Vector3f(0.8f, 0.8f, 0.9f)));
	world[index] = std::make_unique<bs::Sphere>(bs::Vector3f(2.f, 1.f, -3.f), 1.f, materials[index]);

	for (size_t i = ++index; i < elements; ++i)
	{
		float material_type = bs::random();

		// diffuse
		if (material_type < .6f)
		{
			materials.push_back(std::make_shared<bs::Lambertian>(bs::Vector3f(bs::random() * bs::random(), bs::random() * bs::random(), bs::random()* bs::random())));
		}
		// metallic
		else if (material_type < .95f)
		{
			materials.push_back(std::make_shared<bs::Metallic>(bs::Vector3f(1+bs::random(), 1+bs::random(), 1+bs::random()) * .5f, .5f * bs::random()));
		}
		// glass
		else
		{
			float refractive_index = (bs::random() + 3.f) * .5f;
			materials.push_back(std::make_shared<bs::Dielectric>(refractive_index));
		}
	}

	const float minimum_size = 0.1f;
	const float maximum_size = 0.25f;
	for (size_t i = index; i < elements; ++i)
	{
		float radius_rand = bs::random();
		float radius = (1 - radius_rand) * minimum_size + radius_rand * maximum_size;

		auto pos = bs::Vector3f(6 + bs::random_range(0.f, 6.f), radius, bs::random_range(-8.f, 0.f));

		world[i] = std::make_unique<bs::Sphere>(pos, radius, materials[i]);
	}

	return world;
}

int main()
{
	using namespace std::chrono;

	auto start_time = high_resolution_clock::now();

	const int width = 192;
	const int height = 108;

	//world
	const size_t world_elements = 150;
	std::vector<std::shared_ptr<bs::Material>> mats;
	auto world = generate_random_world(mats, world_elements);

	// camera
	const float cameraFov = 60;
	const float aspect = (float)width / (float)height;

	const bs::Vector3f world_up = bs::Vector3f(0, 1, 0);
	const bs::Vector3f camera_pos = bs::Vector3f(0, 2, 1);
	const bs::Vector3f poi = bs::Vector3f(2, 0, -3);

	const float focus_distance = (camera_pos - poi).magnitude();
	const float aperture = 0.15f;
	bs::Camera camera(camera_pos, poi, world_up, cameraFov, aspect, aperture, focus_distance);

	//render
	const int smoothSamples = 2;
	const bs::RenderSettings render_settings(camera, width, height, smoothSamples);
	auto render_data = bs::RayTracer::render(render_settings, world);

	//output
	const std::string path = "./output.ppm";
	try
	{
		bs::PPMExporter::save_data(render_data, width, height, path);
	}
	catch (std::exception & e)
	{
		std::cout << "Error! " << e.what();
	}

	auto end_time = high_resolution_clock::now();

	auto elapsed_ms = duration_cast<milliseconds>(end_time - start_time);

	std::cout << "========================================\n"
		<< "Finished in: " << elapsed_ms.count() << " [ms].\n"
		<< "========================================\n";
}