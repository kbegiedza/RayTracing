#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <memory>

#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Materials/Material.hpp"

namespace bs
{
	class Geometry
	{
	public:
		Geometry(std::shared_ptr<Material> material);

		virtual bool hit(const Ray& ray, const float& min_translation, const float& max_translation, HitInfo& hit) const = 0;

		const Material& material() const;

	private:
		std::shared_ptr<Material> material_;
	};
}

#endif // !GEOMETRY_HPP_