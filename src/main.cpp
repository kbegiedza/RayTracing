#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

bs::Vector3f cast_ray(const bs::Ray& ray, bs::IHittable** world, int elements, int depth)
{
	bs::hit_info hit;

	float current_max = std::numeric_limits<float>::max();
	const float minimum = 0.001;
	bool got_any_hit = false;
	bs::hit_info tempHit;
	for (int i = 0; i < elements; ++i)
	{
		if ((*(world + i))->hit(ray, minimum, current_max, tempHit))
		{
			got_any_hit = true;
			current_max = tempHit.t;
			hit = tempHit;
		}
	}

	if (got_any_hit)
	{
		bs::Ray scattered;
		bs::Vector3f attenuation;

		if (depth < 50 && hit.object->material->scatter(ray, hit, attenuation, scattered))
		{
			return attenuation.hadamard(cast_ray(scattered, world, elements, depth + 1));
		}
		else
		{
			return bs::Vector3f();
		}
	}
	else
	{
		auto norm_dir = ray.direction().normalized();
		float t = 0.5f * (norm_dir.y() + 1);
		return bs::Vector3f(1.0, 1.0, 1.0) * (1 - t) + bs::Vector3f(0.5, 0.7, 1.0) * t;
	}
}

void export_to_ppm(int width, int height)
{
	const std::string path = "./output.ppm";

	std::ofstream stream(path);
	if (!stream.is_open())
	{
		throw std::runtime_error("cannot open file" + path);
	}

	// file header
	stream << "P3\n" << width << ' ' << height << "\n255\n";

	const int upp = 100;
	const int clipZ = -1;

	bs::Vector3f bottom_left(-width / upp, -height / upp, clipZ);
	bs::Vector3f horizontal(width / upp * 2, 0, 0);
	bs::Vector3f vertical(0, height / upp * 2, 0);
	bs::Camera camera(bs::Vector3f(), bottom_left, horizontal, vertical);

	bs::Material* matteRedMat = new bs::Lambertian(bs::Vector3f(.8f, .5, .8f));
	bs::Material* matteGreenMat = new bs::Lambertian(bs::Vector3f(.3, 1, .3f));
	bs::Material* metallicMat = new bs::Metallic(bs::Vector3f(0.7f, 0.7f, 0.9f));

	const int elements = 4;
	bs::IHittable** world = new bs::IHittable * [elements]
	{
		new bs::Sphere(bs::Vector3f(1, 0, -1), .5f, matteRedMat),
		new bs::Sphere(bs::Vector3f(-1, 0, -1.25), .7f, matteRedMat),
		new bs::Sphere(bs::Vector3f(0, 0, -1), .5f, metallicMat),
		new bs::Sphere(bs::Vector3f(0, -100.5f, -1), 100, matteGreenMat)
	};


	const int smoothSamples = 20;

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; ++x)
		{
			bs::Vector3f color;

			for (int s = 0; s < smoothSamples; ++s)
			{
				float u = float(x + bs::random()) / float(width);
				float v = float(y + bs::random()) / float(height);

				color += cast_ray(camera.get_ray(u, v), world, elements, 0);
			}
			
			color /= smoothSamples;
			color = bs::Vector3f(std::sqrt(color[0]), std::sqrt(color[1]), std::sqrt(color[2]));
			bs::Vector3<int> ppmColor(int(255.99 * color.r()), int(255.99 * color.g()), int(255.99 * color.b()));

			stream << ppmColor << std::endl;
		}
	}

	for (int i = 0; i < elements; ++i)
	{
		delete* world;
		*world = nullptr;
	}
	delete[] world;
	world = nullptr;

	delete matteRedMat;
	matteRedMat = nullptr;
	delete matteGreenMat;
	matteGreenMat = nullptr;
	delete metallicMat;
	metallicMat = nullptr;

	stream.close();
}

int main()
{
	using namespace std::chrono;

	auto start_time = high_resolution_clock::now();
	
	const int sizeX = 200;
	const int sizeY = 100;

	export_to_ppm(sizeX, sizeY);

	auto end_time = high_resolution_clock::now();

	auto elapsed_ms = duration_cast<std::chrono::milliseconds>(end_time - start_time);
	
	std::cout << "========================================\n"
			  << "Finished in: " << elapsed_ms.count() << " [ms].\n"
			  << "========================================\n";

}