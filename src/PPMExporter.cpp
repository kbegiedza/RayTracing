#include <fstream>

#include "PPMExporter.hpp"
#include "Core/Vector3.hpp"

namespace bs
{
	void PPMExporter::save_data(const std::vector<Color>& data, const size_t& width, const size_t& height, const std::string& path)
	{
		std::ofstream stream(path);
		if (!stream.is_open())
		{
			throw std::runtime_error("cannot open file" + path);
		}

		write_header(stream, width, height);
		write_data(stream, data);

		stream.close();
	}

	void PPMExporter::write_data(std::ofstream& stream, const std::vector<bs::Color>& data)
	{
		for (auto&& color : data)
		{
			bs::Vector3<int> ppmColor(int(255.99 * color.r()), int(255.99 * color.g()), int(255.99 * color.b()));

			stream << ppmColor[0] << " " << ppmColor[1] << " " << ppmColor[2] << std::endl;
		}
	}

	void PPMExporter::write_header(std::ofstream& stream, const size_t& width, const size_t& height)
	{
		const std::string color_value = "255";
		const std::string header = "P3";
		const char separator = ' ';

		stream << header << std::endl
			<< width << ' ' << height << std::endl
			<< color_value << std::endl;
	}
}