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

		T x() const { return data_[0]; }
		T y() const { return data_[1]; }
		T z() const { return data_[2]; }

		const Vector3<T>& operator+() const { return *this; }
		Vector3<T> operator-() const { return Vector3<T>(-data_[0], -data_[1], -data_[2]); }
		T operator[](const int i) const { return data_[i]; }
		T& operator[](const int i) { return data_[i]; }

		Vector3<T>& hadamard(const Vector3<T> & rhs);
		Vector3<T>& inversed_hadamard(const Vector3<T> & rhs);

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

		T magnitude() const { return sqrt(squard_magnitude()); }
		T squard_magnitude() const { return data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2]; }

		void normalize();
		Vector3<T> normalized() const;

		template<typename T>
		friend std::ifstream& operator>>(std::ifstream & input, Vector3<T> & rhs);

		template<typename T>
		friend std::ofstream& operator<<(std::ofstream & output, const Vector3<T> & rhs);

		template<typename T>
		friend std::istream& operator>>(std::istream & input, Vector3<T> & rhs);

		template<typename T>
		friend std::ostream& operator<<(std::ostream & output, const Vector3<T> & rhs);

		template<typename T>
		friend Vector3<T> operator*(const T lhs, const Vector3<T>& rhs);

	private:
		T data_[3];
	};

	typedef Vector3<float> Vector3f;

	template<typename T>
	Vector3<T>::Vector3()
	{
		data_[0] = 0;
		data_[1] = 0;
		data_[2] = 0;
	}

	template<typename T>
	Vector3<T>::Vector3(const T x, const T y, const T z)
	{
		data_[0] = x;
		data_[1] = y;
		data_[2] = z;
	}

	template<typename T>
	T Vector3<T>::dot(const Vector3<T>& rhs) const
	{
		return data_[0] * rhs[0] + data_[1] * rhs[1] + data_[2] * rhs[2];
	}

	template<typename T>
	Vector3<T> Vector3<T>::cross(const Vector3<T>& rhs) const
	{
		return Vector3<T>(
			data_[1] * rhs.data_[2] - data_[2] * rhs.data_[1],
			data_[2] * rhs.data_[0] - data_[0] * rhs.data_[2],
			data_[0] * rhs.data_[1] - data_[1] * rhs.data_[0]
			);
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
	Vector3<T>& Vector3<T>::inversed_hadamard(const Vector3<T>& rhs)
	{
		data_[0] /= rhs.data_[0];
		data_[1] /= rhs.data_[1];
		data_[2] /= rhs.data_[2];

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
	std::ifstream& operator>>(std::ifstream & input, Vector3<T> & rhs)
	{
		input >> rhs[0] >> " " >> rhs[1] >> " " >> rhs[2];

		return input;
	}

	template<typename T>
	std::ofstream& operator<<(std::ofstream & output, const Vector3<T> & rhs)
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