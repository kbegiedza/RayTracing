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

	bool Arguments::parse_arguments(const int argc, const char** argv)
	{
		if (argc < 6)
		{
			show_help();

			return false;
		}

		width_ = std::max<unsigned int>(std::strtoul(argv[1], 0, 10), 1);
		height_ = std::max<unsigned int>(std::strtoul(argv[2], 0, 10), 1);
		smoothing_ = std::max<unsigned int>(std::strtoul(argv[3], 0, 10), 1);
		aperture_ = static_cast<float>(std::atof(argv[4]));
		output_path_ = argv[5];

		return true;
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