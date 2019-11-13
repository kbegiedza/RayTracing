#include "Geometry/Geometry.hpp"

namespace rt
{
namespace geometry
{
	using namespace materials;

	Geometry::Geometry(const Material& material)
		: material_(material)
	{
	}

	Geometry::~Geometry()
	{
	}

	const Material& Geometry::material() const
	{
		return material_;
	}
}
}