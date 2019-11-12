#include "Geometry/Geometry.hpp"

namespace rt
{
namespace geometry
{
	Geometry::Geometry(const Material& material)
		:material_(material)
	{
	}

	const Material& Geometry::material() const
	{
		return material_;
	}
}
}