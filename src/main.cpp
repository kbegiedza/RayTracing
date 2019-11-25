#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>

#include "Arguments.hpp"
#include "PPMExporter.hpp"
#include "DemoRunner.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

void render_with_arguments(const rt::Arguments arguments);

int main(int argc, const char** argv)
{
	rt::Arguments::parse_arguments(argc, argv, render_with_arguments);

	std::cout << "Press any key to exit\n";
	std::cin.get();

	return 0;
}

void render_with_arguments(const rt::Arguments arguments)
{
	constexpr int world_size = 150;

	rt::DemoRunner demo(arguments, world_size);

	const auto start_time = high_resolution_clock::now();

	const auto render_data = demo.render();

	const auto end_time = high_resolution_clock::now();
	const auto rendering_milliseconds = duration_cast<milliseconds>(end_time - start_time);

	try
	{
		rt::PPMExporter::save_data(render_data, arguments.width(), arguments.height(), arguments.output_path());
	}
	catch (std::exception & e)
	{
		std::cout << "Error! " << e.what() << std::endl;
	}

	std::cout << "Rendering time: " << rendering_milliseconds.count() << " [ms]\n";
}