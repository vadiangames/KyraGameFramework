#include <KyraGameFramework/UserInterface/DLL.hpp>
#include <KyraGameFramework/UserInterface/Widget.hpp>
	
namespace kyra	{
	
	namespace ui {
	
		KYRA_USERINTERFACE_API Widget::Widget() {
		
		}
	
		KYRA_USERINTERFACE_API Widget::~Widget() {
		
		}
		
		void KYRA_USERINTERFACE_API Widget::bind( WidgetEvent event, std::function<void()> func) {
			m_FunctionMap[event] = func;
		}
			
		void KYRA_USERINTERFACE_API Widget::execute(WidgetEvent event) {
			if(m_FunctionMap.find(event) != m_FunctionMap.end()) {
				m_FunctionMap[event]();
			}
		}
	
	}

}
