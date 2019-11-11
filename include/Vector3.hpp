#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <iostream>
#include <cmath>

namespace bs
{
	template <typename T>
	class Vector3
	{
	public:
		Vector3();
		Vector3(const T x, const T y, const T z);

		inline T x() const { return data_[0]; }
		inline T y() const { return data_[1]; }
		inline T z() const { return data_[2]; }

		inline const Vector3<T>& operator+() const { return *this; }
		inline Vector3<T> operator-() const { return Vector3<T>(-data_[0], -data_[1], -data_[2]); }
		inline T operator[](const int i) const { return data_[i]; }
		inline T& operator[](const int i) { return data_[i]; }

		inline Vector3<T>& hadamard(const Vector3<T> & rhs);
		inline Vector3<T>& inversed_hadamard(const Vector3<T> & rhs);

		inline Vector3<T>& operator+=(const Vector3<T> & rhs);
		inline Vector3<T>& operator-=(const Vector3<T> & rhs);
		inline Vector3<T>& operator*=(const T scalar);
		inline Vector3<T>& operator/=(const T scalar);

		inline Vector3<T> operator*(const T scalar) const;
		inline Vector3<T> operator/(const T scalar) const;
		inline Vector3<T> operator+(const Vector3<T>& rhs) const;
		inline Vector3<T> operator-(const Vector3<T>& rhs) const;

		inline T dot(const Vector3<T>& rhs) const;
		inline Vector3<T> cross(const Vector3<T>& rhs) const;

		inline T magnitude() const { return sqrt(squard_magnitude()); }
		inline T squard_magnitude() const { return data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2]; }

		inline void normalize();
		inline Vector3<T> normalized() const;

		template<typename T>
		friend inline std::ifstream& operator>>(std::ifstream & input, Vector3<T> & rhs);

		template<typename T>
		friend inline std::ofstream& operator<<(std::ofstream & output, const Vector3<T> & rhs);

		template<typename T>
		friend inline std::istream& operator>>(std::istream & input, Vector3<T> & rhs);

		template<typename T>
		friend inline std::ostream& operator<<(std::ostream & output, const Vector3<T> & rhs);

		template<typename T>
		friend inline Vector3<T> operator*(const T lhs, const Vector3<T>& rhs);

	private:
		T data_[3];
	};

	typedef Vector3<float> Vector3f;

	template<typename T>
	inline Vector3<T>::Vector3()
	{
		data_[0] = 0;
		data_[1] = 0;
		data_[2] = 0;
	}

	template<typename T>
	inline Vector3<T>::Vector3(const T x, const T y, const T z)
	{
		data_[0] = x;
		data_[1] = y;
		data_[2] = z;
	}

	template<typename T>
	inline T Vector3<T>::dot(const Vector3<T>& rhs) const
	{
		return data_[0] * rhs[0] + data_[1] * rhs[1] + data_[2] * rhs[2];
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::cross(const Vector3<T>& rhs) const
	{
		return Vector3<T>(
			data_[1] * rhs.data_[2] - data_[2] * rhs.data_[1],
			data_[2] * rhs.data_[0] - data_[0] * rhs.data_[2],
			data_[0] * rhs.data_[1] - data_[1] * rhs.data_[0]
			);
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::operator*(const T scalar) const
	{
		return Vector3<T>(data_[0] * scalar, data_[1] * scalar, data_[2] * scalar);
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::operator/(const T scalar) const
	{
		return Vector3<T>(data_[0] / scalar, data_[1] / scalar, data_[2] / scalar);
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& rhs) const
	{
		return Vector3<T>(data_[0] + rhs[0], data_[1] + rhs[1], data_[2] + rhs[2]);
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& rhs) const
	{
		return Vector3<T>(data_[0] - rhs[0], data_[1] - rhs[1], data_[2] - rhs[2]);
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::hadamard(const Vector3<T>& rhs)
	{
		data_[0] *= rhs.data_[0];
		data_[1] *= rhs.data_[1];
		data_[2] *= rhs.data_[2];

		return *this;
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::inversed_hadamard(const Vector3<T>& rhs)
	{
		data_[0] /= rhs.data_[0];
		data_[1] /= rhs.data_[1];
		data_[2] /= rhs.data_[2];

		return *this;
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& rhs)
	{
		data_[0] += rhs.data_[0];
		data_[1] += rhs.data_[1];
		data_[2] += rhs.data_[2];

		return *this;
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& rhs)
	{
		data_[0] -= rhs.data_[0];
		data_[1] -= rhs.data_[1];
		data_[2] -= rhs.data_[2];

		return *this;
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator*=(const T scalar)
	{
		data_[0] *= scalar;
		data_[1] *= scalar;
		data_[2] *= scalar;

		return *this;
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator/=(const T scalar)
	{
		data_[0] /= scalar;
		data_[1] /= scalar;
		data_[2] /= scalar;

		return *this;
	}

	template<typename T>
	inline void Vector3<T>::normalize()
	{
		T mag = magnitude();

		data_[0] /= mag;
		data_[1] /= mag;
		data_[2] /= mag;
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::normalized() const
	{
		T mag = magnitude();

		return Vector3<T>(data_[0] / mag, data_[1] / mag, data_[2] / mag);
	}

	template<typename T>
	inline std::ifstream& operator>>(std::ifstream & input, Vector3<T> & rhs)
	{
		input >> rhs[0] >> " " >> rhs[1] >> " " >> rhs[2];

		return input;
	}

	template<typename T>
	inline std::ofstream& operator<<(std::ofstream & output, const Vector3<T> & rhs)
	{
		output << rhs[0] << " " << rhs[1] << " " << rhs[2];

		return output;
	}

	template<typename T>
	std::istream& operator>>(std::istream & input, Vector3<T> & rhs)
	{
		input >> rhs[0] >> " " >> rhs[1] >> " " >> rhs[2];

		return input;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream & output, const Vector3<T> & rhs)
	{
		output << rhs[0] << " " << rhs[1] << " " << rhs[2];

		return output;
	}

	template<typename T>
	Vector3<T> operator*(const T lhs, const Vector3<T>& rhs)
	{
		return rhs * lhs;
	}
}

#endif // !VECTOR3_HPP_