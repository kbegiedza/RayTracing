#ifndef LAMBERTIAN_HPP_
#define LAMBERTIAN_HPP_

#include "Materials/Material.hpp"

namespace rt
{
namespace materials
{
	class Lambertian : public Material
	{
	public:
		explicit Lambertian(const Vector3f& albedo);

		virtual bool scatter(const Ray& ray, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const;

	private:
		const Vector3f albedo_;
	};
}
}

#endif // !LAMBERTIAN_HPP_