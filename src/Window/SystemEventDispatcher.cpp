
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
	
}