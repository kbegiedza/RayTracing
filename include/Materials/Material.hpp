#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "Core/Mathf.hpp"
#include "Core/Vector3.hpp"
#include "Core/Random.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"

namespace rt
{
namespace materials
{
	class Material
	{
	public:
		virtual ~Material() {}

		virtual bool scatter(const Ray& ray, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const = 0;
	};
}
}
#endif //! MATERIAL_HPP_