#ifndef HIT_INFO_HPP_
#define HIT_INFO_HPP_

namespace bs
{
	class HittableObject;

	struct hit_info
	{
		float t;
		Vector3f point;
		Vector3f normal;
		const HittableObject* object;
	};
}

#endif // !HITINFO_HPP_