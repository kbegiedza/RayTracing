#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Math.hpp"

bs::Vector3f colorize(const bs::Ray& ray, bs::IHittable** world, int elements)
{
	bs::hit hit;

	float current_max = std::numeric_limits<float>::max();
	const float minimum = 0;
	bool got_any_hit = false;
	bs::hit tempHit;
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
		bs::Vector3f color = hit.normal + bs::Vector3f(1, 1, 1);
		return color * 0.5;
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
	bs::Vector3f camera;

	const int elements = 4;
	bs::IHittable** world = new bs::IHittable* [elements]
	{
		new bs::Sphere(bs::Vector3f(0, 0, -1), .5f),
		new bs::Sphere(bs::Vector3f(-1, 0, -1.5), .3f),
		new bs::Sphere(bs::Vector3f(0.6, -.5, -.4), .2f),
		new bs::Sphere(bs::Vector3f(0, -100.5f, -1), 100)
	};

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; ++x)
		{
			float u = float(x) / float(width);
			float v = float(y) / float(height);

			bs::Ray ray(camera, bottom_left + (horizontal * u) + (vertical * v));

			bs::Vector3f color = colorize(ray, world, elements);

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

	stream.close();
}

int main()
{
	const int sizeX = 300;
	const int sizeY = 200;

	export_to_ppm(sizeX, sizeY);
}