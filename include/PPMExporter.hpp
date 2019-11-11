#ifndef PPMEXPORTER_HPP_
#define PPMEXPORTER_HPP_

#include <vector>
#include <string>

#include "Color.hpp"

namespace bs
{
	class PPMExporter
	{
	public:
		static void save_data(const std::vector<Color>& data, const size_t& width, const size_t& height, const std::string& path);
	};
}

#endif // !PMMEXPORTER_HPP_