#ifndef IHITTABLE_HPP_
#define IHITTABLE_HPP_

#include <memory>

#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Material.hpp"

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

#endif // !IHITTABLE_HPP_