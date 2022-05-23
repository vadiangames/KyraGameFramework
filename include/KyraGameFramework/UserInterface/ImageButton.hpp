#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_IMAGEBUTTON_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_IMAGEBUTTON_HPP


#include <KyraGameFramework/UserInterface/Widget.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ISprite.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRectangleShape.hpp>
#include <KyraGameFramework/RenderDeviceGL/Text.hpp>


#include <iostream>

namespace kyra {
	
	namespace ui {
				
		class KYRA_USERINTERFACE_API ImageButton : public Widget {
			
			IText::Ptr m_Text;
			ITexture::Ptr m_Texture;
			ISprite::Ptr m_Sprite;
			
			ImageButton(IFont::Ptr font, const std::string& text, ITexture::Ptr texture, IRenderDevice::Ptr renderDevice);

			public:
			~ImageButton();
			
			typedef std::shared_ptr<ImageButton> Ptr;
			
			constexpr virtual bool hasChildElements() const final {
				return false;
			}
			
			virtual Widget::Ptr getHoveredChild( const math::Vector2<float>& vec) {
				return Widget::Ptr(nullptr);
			}
			
			
			void setPosition(const math::Vector3<float>& position);
			
			void setTexture( ITexture::Ptr texture );
			
			void setSize(const math::Vector2<float>& size);
			
			void setColor(const math::Vector4<float>& color);
			
			math::Vector2<float> getSize() const final;
			
			bool contains(const math::Vector2<float>& vec) const final;
			
			static ImageButton::Ptr create(IFont::Ptr font, const std::string& text, ITexture::Ptr texture, IRenderDevice::Ptr renderDevice);
			
			void draw(IRenderDevice& device) final;
		};
		
	}
}

#endif