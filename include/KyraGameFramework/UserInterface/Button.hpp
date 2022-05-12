#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_BUTTON_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_BUTTON_HPP

#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ISprite.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRectangleShape.hpp>



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
			
			static Button::Ptr create(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
				Button::Ptr button = Button::Ptr(new Button(font, text, renderDevice));
				return button;
			} 
			
			void draw(IRenderDevice& device) final {
				device.draw(m_Shape);
				device.draw(m_Text);
			}
		};
		
		class ImageButton : public Widget {
			
			IText::Ptr m_Text;
			ISprite::Ptr m_Sprite;
			
			ImageButton(ISprite::Ptr sprite, IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
				m_Text = IText::Ptr(new Text());
				m_Text->setText(font, text, *renderDevice);
			}

			public:
			~ImageButton() {}
			
			typedef std::shared_ptr<ImageButton> Ptr;
			
			static ImageButton::Ptr create(ISprite::Ptr sprite, IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
				ImageButton::Ptr button = ImageButton::Ptr(new ImageButton(sprite,font, text, renderDevice));
				return button;
			} 
			
			void draw(IRenderDevice& device) final {
				device.draw(m_Sprite);
				//device.draw(m_Text);
			}
		};
	}
}

#endif