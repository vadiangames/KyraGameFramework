#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_BUTTON_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_BUTTON_HPP


#include <KyraGameFramework/UserInterface/Widget.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ISprite.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRectangleShape.hpp>
#include <KyraGameFramework/RenderDeviceGL/Text.hpp>


#include <iostream>

namespace kyra {
	
	namespace ui {
		
		
		class Button : public Widget {
			
			IText::Ptr m_Text;
			IRectangleShape::Ptr m_Shape;
			
			
			Button(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
				m_Text = IText::Ptr(new Text());
				m_Text->setText(font, text, *renderDevice);
				m_Shape = renderDevice->createRectangleShape(math::Vector3(0.0f, 0.0f,0.0f), math::Vector2(0.0f,0.0f));
			}

			public:
			~Button() {
				
			}
			
			typedef std::shared_ptr<Button> Ptr;
			
			void setPosition(const math::Vector3<float>& position){
				m_Shape->setPosition(position);
				m_Text->setPosition(position);
			}
			
			void setSize(const math::Vector2<float>& size) {
				m_Shape->setSize(size);
			}
			
			void setColor(const math::Vector4<float>& color) {
				m_Shape->setColor(color);
			}
			
			math::Vector2<float> getSize() const final {
				return m_Shape->getSize();
			}
			
			bool contains(const math::Vector2<float>& vec) const final {
				
				kyra::math::Vector3<float> pos1 = m_Shape->getPosition();
				kyra::math::Vector3<float> pos2 = m_Shape->getPosition() + m_Shape->getSize();

				if( vec.get(0) >= pos1.get(0) && vec.get(0) <= pos2.get(0)) {
					if( vec.get(1) >= pos1.get(1) && vec.get(1) <= pos2.get(1)) {
						return true;
					}				
				}
								
				return false;
			}
			
			static Button::Ptr create(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
				return Button::Ptr(new Button(font, text, renderDevice));;
			} 
			
			void draw(IRenderDevice& device) final {
				device.draw(m_Shape);
				device.draw(m_Text);
			}
		};
		
	}
}

#endif