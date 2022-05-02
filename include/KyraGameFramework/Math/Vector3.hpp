#ifndef KYRAGAMEFRAMEWORK_MATH_VECTOR3_HPP
#define KYRAGAMEFRAMEWORK_MATH_VECTOR3_HPP

#include <array>

namespace kyra {
		
	template<class T>
	class Vector3 {
	
		std::array<T,3> m_Data;
		
		public:
		Vector3() : m_Data{0,0,0} {}
		Vector3(T x, T y, T z) : m_Data{x,y,z} {}
		
		void* getData() {
			return &m_Data[0];
		}
		
		T get(size_t index) const {
			return m_Data.at(index);
		}
		
		T& operator[](size_t index) {
			return m_Data[index];
		}
		
		Vector3<T> operator - (const Vector3<float>& vec) const {
			return Vector3<T>( m_Data[0] - vec.m_Data[0], m_Data[1] - vec.m_Data[1],m_Data[2] - vec.m_Data[2]);
		}
		
		Vector3<T> operator + (const Vector3<float>& vec) const {
			return Vector3<T>( m_Data[0] + vec.m_Data[0], m_Data[1] + vec.m_Data[1],m_Data[2] + vec.m_Data[2]);
		}
		
		Vector3<T> operator * (float value) {
			return Vector3<T>( m_Data[0] * value, m_Data[1] * value, m_Data[2] * value);
		}
		
	};
}

#endif