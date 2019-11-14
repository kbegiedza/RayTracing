#ifndef METALLIC_HPP_
#define METALLIC_HPP_

#include "Materials/Material.hpp"

namespace rt
{
namespace materials
{
	class Metallic : public Material
	{
	public:
		Metallic(const Vector3f& albedo_, const float& fuzzy = 0);

		virtual bool scatter(const Ray& ray, const HitInfo& hit, Vector3f& attenuation, Ray& scattered) const;

	private:
		Vector3f albedo_;
		float fuzziness_;
	};
}
}
#endif // !METALLIC_HPP_