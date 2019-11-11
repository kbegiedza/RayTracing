#include "Geometry.hpp"

namespace bs
{
	Geometry::Geometry(std::shared_ptr<Material> material)
	{
		material_ = material;
	}

	const Material& Geometry::material() const
	{
		return *material_;
	}
}