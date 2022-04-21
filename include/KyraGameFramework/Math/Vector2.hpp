#ifndef KYRAGAMEFRAMEWORK_MATH_VECTOR2_HPP
#define KYRAGAMEFRAMEWORK_MATH_VECTOR2_HPP

namespace kyra {
		
	template<class T>
	class Vector2 {
	
		T m_Data[2];
		
		public:
		Vector2() : m_Data{0,0} {}
		Vector2(T x, T y) : m_Data{x,y} {}
		
		void* getData() {
			return &m_Data[0];
		}
		
		T& operator[](size_t index) {
			return m_Data[index];
		}
		
	};
}

#endif