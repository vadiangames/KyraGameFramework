#ifndef KYRAGAMEFRAMEWORK_MATH_VECTOR4_HPP
#define KYRAGAMEFRAMEWORK_MATH_VECTOR4_HPP

namespace kyra {
		
	template<class T>
	class Vector4 {
	
		T m_Data[4];
		
		public:
		Vector4() : m_Data{0,0,0,0} {}
		Vector4(T x, T y, T z, T v ) : m_Data{x,y,z,v} {}
		
		void* getData() {
			return &m_Data[0];
		}
		
		T& operator[](size_t index) {
			return m_Data[index];
		}
		
	};
}

#endif