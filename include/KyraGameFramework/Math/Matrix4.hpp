#ifndef KYRAGAMEFRAMEWORK_MATH_MATRIX4_HPP
#define KYRAGAMEFRAMEWORK_MATH_MATRIX4_HPP

#include <array>

namespace kyra {
	
	namespace math {
	
		///  \brief a template for 4-dimensional matrices
		///  \todo do we need this as a template or can we use float by default?
		template<class T>
		class Matrix4 {
		
			/// \brief The data of the matrix
			std::array< std::array<T,4> ,4> m_Data;
			
			public:
			/// \brief Constructor, sets identity matrix
			constexpr Matrix4() : m_Data{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1} {}
			
			/// \brief returns the n-th elemen of the matrix, given by the index
			std::array<T,4>& operator[](size_t index) {
				return m_Data[index];
			}
			
			/// \brief returns the value on the position [x,y]
			constexpr T get(size_t x, size_t y) const {
				return m_Data.at(x).at(y);
			}
			
			/// \brief returns the idendity matrix
			static Matrix4 getIdentity() {
				
				
				/**	The Idendity-matrix has to look like the following:
					
					[1][0][0][0]
					[0][1][0][0]
					[0][0][1][0]
					[0][0][0][1]
				
					Multiplying a vector A with the idendity-matrix has to return a vector equal to vector A.
					
					kyra::Vector4<float> vec{1,1,1,1};
					kyra::Vector4<float> vec2 = kyra::Matrix4<float>::getIdendity() * vec;
					ASSERT_EQUAL(vec,vec2)
									
				*/
						
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
			
			/// \brief returns the orthogonal matrix
			static Matrix4<float> getOrtho(float left, float right, float bottom, float top) {
				
				/**
					The Idendity-matrix without near and far-value has to look like the following:
					
					[ 2/(right-left)][			0		][	0	][	-1 * ((right+left) / (right-left)	]
					[		0		][	2/(top-bottom)	][	0	][	-1 * ((top+bottom)/ (top-bottom)	]
					[		0		][			0		][	-1	][					0					]
					[		0		][			0		][	0	][					1					]
				
				*/
				
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

			/// \brief returns the orthogonal matrix - with near and far values
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
			
			/// \brief sets the translation-data of the matrix
			constexpr void translate( const Vector3<T>& vec ) {
				m_Data[3][0] = vec.get(0);
				m_Data[3][1] = vec.get(1);
				m_Data[3][2] = vec.get(2);
			}
			
			/// \brief sets the scaling-data of the matrix
			constexpr void scale( const Vector3<T>& vec ) {
				m_Data[0][0] = vec.get(0);
				m_Data[1][1] = vec.get(1);
				m_Data[2][2] = vec.get(2);
			}
			
			/// \brief returns a pointer to the first element
			T* getData() {
				return &m_Data[0];
			}
			
		};
	}
}

#endif