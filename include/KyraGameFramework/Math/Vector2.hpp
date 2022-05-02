#ifndef KYRAGAMEFRAMEWORK_MATH_VECTOR2_HPP
#define KYRAGAMEFRAMEWORK_MATH_VECTOR2_HPP

#include <array>

namespace kyra {
		
	template<class T>
	class Vector2 {
	
		std::array<T,2> m_Data;
		
		public:
		Vector2() : m_Data{0,0} {}
		Vector2(T x, T y) : m_Data{x,y} {}
		
		void* getData() {
			return &m_Data[0];
		}
		
		T get(size_t index) const {
			return m_Data.at(index);
		}
		
		T& operator[](size_t index) {
			return m_Data[index];
		}
		
	};
}

#endif