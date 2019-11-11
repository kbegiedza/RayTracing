#ifndef PPMEXPORTER_HPP_
#define PPMEXPORTER_HPP_

#include <vector>
#include <string>

#include "Core/Color.hpp"

namespace bs
{
	class PPMExporter
	{
	public:
		static void save_data(const std::vector<Color>& data, const size_t& width, const size_t& height, const std::string& path);
	private:
		static void write_data(std::ofstream& stream, const std::vector<bs::Color>& data);
		static void write_header(std::ofstream& stream,const size_t& width, const size_t& height);
	};
}

#endif // !PMMEXPORTER_HPP_