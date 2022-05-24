#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_LISTBOX_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_LISTBOX_HPP

#include <vector>
#include <KyraGameFramework/UserInterface/Widget.hpp>

namespace kyra {
	namespace ui {
		
		class ListBox : public Widget {
			
			std::vector<Widget::Ptr> m_Widgets;
			View m_View;
			
			math::Vector2<float> m_RowSize;
			
			void recalculate() {
				
			}
			
			public:
			ListBox() {
				
			}
			
			~ListBox() {
				
			}
			
			void setRowSize(const math::Vector2<float>& vec) {
				m_RowSize = vec;
				recalculate();
			}
			
			void add(Widget::Ptr widget) {
				m_Widgets.push_back(widget);
				recalculate();
			}
			
			void draw(IRenderDevice& renderDevice) final {
				View view = renderDevice.getView();
				
				for(auto& widget : m_Widgets) {
					renderDevice.draw(widget);
				}				
				
				renderDevice.setView(m_View);
				renderDevice.setView(view);
			}			
			
		};
	}
}

#endif