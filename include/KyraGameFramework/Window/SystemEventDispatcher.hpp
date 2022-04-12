#ifndef KYRAGAMEFRAMEWORK_WINDOW_SYSTEMEVENTDISPATCHER_HPP
#define KYRAGAMEFRAMEWORK_WINDOW_SYSTEMEVENTDISPATCHER_HPP

#include <KyraGameFramework/Window/SystemEventListener.hpp>
#include <list>

namespace kyra {
	
	class KYRA_WINDOW_API SystemEventDispatcher {
	
		std::list<SystemEventListener*> m_Listeners;
	
		public:
		SystemEventDispatcher();
		virtual ~SystemEventDispatcher();
		
		void addListener(SystemEventListener* listener);
		void removeListener(SystemEventListener* listener);
		
		void sendOnCloseEvent();
		void sendOnResizeEvent(uint32_t windowWidth, uint32_t windowHeight);
		void sendOnFocusLostEvent();
		void sendOnFocusGainedEvent();
		void sendOnKeyPressedEvent(size_t key);
		void sendOnKeyReleasedEvent(size_t key);
	};
	
}

#endif