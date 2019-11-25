#include <fstream>

#include "PPMExporter.hpp"
#include "Core/Vector3.hpp"
#include <iostream>

namespace rt
{
	const std::string PPMExporter::extension_ = ".ppm";

	void PPMExporter::save_data(const std::vector<Color>& data, const size_t& width, const size_t& height, const std::string& path)
	{
		const std::string path_with_extension = path + extension_;

		std::ofstream stream(path_with_extension);
		if (!stream.is_open())
		{
			throw std::runtime_error("Cannot open or create file" + path_with_extension);
		}

		write_header(stream, width, height);
		write_data(stream, data);

		stream.close();

		std::cout << "Render saved under: " << path << std::endl;
	}

	void PPMExporter::write_data(std::ofstream& stream, const std::vector<rt::Color>& data)
	{
		for (auto& color : data)
		{
			rt::Vector3<int> ppmColor(int(255 * color.r()), int(255 * color.g()), int(255 * color.b()));

			stream << ppmColor[0] << separator_ << ppmColor[1] << separator_ << ppmColor[2] << std::endl;
		}
	}

	void PPMExporter::write_header(std::ofstream& stream, const size_t& width, const size_t& height)
	{
		const std::string color_value = "255";
		const std::string header = "P3";

		stream << header << std::endl
			<< width << separator_ << height << std::endl
			<< color_value << std::endl;
	}
}