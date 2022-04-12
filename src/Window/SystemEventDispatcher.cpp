
#include <KyraGameFramework/Window/SystemEventDispatcher.hpp>

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
		for(auto& listener : m_Listeners) {
			listener->onClose();
		}
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnResizeEvent(uint32_t windowWidth, uint32_t windowHeight) {
		for(auto& listener : m_Listeners) {
			listener->onResize(windowWidth, windowHeight);
		}
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnFocusLostEvent() {
		for(auto& listener : m_Listeners) {
			listener->onFocusLost();
		}
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnFocusGainedEvent() {
		for(auto& listener : m_Listeners) {
			listener->onFocusGained();
		}
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnKeyPressedEvent(size_t key) {
		for(auto& listener : m_Listeners) {
			listener->onKeyPressed(key);
		}
	}
	
	void KYRA_WINDOW_API SystemEventDispatcher::sendOnKeyReleasedEvent(size_t key) {
		for(auto& listener : m_Listeners) {
			listener->onKeyReleased(key);
		}
	}
	
	
}