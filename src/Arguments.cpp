#include "Arguments.hpp"
#include <iostream>

namespace rt
{
	void Arguments::show_help()
	{
		std::cout << "\n==========\nDemo ray tracer\n==========\n"
			<< "input parameters:\n"
			<< "1st param: render width (> 0)\n"
			<< "2nd param: render height (> 0)\n"
			<< "3rd param: smoothing samples (> 0)\n"
			<< "4th param: camera\'s aperture [float]\n"
			<< "5th param: output file path\n"
			<< std::endl;
	}

	void Arguments::parse_arguments(const int argc, const char** argv, const std::function<void(Arguments)>& success_callback)
	{
		if (argc < 6)
		{
			show_help();

			return;
		}

		const auto width = std::max<unsigned int>(std::strtoul(argv[1], 0, 10), 1);
		const auto height = std::max<unsigned int>(std::strtoul(argv[2], 0, 10), 1);
		const auto smoothing = std::max<unsigned int>(std::strtoul(argv[3], 0, 10), 1);
		const auto aperture = static_cast<float>(std::atof(argv[4]));
		const auto output_path = argv[5];

		const Arguments arguments(width, height, smoothing, aperture, output_path);

		success_callback(arguments);
	}

	Arguments::Arguments(const size_t& width, const size_t& height, const size_t& smoothing, const float& aperture, const std::string& output_path)
		:width_(width),
		height_(height),
		smoothing_(smoothing),
		aperture_(aperture),
		output_path_(output_path)
	{
	}

	const size_t Arguments::width() const
	{
		return width_;
	}

	const size_t Arguments::height() const
	{
		return height_;
	}

	const size_t Arguments::smoothing() const
	{
		return smoothing_;
	}

	const float Arguments::aperture() const
	{
		return aperture_;
	}

	const std::string Arguments::output_path() const
	{
		return output_path_;
	}
}