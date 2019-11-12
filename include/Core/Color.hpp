#ifndef COLOR_HPP_
#define COLOR_HPP_

namespace rt
{
	class Color
	{
	public:
		static Color black();

	public:
		Color();
		Color(const float& red, const float& green, const float& blue);

		float r() const;
		float g() const;
		float b() const;

		void set_r(const float& value);
		void set_g(const float& value);
		void set_b(const float& value);

	private:
		float r_;
		float g_;
		float b_;
	};
}

#endif // !COLOR_HPP_