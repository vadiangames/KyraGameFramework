#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_UICONTEXT_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_UICONTEXT_HPP

#include <KyraGameFramework/UserInterface/Widget.hpp>
#include <KyraGameFramework/Window/SystemEventListener.hpp>


#include <list>

namespace kyra {
	
	namespace ui {
	
		class KYRA_USERINTERFACE_API Context : public SystemEventListener {
			
			/// \brief List of all widgets registered to this context
			std::list<Widget::Ptr> m_WidgetList;
			
			/// \brief The active widget 
			Widget::Ptr m_ActiveWidget;
			
			/// \brief The hovered widget
			Widget::Ptr m_HoveredWidget;
	
			public:
			Context();
			virtual ~Context();
			
			/// \brief Typedefinition for the widget-iterator
			typedef std::list<Widget::Ptr>::iterator Iterator;
			
			/// \brief Returns the iterator to the first widget
			Iterator begin();
			
			/// \brief Returns the iterator to the last widget
			Iterator end();
			
			/// \brief Add a widget to the context
			void add(Widget::Ptr widget);
			
			/// \brief Remvoe the widget from the context
			void remove(Widget::Ptr widget);
			
			/// \brief Handle the onMouseMoved-Event
			void onMouseMoved(uint32_t x, uint32_t y) final;
			
		};
	}
}

#endif