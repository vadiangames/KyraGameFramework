#include <KyraGameFramework/UserInterface/Context.hpp>
#include <KyraGameFramework/Math.hpp>
#include <iostream>

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
			std::list<Widget::Ptr>::iterator hoveredWidgetIt = std::find_if(m_WidgetList.begin(), 
																		  m_WidgetList.end(),
																		  [&](Widget::Ptr widget){
																			return widget->contains(math::Vector2<float>( (float)(x), (float)(y)));
			});
			
			Widget::Ptr hoveredWidget = Widget::Ptr(nullptr);
			if(hoveredWidgetIt != m_WidgetList.end()) {
				hoveredWidget = *(hoveredWidgetIt);
			}
			
			if( (hoveredWidget) ) {
				if( hoveredWidget->hasChildElements()) {
					hoveredWidget = hoveredWidget->getHoveredChild(math::Vector2<float>( (float)(x), (float)(y)));
				}
			}
			
			if(m_HoveredWidget != hoveredWidget) {
				if(m_HoveredWidget) {
					m_HoveredWidget->execute(WidgetEvent::ON_LEAVE);
				}
				m_HoveredWidget = hoveredWidget;
				if(m_HoveredWidget) {
					m_HoveredWidget->execute(WidgetEvent::ON_HOVER);	
				}
			}
		}
		
		void KYRA_USERINTERFACE_API Context::onMouseButtonPressed() {
			
		}
		
		void KYRA_USERINTERFACE_API Context::onMouseButtonReleased() {
			if(m_ActiveWidget == m_HoveredWidget) {
				return;
			}
			if(m_ActiveWidget) {
				m_ActiveWidget->execute(kyra::ui::WidgetEvent::ON_DEACTIVATE);
			}
			m_ActiveWidget = m_HoveredWidget;
			if(m_ActiveWidget) {
				m_ActiveWidget->execute(kyra::ui::WidgetEvent::ON_ACTIVATE);
			}
		}
		
		void KYRA_USERINTERFACE_API Context::onTextEntered(char character) {
			if(m_ActiveWidget) {
				if(character == 0x0D) {
					m_ActiveWidget->execute(kyra::ui::WidgetEvent::ON_DEACTIVATE);
					m_ActiveWidget = Widget::Ptr(nullptr);
					return;
				}
				m_ActiveWidget->onTextEntered(character);
			}
		}
			
		
	}
}