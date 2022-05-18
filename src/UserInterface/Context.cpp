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
		
		void KYRA_USERINTERFACE_API Context::onMouseMoved(uint32_t x, uint32_t y) {
		
			std::list<Widget::Ptr>::iterator hoveredWidget = std::find_if(m_WidgetList.begin(), 
																		  m_WidgetList.end(),
																		  [&](Widget::Ptr widget){
																			return widget->contains(math::Vector2<float>( (float)(x), (float)(y)));
			});
			
			if(m_HoveredWidget != *hoveredWidget) {
				if(m_HoveredWidget) {
					m_HoveredWidget->execute(WidgetEvent::ON_LEAVE);
				}
				m_HoveredWidget = (hoveredWidget == m_WidgetList.end()) ? nullptr : *hoveredWidget;
				if(m_HoveredWidget) {
					m_HoveredWidget->execute(WidgetEvent::ON_HOVER);	
				}
			}
		}
			
		
	}
}