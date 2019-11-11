#ifndef COLOR_HPP_
#define COLOR_HPP_

namespace bs
{
	class Color
	{
	public:
		Color();
		Color(const float& r, const float& g, const float& b);

		float r() const;
		float g() const;
		float b() const;

		void r(const float& value);
		void g(const float& value);
		void b(const float& value);

	private:
		float r_;
		float g_;
		float b_;
	};
}

#endif // !COLOR_HPP_