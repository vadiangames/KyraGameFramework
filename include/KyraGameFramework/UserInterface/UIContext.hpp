#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_UICONTEXT_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_UICONTEXT_HPP

#include <KyraGameFramework/UserInterface/Widget.hpp>
#include <KyraGameFramework/Window/SystemEventListener.hpp>
#include <list>

namespace kyra {
	
	namespace ui {
	
		/// \todo rename to Context
		class UIContext : public SystemEventListener {
			
			std::list<Widget::Ptr> m_WidgetList;
			
			public:
			UIContext() {}
			~UIContext() {}
			
			typedef std::list<Widget::Ptr>::iterator Iterator;
			Iterator begin() {return m_WidgetList.begin();}
			Iterator end() {return m_WidgetList.end();}
			
			void add(Widget::Ptr widget) {
				m_WidgetList.push_back(widget);
			}
			
			void remove(Widget::Ptr widget) {
				m_WidgetList.remove(widget);
			}
			
		};
	}
}

#endif