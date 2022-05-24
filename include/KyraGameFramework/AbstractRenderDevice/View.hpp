#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_VIEW_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_VIEW_HPP

#include <array>

namespace kyra {
	
	class View {
		
		std::array<int32_t,4> m_Data;
				
		public:
		View() {}
		View(int32_t x, int32_t y, int32_t width, int32_t height) : m_Data{x,y,width,height} {}
		~View() {}
		
		int32_t getX() const {
			return m_Data[0];
		}
		
		int32_t getY() const {
			return m_Data[1];
		}
		
		int32_t getWidth() const {
			return m_Data[2];
		}
		
		int32_t getHeight() const {
			return m_Data[3];
		}
		
		
	};
	
}


#endif