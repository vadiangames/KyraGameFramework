#ifndef KYRAGAMEFRAMEWORK_MATH_MATRIX4_HPP
#define KYRAGAMEFRAMEWORK_MATH_MATRIX4_HPP

#include <array>

namespace kyra {
	
	template<class T>
	class Matrix4 {
	
		std::array< std::array<T,4> ,4> m_Data;
		
		public:
		Matrix4() : m_Data{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1} {}
		
		std::array<T,4>& operator[](size_t index) {
			return m_Data[index];
		}
		
		T get(size_t x, size_t y) const {
			return m_Data.at(x).at(y);
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
		
		static Matrix4<float> getOrtho(float left, float right, float bottom, float top) {
			
			Matrix4<float> matrix;
			
			matrix.m_Data[0][0] = 2.0f / (right-left);
			matrix.m_Data[0][1] = 0;
			matrix.m_Data[0][2] = 0;
			matrix.m_Data[0][3] = 0;
			
			matrix.m_Data[1][0] = 0;
			matrix.m_Data[1][1] = 2.0f / (top - bottom);
			matrix.m_Data[1][2] = 0;
			matrix.m_Data[1][3] = 0;
			
			matrix.m_Data[2][0] = 0;
			matrix.m_Data[2][1] = 0;
			matrix.m_Data[2][2] = -1.0f;
			matrix.m_Data[2][3] = 0;
			
			matrix.m_Data[3][0] = -1 * ((right+left) / (right-left));
			matrix.m_Data[3][1] = -1 * ((top+bottom)/ (top-bottom));
			matrix.m_Data[3][2] = 0;
			matrix.m_Data[3][3] = 1;
					
			return matrix;
		}

		static Matrix4<float> getOrtho(float left, float right, float bottom, float top, float near_val, float far_val) {
			
			Matrix4<float> matrix;
			
			matrix.m_Data[0][0] = 2.0f / (right-left);
			matrix.m_Data[0][1] = 0;
			matrix.m_Data[0][2] = 0;
			matrix.m_Data[0][3] = 0;
			
			matrix.m_Data[1][0] = 0;
			matrix.m_Data[1][1] = 2.0f / (top - bottom);
			matrix.m_Data[1][2] = 0;
			matrix.m_Data[1][3] = 0;
			
			matrix.m_Data[2][0] = 0;
			matrix.m_Data[2][1] = 0;
			matrix.m_Data[2][2] = 2.0f / (far_val - near_val);
			matrix.m_Data[2][3] = 0;
			
			matrix.m_Data[3][0] = -1 * ((right+left) / (right-left));
			matrix.m_Data[3][1] = -1 * ((top+bottom)/(top-bottom));
			matrix.m_Data[3][2] = -1 * ((far_val+near_val)/(far_val-near_val));
			matrix.m_Data[3][3] = 1;
					
			return matrix;
		}		
		
		void translate( const kyra::Vector3<T>& vec ) {
			m_Data[3][0] = vec.get(0);
			m_Data[3][1] = vec.get(1);
			m_Data[3][2] = vec.get(2);
		}
		
		void scale( const kyra::Vector3<T>& vec ) {
			m_Data[0][0] = vec.get(0);
			m_Data[1][1] = vec.get(1);
			m_Data[2][2] = vec.get(2);
		}
		
		T* getData() {
			return &m_Data[0];
		}
		
	};
}

#endif