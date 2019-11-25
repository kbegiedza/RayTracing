#ifndef DIELECTIC_HPP_
#define DIELECTIC_HPP_

#include "Materials/Material.hpp"

namespace rt
{
namespace materials
{
	class Dielectric : public Material
	{
	private:
		struct refract_data
		{
			const Vector3f normal;
			const float index;
			const float cosine;
		};

	public:
		explicit Dielectric(const float& refractive_index);

		bool refract(const Vector3f& vector, const Vector3f& normal, const float& refractive_index, Vector3f& refracted) const;
		virtual bool scatter(const Ray& r_in, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const;

	private:
		refract_data calculate_refract_data(Vector3f direction, Vector3f normal) const;

	private:
		const float refractive_index_;
		const Vector3f albedo_;
	};
}
}

#endif // !DIELECTIC_HPP_