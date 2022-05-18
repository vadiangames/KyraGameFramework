#ifndef KYRAGAMEFRAMEWORK_WINDOW_SYSTEMEVENTLISTENER_HPP
#define KYRAGAMEFRAMEWORK_WINDOW_SYSTEMEVENTLISTENER_HPP

#include <KyraGameFramework/Window/DLL.hpp>
#include <cstdint>


namespace kyra {
	
	class KYRA_WINDOW_API SystemEventListener {
	
		public:
		SystemEventListener();
		virtual ~SystemEventListener();
		
		virtual void onClose();
		virtual void onResize( uint32_t windowWidth, uint32_t windowHeight );
		virtual void onFocusLost();
		virtual void onFocusGained();
		virtual void onKeyPressed(size_t key);
		virtual void onKeyReleased(size_t key);
		virtual void onTextEntered(char character);
		virtual void onMouseMoved( uint32_t x, uint32_t y);
		virtual void onMouseWheelMoved();
		virtual void onMouseButtonPressed();
		virtual void onMouseButtonReleased();
		
	};
	
}

#endif