#ifndef RAY_HPP_
#define RAY_HPP_

#include "Core/Vector3.hpp"

namespace rt
{
	class Ray
	{
	public:
		Ray();
		Ray(const Vector3f& origin, const Vector3f& direction);

		Vector3f origin() const;
		Vector3f direction() const;

		Vector3f travel(const float& time) const;

	private:
		Vector3f origin_;
		Vector3f direction_;
	};
}

#endif // !RAY_HPP_