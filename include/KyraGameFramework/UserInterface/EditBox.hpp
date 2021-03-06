#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_EDITBOX_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_EDITBOX_HPP


#include <KyraGameFramework/UserInterface/DLL.hpp>
#include <KyraGameFramework/UserInterface/Widget.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRectangleShape.hpp>
#include <KyraGameFramework/RenderDeviceGL/Text.hpp>


#include <iostream>

namespace kyra {
	
	namespace ui {
				
		class KYRA_USERINTERFACE_API EditBox : public Widget {
			
			IFont::Ptr m_Font;
			IText::Ptr m_Text;
			IRectangleShape::Ptr m_Shape;
			IRenderDevice::Ptr m_RenderDevice;
			
			EditBox(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice);

			public:
			~EditBox();
			
			virtual void onTextEntered( char character ) final {
				std::string text = m_Text->getText();
				switch(character) {
					case 0x08: // Backspace
						if(text.size() > 0) {
							text.pop_back();
						}
					break;
					case 0x0D: // Carriage return
						return;
					case 0x09:
						return;
					default:
						text = text + character;
				}
				m_Text->setText( m_Font, text, *(getRenderDevice()) );
			}
			
			constexpr virtual bool hasChildElements() const final {
				return false;
			}
			
			virtual Widget::Ptr getHoveredChild( const math::Vector2<float>& vec) final {
				return Widget::Ptr(nullptr);
			}
			
			
			typedef std::shared_ptr<EditBox> Ptr;
			
			void setPosition(const math::Vector3<float>& position) final;
			
			void setSize(const math::Vector2<float>& size) final;
			
			void setColor(const math::Vector4<float>& color);
			
			math::Vector2<float> getSize() const final;
			
			bool contains(const math::Vector2<float>& vec) const final;
			
			static EditBox::Ptr create(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice);
			
			void draw(IRenderDevice& device) final;
		};
		
	}
}

#endif