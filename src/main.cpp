#include <iostream>
#include <fstream>
#include <string>

#include "Vector3.hpp"

void export_to_ppm(int width, int height)
{
	const std::string path = "./output.ppm";

	std::ofstream stream(path);
	if (!stream.is_open())
	{
		throw std::runtime_error("cannot open file" + path);
	}

	stream << "P3\n" << width << ' ' << height << "\n255\n";
	
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; ++x)
		{
			bs::Vector3f color(float(x) / float(width), float(y) / float(height), .5f);

			bs::Vector3<int> ppmColor(int(255.99 * color.r()), int(255.99 * color.g()), int(255.99 * color.b()));

			stream << ppmColor << std::endl;
		}
	}

	stream.close();
}

int main()
{
	const int size = 300;

	export_to_ppm(size, size);
}