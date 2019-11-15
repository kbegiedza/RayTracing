#ifndef DEMORUNNER_HPP_
#define DEMORUNNER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#include "Arguments.hpp"
#include "Materials/Materials.hpp"
#include "Geometry/Sphere.hpp"
#include "RayTracer.hpp"
#include "PPMExporter.hpp"
#include "DemoRunner.hpp"

namespace rt
{
	class DemoRunner
	{
	public:
		DemoRunner(const Arguments& arguments, const size_t& world_elements = 150);

		std::vector<Color> render() const;

	private:
		void add_predefined_world_elements();
		void generate_world(const size_t& size);
		std::shared_ptr<materials::Material> get_random_material() const;

	private:
		const size_t width_;
		const size_t height_;
		const size_t smoothing_samples_;
		const float aperture_;

		std::vector<std::unique_ptr<geometry::Geometry>> world_;
		std::vector<std::shared_ptr<materials::Material>> materials_;
	};
}

#endif // !DEMORUNNER_HPP_