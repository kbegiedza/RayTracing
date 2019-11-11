#include <fstream>

#include "PPMExporter.hpp"
#include "Vector3.hpp"

namespace bs
{
	void PPMExporter::save_data(const std::vector<Color>& data, const size_t& width, const size_t& height, const std::string& path)
	{
		std::ofstream stream(path);
		if (!stream.is_open())
		{
			throw std::runtime_error("cannot open file" + path);
		}

		// file header
		stream << "P3\n" << width << ' ' << height << "\n255\n";
		for (auto&& color : data)
		{
			bs::Vector3<int> ppmColor(int(255.99 * color.r()), int(255.99 * color.g()), int(255.99 * color.b()));

			stream << ppmColor << std::endl;
		}
		stream.close();
	}
}