#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <cmath>

namespace rt
{
	template <typename T = double>
	class Vector3
	{
	public:
		static Vector3<T> reflect(const Vector3<T>& vector, const Vector3<T>& normal);
		static T dot(const Vector3<T>& lhs, const Vector3<T>& rhs);
		static Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs);

	public:
		Vector3();
		Vector3(const T& x, const T& y, const T& z);

		T x() const { return data_[0]; }
		T y() const { return data_[1]; }
		T z() const { return data_[2]; }

		void set_x(const T& value) { data_[0] = value; }
		void set_y(const T& value) { data_[1] = value; }
		void set_z(const T& value) { data_[2] = value; }

		T& operator[](const int i) { return data_[i]; }
		T operator[](const int i) const { return data_[i]; }
		const Vector3<T>& operator+() const { return *this; }
		Vector3<T> operator-() const { return Vector3<T>(-data_[0], -data_[1], -data_[2]); }

		Vector3<T>& hadamard(const Vector3<T> & rhs);

		Vector3<T>& operator+=(const Vector3<T> & rhs);
		Vector3<T>& operator-=(const Vector3<T> & rhs);
		Vector3<T>& operator*=(const T scalar);
		Vector3<T>& operator/=(const T scalar);

		Vector3<T> operator*(const T scalar) const;
		Vector3<T> operator/(const T scalar) const;
		Vector3<T> operator+(const Vector3<T>& rhs) const;
		Vector3<T> operator-(const Vector3<T>& rhs) const;

		T dot(const Vector3<T>& rhs) const;
		Vector3<T> cross(const Vector3<T>& rhs) const;

		T magnitude() const;
		T squared_magnitude() const;

		void normalize();
		Vector3<T> normalized() const;

		template<typename T>
		friend Vector3<T> operator*(const T lhs, const Vector3<T>& rhs);

	private:
		T data_[3];
	};

	typedef Vector3<float> Vector3f;

	template<typename T>
	Vector3<T> Vector3<T>::reflect(const Vector3<T>& vector, const Vector3<T>& normal)
	{
		return vector - (normal * 2 * vector.dot(normal));
	}

	template<typename T>
	inline T Vector3<T>::dot(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::cross(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		return Vector3<T>(lhs[1] * rhs[2] - lhs[2] * rhs[1],
						lhs[2] * rhs[0] - lhs[0] * rhs[2],
						lhs[0] * rhs[1] - lhs[1] * rhs[0]);
	}

	template<typename T>
	Vector3<T>::Vector3()
	{
		data_[0] = 0;
		data_[1] = 0;
		data_[2] = 0;
	}

	template<typename T>
	Vector3<T>::Vector3(const T& x, const T& y, const T& z)
	{
		data_[0] = x;
		data_[1] = y;
		data_[2] = z;
	}

	template<typename T>
	inline T Vector3<T>::dot(const Vector3<T>& rhs) const
	{
		return dot(*this, rhs);
	}

	template<typename T>
	Vector3<T> Vector3<T>::cross(const Vector3<T>& rhs) const
	{
		return cross(*this, rhs);
	}

	template<typename T>
	inline T Vector3<T>::magnitude() const
	{
		return sqrt(squared_magnitude());
	}

	template<typename T>
	inline T Vector3<T>::squared_magnitude() const
	{
		return dot(*this, *this);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator*(const T scalar) const
	{
		return Vector3<T>(data_[0] * scalar, data_[1] * scalar, data_[2] * scalar);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator/(const T scalar) const
	{
		return Vector3<T>(data_[0] / scalar, data_[1] / scalar, data_[2] / scalar);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator+(const Vector3<T>& rhs) const
	{
		return Vector3<T>(data_[0] + rhs[0], data_[1] + rhs[1], data_[2] + rhs[2]);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator-(const Vector3<T>& rhs) const
	{
		return Vector3<T>(data_[0] - rhs[0], data_[1] - rhs[1], data_[2] - rhs[2]);
	}

	template<typename T>
	Vector3<T>& Vector3<T>::hadamard(const Vector3<T>& rhs)
	{
		data_[0] *= rhs.data_[0];
		data_[1] *= rhs.data_[1];
		data_[2] *= rhs.data_[2];

		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& rhs)
	{
		data_[0] += rhs.data_[0];
		data_[1] += rhs.data_[1];
		data_[2] += rhs.data_[2];

		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& rhs)
	{
		data_[0] -= rhs.data_[0];
		data_[1] -= rhs.data_[1];
		data_[2] -= rhs.data_[2];

		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator*=(const T scalar)
	{
		data_[0] *= scalar;
		data_[1] *= scalar;
		data_[2] *= scalar;

		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator/=(const T scalar)
	{
		data_[0] /= scalar;
		data_[1] /= scalar;
		data_[2] /= scalar;

		return *this;
	}

	template<typename T>
	void Vector3<T>::normalize()
	{
		T mag = magnitude();

		data_[0] /= mag;
		data_[1] /= mag;
		data_[2] /= mag;
	}

	template<typename T>
	Vector3<T> Vector3<T>::normalized() const
	{
		T mag = magnitude();

		return Vector3<T>(data_[0] / mag, data_[1] / mag, data_[2] / mag);
	}

	template<typename T>
	Vector3<T> operator*(const T lhs, const Vector3<T>& rhs)
	{
		return rhs * lhs;
	}
}

#endif // !VECTOR3_HPP_