#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_LAYOUT_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_LAYOUT_HPP

#include <KyraGameFramework/UserInterface/Widget.hpp>

namespace kyra {
	namespace ui {
		
		class Layout : public Widget {
			
			math::Vector2<float> m_Size;
			math::Vector3<float> m_Position;
			std::vector<Widget::Ptr> m_Widgets;

			protected:
			virtual void recalculate(std::vector<Widget::Ptr>& widgets) = 0;
			
			
			public:
			Layout(IRenderDevice::Ptr renderDevice) : Widget(renderDevice) {}
			virtual ~Layout() {}
			
			size_t getChildCount() const {
				return m_Widgets.size();
			}
			
			constexpr virtual bool hasChildElements() const final {
				return true;
			}
			
			virtual Widget::Ptr getHoveredChild( const math::Vector2<float>& vec) {
				for(auto& widget : m_Widgets) {
					if(widget->contains(vec)) {
						return widget;
					}
				}
				return Widget::Ptr(nullptr);
			}
			
			bool contains( const math::Vector2<float>& vec) const final {
				
				kyra::math::Vector3<float> pos1 = m_Position;
				kyra::math::Vector3<float> pos2 = m_Position + m_Size;

				if( vec.get(0) >= pos1.get(0) && vec.get(0) <= pos2.get(0)) {
					if( vec.get(1) >= pos1.get(1) && vec.get(1) <= pos2.get(1)) {
						return true;
					}				
				}
				
				return false;
			}
					
			
			void setSize( const math::Vector2<float>& size) {
				m_Size = size;
				recalculate(m_Widgets);
			}
			
			math::Vector2<float> getSize() const {
				return m_Size;
			}
			
			void setPosition( const math::Vector3<float>& pos ) {
				m_Position = pos;
				recalculate(m_Widgets);
			}
			
			math::Vector3<float> getPosition() const {
				return m_Position;
			}
						
			void add(Widget::Ptr widget) {
				m_Widgets.push_back(widget);
				recalculate(m_Widgets);
			}
			
			void draw(IRenderDevice& renderDevice) final {
				for(auto& widget : m_Widgets) {
					renderDevice.draw(widget);
				}
			}
			
			
		};
	}
}

#endif