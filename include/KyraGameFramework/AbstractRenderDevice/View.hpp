#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_VIEW_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_VIEW_HPP

#include <array>
#include <KyraGameFramework/Math/Matrix4.hpp>

namespace kyra {
	
	class View {
		
		std::array<int32_t,4> m_Data;
				
		public:
		View() {}
		View(int32_t x, int32_t y, int32_t width, int32_t height) : m_Data{x,y,width,height} {}
		~View() {}
		
		/// Set the position
		void setPosition(const kyra::math::Vector3<float>& vec) {
			m_Data[0] = (int32_t)(vec.get(0));
			m_Data[1] = (int32_t)(vec.get(1));
		}
		
		/// Set the size
		void setSize(const kyra::math::Vector2<float>& vec) {
			m_Data[2] = (int32_t)(vec.get(0));
			m_Data[3] = (int32_t)(vec.get(1));
		}
		
		/// Returns the x-coordinate
		int32_t getX() const {
			return m_Data[0];
		}
		
		/// Returns the y coordinate
		int32_t getY() const {
			return m_Data[1];
		}
		
		/// Returns the width
		int32_t getWidth() const {
			return m_Data[2];
		}
		
		/// Returns the height
		int32_t getHeight() const {
			return m_Data[3];
		}
		
		
	};
	
}


#endif