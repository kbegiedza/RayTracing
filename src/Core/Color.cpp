#include "Core/Color.hpp"
#include "Core/Mathf.hpp"

namespace rt
{
	Color Color::black()
	{
		return Color();
	}

	Color::Color()
	{
		r_ = g_ = b_ = 0;
	}

	Color::Color(const float& red, const float& green, const float& blue)
		: r_(mathf::clamp01(red)),
		g_(mathf::clamp01(green)),
		b_(mathf::clamp01(blue))
	{
	}

	float Color::r() const
	{
		return r_;
	}

	float Color::g() const
	{
		return g_;
	}

	float Color::b() const
	{
		return b_;
	}

	void Color::set_r(const float& value)
	{
		r_ = mathf::clamp01(value);
	}

	void Color::set_g(const float& value)
	{
		g_ = mathf::clamp01(value);
	}

	void Color::set_b(const float& value)
	{
		b_ = mathf::clamp01(value);
	}
}