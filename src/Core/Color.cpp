#include "Core/Color.hpp"
#include "Core/Mathf.hpp"

namespace rt
{
	using mathf::clamp01;

	Color Color::black()
	{
		return Color();
	}

	Color Color::correct_gamma(const Vector3f& color)
	{
		return Color(
			std::sqrt(color[0]),
			std::sqrt(color[1]),
			std::sqrt(color[2])
		);
	}

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

	void Color::set_r(const float& value)
	{
		r_ = clamp01(value);
	}

	void Color::set_g(const float& value)
	{
		g_ = clamp01(value);
	}

	void Color::set_b(const float& value)
	{
		b_ = clamp01(value);
	}
}