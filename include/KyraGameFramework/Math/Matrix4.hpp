#ifndef KYRAGAMEFRAMEWORK_MATH_MATRIX4_HPP
#define KYRAGAMEFRAMEWORK_MATH_MATRIX4_HPP

namespace kyra {
		
	template<class T>
	class Matrix4 {
	
		T m_Data[4][4];
		
		public:
		Matrix4() : m_Data{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1} {}
		
		void* getData() {
			return &m_Data[0];
		}
		
		T& operator[](size_t index) {
			return m_Data[index];
		}
		
		static Matrix4 getIdentity() {
			
			Matrix4 matrix;
			matrix.m_Data[0][0] = 1;
			matrix.m_Data[0][1] = 0;
			matrix.m_Data[0][2] = 0;
			matrix.m_Data[0][3] = 0;
			
			matrix.m_Data[1][0] = 0;
			matrix.m_Data[1][1] = 1;
			matrix.m_Data[1][2] = 0;
			matrix.m_Data[1][3] = 0;
			
			matrix.m_Data[2][0] = 0;
			matrix.m_Data[2][1] = 0;
			matrix.m_Data[2][2] = 1;
			matrix.m_Data[2][3] = 0;
			
			matrix.m_Data[3][0] = 0;
			matrix.m_Data[3][1] = 0;
			matrix.m_Data[3][2] = 0;
			matrix.m_Data[3][3] = 1;
					
			return matrix;
		}
		
		
		T* getData() {
			return &m_Data[0];
		}
		
	};
}

#endif