#ifndef KYRAGAMEFRAMEWORK_MATH_VECTOR3_HPP
#define KYRAGAMEFRAMEWORK_MATH_VECTOR3_HPP

namespace kyra {
		
	template<class T>
	class Vector3 {
	
		T m_Data[3];
		
		public:
		Vector3() : m_Data{0,0,0} {}
		Vector3(T x, T y, T z) : m_Data{x,y,z} {}
		
		void* getData() {
			return &m_Data[0];
		}
		
		T& operator[](size_t index) {
			return m_Data[index];
		}
		
	};
}

#endif