#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_VERTICALLAYOUT_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_VERTICALLAYOUT_HPP

#include <KyraGameFramework/UserInterface/Layout.hpp>

namespace kyra {
	namespace ui {
		
		class VerticalLayout : public Layout {
			
			
			public:
			VerticalLayout(IRenderDevice::Ptr renderDevice) : Layout(renderDevice) {}
			virtual ~VerticalLayout() {}
			
			typedef std::shared_ptr<VerticalLayout> Ptr;
			
			static std::shared_ptr<VerticalLayout> create(IRenderDevice::Ptr renderDevice) {
				return std::shared_ptr<VerticalLayout>(new VerticalLayout(renderDevice));
			}
						
			void recalculate(std::vector<Widget::Ptr>& widgets) final {
				size_t elements = widgets.size();
				float heightPerElement = getSize()[1] / (float)(elements);
				float ypos = getPosition()[1];
				for(Widget::Ptr widget : widgets) {
					widget->setPosition(math::Vector3<float>(getPosition()[0], ypos, 0));
					widget->setSize(math::Vector2<float>(getSize()[0], heightPerElement));
					ypos += heightPerElement;
				}
			}
			
									
		};
	}
}

#endif