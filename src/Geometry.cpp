#include "Geometry.hpp"

namespace bs
{
	Geometry::Geometry(std::shared_ptr<Material> material)
	{
		material_ = material;
	}
}