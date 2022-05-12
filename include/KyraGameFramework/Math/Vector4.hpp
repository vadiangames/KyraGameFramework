#ifndef KYRAGAMEFRAMEWORK_MATH_VECTOR4_HPP
#define KYRAGAMEFRAMEWORK_MATH_VECTOR4_HPP

#include <array>

namespace kyra {

	namespace math {
		
		/// \brief Template class for a 4-dimensional vector
		template<class T>
		class Vector4 {
		
			/// \brief The data of the vector
			std::array<T,4> m_Data;
			
			public:
			/// \brief Constructor
			Vector4() : m_Data{0,0,0,0} {}
			
			/// \brief Constructor
			Vector4(T x, T y, T z, T v ) : m_Data{x,y,z,v} {}
			
			/// \brief Returns a pointer to the first element
			void* getData() {
				return &m_Data[0];
			}
			
			/// \brief Returns the element on position index (const)
			/// \todo Make access more safely
			T get(size_t index) const {
				return m_Data.at(index);
			}
			
			
			/// \brief Returns the element on position index
			/// \todo Make access more safely
			T& operator[](size_t index) {
				return m_Data[index];
			}
			
			/// \brief Subtracts the vector vec from the vector
			Vector4<T> operator - (const Vector4<float>& vec) const {
				return Vector4<T>( m_Data[0] - vec.m_Data[0], m_Data[1] - vec.m_Data[1],m_Data[2] - vec.m_Data[2],m_Data[3] - vec.m_Data[3]);
			}
			
			/// \brief Adds the vector vec to the vector
			Vector4<T> operator + (const Vector4<float>& vec) const {
				return Vector4<T>( m_Data[0] + vec.m_Data[0], m_Data[1] + vec.m_Data[1],m_Data[2] + vec.m_Data[2],m_Data[3] + vec.m_Data[3]);
			}
			
			/// \brief Multiplies the vector by value
			Vector4<T> operator * (T value) {
				return Vector4<T>( m_Data[0] * value, m_Data[1] * value, m_Data[2] * value, m_Data[3] * value);
			}
			
		};
	}
}

#endif