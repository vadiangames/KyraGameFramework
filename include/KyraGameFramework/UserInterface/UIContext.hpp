#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_UICONTEXT_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_UICONTEXT_HPP

#include <KyraGameFramework/UserInterface/Widget.hpp>
#include <list>

namespace kyra {
	
	class UIContext  {
		
		std::list<Widget::Ptr> m_WidgetList;
		
		public:
		UIContext() {}
		~UIContext() {}
		
		void add(Widget::Ptr widget) {
			m_WidgetList.push_back(widget);
		}
		
		void remove(Widget::Ptr widget) {
			m_WidgetList.remove(widget);
		}
		
	};
	
}

#endif