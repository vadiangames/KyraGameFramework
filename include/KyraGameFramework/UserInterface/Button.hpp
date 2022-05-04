#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_BUTTON_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_BUTTON_HPP

#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ISprite.hpp>


namespace kyra {
	
	class Button : public Widget {
		
		IText::Ptr m_Text;
		
		size_t m_References;
		static IVertexBuffer::Ptr m_VertexBuffer;
		static IVertexLayout::Ptr m_VertexLayout;
		static IProgram::Ptr m_Program;
		static IIndexBuffer::Ptr m_IndexBuffer;
		
		Button(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
			m_Text = IText::Ptr(new Text());
			m_Text->setText(font, text, *renderDevice);
		}

		public:
		~Button() {
			Button::m_References--;
			if(Button::m_References < 1) {
			}
		}
		
		typedef std::shared_ptr<Button> Ptr;
		
		static Button::Ptr create(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
			if(!Button::m_VertexBuffer) {
				
			}
			if(!Button::m_VertexLayout) {
				
			}
			if(!Button::m_Program) {
				
			}
			if(!Button::m_IndexBuffer) {
				
			}
			Button::m_References++;
			Button::Ptr button = Button::Ptr(new Button(font, text, renderDevice));
			return button;
		} 
		
		void draw(IRenderDevice& device) final {
			device.draw(m_Text);
		}
	};
	
	size_t Button::m_References = 0;
	IVertexBuffer::Ptr Button::m_VertexBuffer;
	IVertexLayout::Ptr Button::m_VertexLayout;
	IProgram::Ptr Button::m_Program;
	IIndexBuffer::Ptr Button::m_IndexBuffer;
		
	
	
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
			device.draw(m_Text);
		}
	};
	
}

#endif