#include <KyraGameFramework/UserInterface/Context.hpp>
#include <KyraGameFramework/Math.hpp>

namespace kyra {
	
	namespace ui {
	
		KYRA_USERINTERFACE_API Context::Context() {
			
		}
		
		KYRA_USERINTERFACE_API Context::~Context() {
			
		}

		Context::Iterator KYRA_USERINTERFACE_API Context::begin() {
			return m_WidgetList.begin();
		}

		Context::Iterator KYRA_USERINTERFACE_API Context::end() {
			return m_WidgetList.end();
		}
			
		void KYRA_USERINTERFACE_API Context::add(Widget::Ptr widget) {
			m_WidgetList.push_back(widget);
		}
			
		void KYRA_USERINTERFACE_API Context::remove(Widget::Ptr widget) {
			m_WidgetList.remove(widget);
		}
		
		/// \todo Can we make this function a little bit nicer?
		void KYRA_USERINTERFACE_API Context::onMouseMoved(uint32_t x, uint32_t y) {
			//Check for a hovered widget
			for(auto& widget : m_WidgetList) {
				if(widget->contains(math::Vector2<float>( (float)(x), (float)(y)))) {
					//Was the hovered widget already hovered, do nothing and leave the function
					if(m_HoveredWidget != widget) {
						if(m_HoveredWidget) {
							m_HoveredWidget->execute(WidgetEvent::ON_LEAVE);
						}
						m_HoveredWidget = widget;
						if(m_HoveredWidget) {
								m_HoveredWidget->execute(WidgetEvent::ON_HOVER);
						}
					}
					return;
				}
			}
			//There is no hovered widget, check if m_HoveredWidget is set and leave it
			if(m_HoveredWidget) {
				m_HoveredWidget->execute(WidgetEvent::ON_LEAVE);
			}
			m_HoveredWidget = Widget::Ptr(nullptr);
		}
		
	}
}