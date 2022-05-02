#ifndef KYRAGAMEFRAMEWORK_MATH_VECTOR4_HPP
#define KYRAGAMEFRAMEWORK_MATH_VECTOR4_HPP

#include <array>

namespace kyra {
		
	template<class T>
	class Vector4 {
	
		std::array<T,4> m_Data;
		
		public:
		Vector4() : m_Data{0,0,0,0} {}
		Vector4(T x, T y, T z, T v ) : m_Data{x,y,z,v} {}
		
		void* getData() {
			return &m_Data[0];
		}
		
		T get(size_t index) const {
			return m_Data.at(index);
		}
		
		
		T& operator[](size_t index) {
			return m_Data[index];
		}
		
		Vector4<T> operator - (const Vector4<float>& vec) const {
			return Vector4<T>( m_Data[0] - vec.m_Data[0], m_Data[1] - vec.m_Data[1],m_Data[2] - vec.m_Data[2],m_Data[3] - vec.m_Data[3]);
		}
		
		Vector4<T> operator + (const Vector4<float>& vec) const {
			return Vector4<T>( m_Data[0] + vec.m_Data[0], m_Data[1] + vec.m_Data[1],m_Data[2] + vec.m_Data[2],m_Data[3] + vec.m_Data[3]);
		}
		
		Vector4<T> operator * (float value) {
			return Vector4<T>( m_Data[0] * value, m_Data[1] * value, m_Data[2] * value, m_Data[3] * value);
		}
		
	};
}

#endif