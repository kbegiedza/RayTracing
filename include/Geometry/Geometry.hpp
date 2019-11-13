#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <memory>

#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Materials/Material.hpp"

namespace rt
{
namespace geometry
{
	class Geometry
	{
	public:
		Geometry(const materials::Material& material);
		virtual ~Geometry();

		const materials::Material& material() const;

		virtual bool hit(const Ray& ray, const float& min_translation, const float& max_translation, HitInfo& hit) const = 0;

	private:
		const materials::Material& material_;
	};

}
}

#endif // !GEOMETRY_HPP_