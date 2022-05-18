#ifndef KYRAGAMEFRAMEWORK_MATH_VECTOR2_HPP
#define KYRAGAMEFRAMEWORK_MATH_VECTOR2_HPP

#include <array>

namespace kyra {

	namespace math {
		
		/// \brief Template class for 2-dimensional vector
		template<class T>
		class Vector2 {
			
			/// \brief The data of the vector
			std::array<T,2> m_Data;
			
			public:
			/// \brief Constructor

#if _MSC_VER == 1800
			Vector2() {
				m_Data[0] = 0;
				m_Data[1] = 0;
			}
#else
			Vector2() : m_Data{ 0, 0 } {

			}
#endif
			

#if _MSC_VER == 1800

			Vector2(T x, T y)  {
				m_Data[0] = x;
				m_Data[1] = y;
			}


#else
			/// \brief Constructor
			/// \param x The x coordinate of the vector
			/// \param y The y coordinate of the vector
			Vector2(T x, T y) : m_Data{ x, y } {

			}

#endif	

			/// \brief Returns a poiner to the first data-element
			void* getData() {
				return &m_Data[0];
			}
			
			/// \brief Returns the data of the index (const)
			/// \todo Make access more safe
			T get(size_t index) const {
				return m_Data.at(index);
			}
						
			/// \brief Returns the data of the index
			/// \todo Make access more safe			
			T& operator[](size_t index) {
				return m_Data[index];
			}
			
			/// \brief Addition of the two vectors
			/// \param vec The Vector to add
			Vector2<T> operator + (const Vector2<T>& vec) const {
				return Vector2<T>(m_Data.at(0) + vec.m_Data.at(0), m_Data.at(1) + vec.m_Data.at(1) );
			}
			
		};

	}
}

#endif