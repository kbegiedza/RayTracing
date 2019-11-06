#include <iostream>
#include <fstream>
#include <string>

#include "Vector3.hpp"
#include "Ray.hpp"

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

	auto skybox = [&](const bs::Ray r) -> bs::Vector3f {
		auto norm_dir = r.direction().normalized();
		float t = 0.5f * (norm_dir.y() + 1);
		return bs::Vector3f(1.0, 1.0, 1.0) * (1 - t) + bs::Vector3f(0.5, 0.7, 1.0) * t;
	};

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; ++x)
		{
			float u = float(x) / float(width);
			float v = float(y) / float(height);

			bs::Ray ray(camera, bottom_left + (horizontal * u) + (vertical * v));

			bs::Vector3f color = skybox(ray);

			bs::Vector3<int> ppmColor(int(255.99 * color.r()), int(255.99 * color.g()), int(255.99 * color.b()));

			stream << ppmColor << std::endl;
		}
	}

	stream.close();
}

int main()
{
	const int sizeX = 300;
	const int sizeY = 200;

	export_to_ppm(sizeX, sizeY);
}