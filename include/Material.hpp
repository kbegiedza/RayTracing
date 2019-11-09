#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Math.hpp"

namespace bs
{
	class Material
	{
	public:
		virtual ~Material() {}
		virtual bool scatter(const Ray& ray, const hit_info& hit, Vector3f& attenuation, Ray& scattered) const = 0;
	};

	class Lambertian : public Material
	{
	public:
		Lambertian(const Vector3f& albedo) 
			: albedo(albedo)
		{
		}

		inline virtual bool scatter(const Ray& ray, const hit_info& hit, Vector3f& attenuation, Ray& scattered) const
		{
			auto target = hit.point + hit.normal + random_in_shpere();
			scattered = Ray(hit.point, target - hit.point);
			attenuation = albedo;

			return true;
		}

	public:
		Vector3f albedo;
	};

	class Metallic : public Material
	{
	public:
		Metallic(const Vector3f& albedo)
			: albedo(albedo)
		{
		}

		inline virtual bool scatter(const Ray& ray, const hit_info& hit, Vector3f& attenuation, Ray& scattered) const
		{
			auto reflected = reflect(ray.direction().normalized(), hit.normal);

			scattered = Ray(hit.point, reflected);
			attenuation = albedo;

			return (scattered.direction().dot(hit.normal) > 0);
		}

	public:
		Vector3f albedo;
	};
}

#endif //! MATERIAL_HPP_