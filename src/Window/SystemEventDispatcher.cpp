
#include <KyraGameFramework/Window/SystemEventDispatcher.hpp>
#include <algorithm>

namespace kyra {
	
	KYRA_WINDOW_API SystemEventDispatcher::SystemEventDispatcher() {
	
	}
	
	KYRA_WINDOW_API SystemEventDispatcher::~SystemEventDispatcher() {
	
	}
		
	void KYRA_WINDOW_API SystemEventDispatcher::addListener(SystemEventListener* listener) {
		m_Listeners.push_back(listener);
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::removeListener(SystemEventListener* listener) {
		m_Listeners.remove(listener);
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnCloseEvent() {
		std::for_each(m_Listeners.begin(),m_Listeners.end(), [](SystemEventListener* listener) {
			listener->onClose();
		});
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnResizeEvent(uint32_t windowWidth, uint32_t windowHeight) {
		std::for_each(m_Listeners.begin(),m_Listeners.end(), [&](SystemEventListener* listener) {
			listener->onResize(windowWidth, windowHeight);
		});
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnFocusLostEvent() {
		std::for_each(m_Listeners.begin(),m_Listeners.end(), [](SystemEventListener* listener) {
			listener->onFocusLost();
		});
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnFocusGainedEvent() {
		std::for_each(m_Listeners.begin(),m_Listeners.end(), [](SystemEventListener* listener) {
			listener->onFocusGained();
		});
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnKeyPressedEvent(size_t key) {
		std::for_each(m_Listeners.begin(),m_Listeners.end(), [&](SystemEventListener* listener) {
			listener->onKeyPressed(key);
		});
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnKeyReleasedEvent(size_t key) {
		std::for_each(m_Listeners.begin(),m_Listeners.end(), [&](SystemEventListener* listener) {
			listener->onKeyReleased(key);
		});
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnMouseMovedEvent(int x, int y) {
		std::for_each(m_Listeners.begin(),m_Listeners.end(), [&](SystemEventListener* listener) {
			listener->onMouseMoved(x,y);
		});
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnTextEnteredEvent(char character) {
		std::for_each(m_Listeners.begin(),m_Listeners.end(), [&](SystemEventListener* listener) {
			listener->onTextEntered(character);
		});
	}
	
		
	
	
}