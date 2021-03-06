#ifndef KYRAGAMEFRAMEWORK_MATH_VECTOR3_HPP
#define KYRAGAMEFRAMEWORK_MATH_VECTOR3_HPP

#include <KyraGameFramework/Math/Vector2.hpp>

#include <array>

namespace kyra {
	
	namespace math {
		
		
		/// \brief Template class for a 3-dimensional vector
		template<class T>
		class Vector3 {
		
			/// \brief The data of the vector 
			std::array<T,3> m_Data;
			
			public:

#if _MSC_VER == 1800

			//Microsoft Visual Studio 2013 implementation
			Vector3() {
				m_Data[0] = 0;
				m_Data[1] = 0;
				m_Data[2] = 0;
			}
#else 
			/// \brief Constructor
			Vector3() : m_Data{ 0, 0, 0 } {

			}
#endif
			
#if _MSC_VER == 1800

			//Microsoft Visual Studio 2013 implementation

			Vector3(T x, T y, T z) {
				m_Data[0] = x;
				m_Data[1] = y;
				m_Data[2] = z;
			}

#else
			/// \brief The data of the vector
			/// \param x The x-coordinate of the vector
			/// \param y The y-coordinate of the vector
			/// \param z The z-coordinate of the vector

			Vector3(T x, T y, T z) : m_Data{ x, y, z } {}

#endif

			/// \brief Returns a pointer to the first data-element
			void* getData() {
				return &m_Data[0];
			}
			
			/// \brief Returns the data-element on position index (const)
			/// \todo Make the access more safely
			T get(size_t index) const {
				return m_Data.at(index);
			}
			
			/// \brief Returns the data-element on position index
			/// \todo Make the access more safely
			T& operator[](size_t index) {
				return m_Data[index];
			}
			
			/// \brief Subtracts the Vector2<T> vec from the vector
			Vector3<T> operator - (const Vector3<float>& vec) const {
				return Vector3<T>( m_Data[0] - vec.m_Data[0], m_Data[1] - vec.m_Data[1],m_Data[2] - vec.m_Data[2]);
			}
			
			/// \brief Adds the Vector2<T> vec to the vector
			Vector3<T> operator + (const Vector3<float>& vec) const {
				return Vector3<T>( m_Data[0] + vec.m_Data[0], m_Data[1] + vec.m_Data[1],m_Data[2] + vec.m_Data[2]);
			}
			
			Vector3<T> operator + (const Vector2<float>& vec) const {
				return Vector3<T>( m_Data[0] + vec.get(0), m_Data[1] + vec.get(1),m_Data[2]);
			}
			
			/// \brief Multiplies the vector by value
			Vector3<T> operator * (T value) {
				return Vector3<T>( m_Data[0] * value, m_Data[1] * value, m_Data[2] * value);
			}
			
		};
	}
}

#endif