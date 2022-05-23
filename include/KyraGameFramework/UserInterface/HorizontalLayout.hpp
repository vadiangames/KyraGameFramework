#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_HORIZONTALLAYOUT_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_HORIZONTALLAYOUT_HPP

#include <KyraGameFramework/UserInterface/Layout.hpp>

namespace kyra {
	namespace ui {
		
		class HorizontalLayout : public Layout {
			
			
			public:
			HorizontalLayout(IRenderDevice::Ptr renderDevice) : Layout(renderDevice) {}
			virtual ~HorizontalLayout() {}
			
			typedef std::shared_ptr<HorizontalLayout> Ptr;
			
			static std::shared_ptr<HorizontalLayout> create(IRenderDevice::Ptr renderDevice) {
				return std::shared_ptr<HorizontalLayout>(new HorizontalLayout(renderDevice));
			}
			
		
			void recalculate(std::vector<Widget::Ptr>& widgets) final {
				size_t elements = widgets.size();
				float widthPerElement = getSize()[0] / (float)(elements);
				float xpos = getPosition()[0];
				for(Widget::Ptr widget : widgets) {
					widget->setPosition(math::Vector3<float>(xpos, getPosition()[1], 0));
					widget->setSize(math::Vector2<float>(widthPerElement, getSize()[1]));
					xpos += widthPerElement;
				}
			}
			
									
		};
	}
}

#endif