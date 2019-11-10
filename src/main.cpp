#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

bs::IHittable** generate_random_world(bs::Material*** materials, const size_t elements = 50)
{
	*materials = new bs::Material * [elements];
	bs::IHittable** world = new bs::IHittable * [elements];

	size_t index = 0;
	(*materials)[index] = new bs::Lambertian(bs::Vector3f(0.5f, 0.5f, 0.5f));
	world[index] = new bs::Sphere(bs::Vector3f(0, -1000, 0), 1000, (*materials)[index]);

	(*materials)[++index] = new bs::Dielectric(1.5);
	world[index] = new bs::Sphere(bs::Vector3f(0, 1, -1), 1, (*materials)[index]);
	(*materials)[++index] = new bs::Lambertian(bs::Vector3f(0.6f, 0.2f, 0.2f));
	world[index] = new bs::Sphere(bs::Vector3f(-2, 1, -1), 1, (*materials)[index]);
	(*materials)[++index] = new bs::Metallic(bs::Vector3f(0.8f, 0.8f, 0.9f));
	world[index] = new bs::Sphere(bs::Vector3f(2, 1, -1), 1, (*materials)[index]);

	for (int i = ++index; i < elements; ++i)
	{
		float material_type = bs::random();

		// diffuse
		if (material_type < .6f)
		{
			(*materials)[i] = new bs::Lambertian(bs::Vector3f(bs::random() * bs::random(), bs::random() * bs::random(), bs::random()* bs::random()));
		}
		// metallic
		else if (material_type < .95f)
		{
			int fuzziness = 0;
			(*materials)[i] = new bs::Metallic(bs::Vector3f(1+bs::random(), 1+bs::random(), 1+bs::random()) * .5f, .5f * bs::random());
		}
		// glass
		else
		{
			int refractive_index = 0;
			(*materials)[i] = new bs::Dielectric(refractive_index);
		}
	}

	const float minimum_size = 0.1;
	const float maximum_size = 0.25;
	for (int i = index; i < elements; ++i)
	{
		float radius_rand = bs::random();
		float radius = (1 - radius_rand) * minimum_size + radius_rand * maximum_size;
		auto pos = bs::Vector3f(5 - bs::random() * 10, radius, 5 - bs::random()*10);
		world[i] = new bs::Sphere(pos, radius, (*materials)[i]);
	}

	return world;
}

bs::Vector3f cast_ray(const bs::Ray & ray, bs::IHittable * *world, int elements, int depth)
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


	const int clipZ = -1;

	const float cameraFov = 60;
	const float aspect = (float)width / (float)height;

	const bs::Vector3f world_up = bs::Vector3f(0, 1, 0);
	const bs::Vector3f camera_pos = bs::Vector3f(3, 2, 3);
	const bs::Vector3f poi = bs::Vector3f(0, 0, -1);

	const float focus_distance = (camera_pos - poi).magnitude();
	const float aperture = 0;

	bs::Material * *mats = nullptr;
	const size_t world_elements = 25;
	auto world = generate_random_world(&mats, world_elements);

	bs::Camera camera(camera_pos, poi, world_up, cameraFov, aspect, aperture, focus_distance);

	const int smoothSamples = 64;

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; ++x)
		{
			bs::Vector3f color;

			for (int s = 0; s < smoothSamples; ++s)
			{
				float u = float(x + bs::random()) / float(width);
				float v = float(y + bs::random()) / float(height);

				color += cast_ray(camera.get_ray(u, v), world, world_elements, 0);
			}

			color /= smoothSamples;
			color = bs::Vector3f(std::sqrt(color[0]), std::sqrt(color[1]), std::sqrt(color[2]));
			bs::Vector3<int> ppmColor(int(255.99 * color.r()), int(255.99 * color.g()), int(255.99 * color.b()));

			stream << ppmColor << std::endl;
		}
	}
	stream.close();

	for (int i = 0; i < world_elements; ++i)
	{
		delete* (mats + i);
		*(mats + i) = nullptr;

		delete * (world + i);
		*(world + i) = nullptr;
	}

	delete[] world;
	world = nullptr;

	delete[] mats;
	mats = nullptr;
}

int main()
{
	using namespace std::chrono;

	auto start_time = high_resolution_clock::now();

	const int sizeX = 640;
	const int sizeY = 480;

	export_to_ppm(sizeX, sizeY);

	auto end_time = high_resolution_clock::now();

	auto elapsed_ms = duration_cast<std::chrono::milliseconds>(end_time - start_time);

	std::cout << "========================================\n"
		<< "Finished in: " << elapsed_ms.count() << " [ms].\n"
		<< "========================================\n";

}