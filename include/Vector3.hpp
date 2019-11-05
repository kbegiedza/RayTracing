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
		Vector3(const T x, const T y, const T z);

		inline T x() const { return data[0]; }
		inline T y() const { return data[1]; }
		inline T z() const { return data[2]; }
		inline T r() const { return data[0]; }
		inline T g() const { return data[1]; }
		inline T b() const { return data[2]; }

		inline const Vector3<T>& operator+() const { return *this; }
		inline Vector3<T> operator-() const { return Vector3<T>(-data[0], -data[1], -data[2]); }
		inline T operator[](const int i) const { return data[i]; }
		inline T& operator[](const int i) { return data[i]; }

		inline Vector3<T>& operator+=(const Vector3<T>& rhs);
		inline Vector3<T>& operator-=(const Vector3<T>& rhs);
		inline Vector3<T>& operator*=(const Vector3<T>& rhs);
		inline Vector3<T>& operator/=(const Vector3<T>& rhs);
		inline Vector3<T>& operator*=(const T scalar);
		inline Vector3<T>& operator/=(const T scalar);

		inline T magnitude() const { return sqrt(squard_magnitude()); }
		inline T squard_magnitude() const { return data[0] * data[0] + data[1] * data[1] + data[2] * data[2]; }
		
		inline void normalize();
		inline Vector3<T> normalized();

		template<typename T>
		friend inline std::ifstream& operator>>(std::ifstream& input, Vector3<T>& rhs);

		template<typename T>
		friend inline std::ofstream& operator<<(std::ofstream& output, const Vector3<T>& rhs);

	private:
		T data[3];
	};

	typedef Vector3<float> Vector3f;
	
	template<typename T>
	inline Vector3<T>::Vector3(const T x, const T y, const T z)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& rhs)
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& rhs)
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& rhs)
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& rhs)
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator*=(const T scalar)
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator/=(const T scalar)
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline void Vector3<T>::normalize()
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::normalized()
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline std::ifstream& operator>>(std::ifstream& input, Vector3<T>& rhs)
	{
		input >> rhs[0] >> " " >> rhs[1] >> " " >> rhs[2];

		return input;
	}
	
	template<typename T>
	inline std::ofstream& operator<<(std::ofstream& output, const Vector3<T>& rhs)
	{
		output << rhs[0] << " " << rhs[1] <<" "<< rhs[2];

		return output;
	}
}

#endif // !VECTOR3_HPP_