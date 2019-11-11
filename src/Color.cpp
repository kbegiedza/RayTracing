#include "Color.hpp"

#include "Math.hpp"

namespace bs
{
	Color::Color()
	{
		r_ = g_ = b_ = 0;
	}

	Color::Color(const float& red, const float& green, const float& blue)
		: r_(clamp01(red)),
		g_(clamp01(green)),
		b_(clamp01(blue))
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

	void Color::r(const float& value)
	{
		r_ = clamp01(value);
	}

	void Color::g(const float& value)
	{
		g_ = clamp01(value);
	}

	void Color::b(const float& value)
	{
		b_ = clamp01(value);
	}
}