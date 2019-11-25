#ifndef PPMEXPORTER_HPP_
#define PPMEXPORTER_HPP_

#include <vector>
#include <string>

#include "Core/Color.hpp"

namespace rt
{
	class PPMExporter
	{
	public:
		static void save_data(const std::vector<Color>& data, const size_t& width, const size_t& height, const std::string& path);

	private:
		static void write_data(std::ofstream& stream, const std::vector<Color>& data);
		static void write_header(std::ofstream& stream, const size_t& width, const size_t& height);

	private:
		static const std::string extension_;
		static constexpr char separator_ = ' ';
	};
}

#endif // !PMMEXPORTER_HPP_