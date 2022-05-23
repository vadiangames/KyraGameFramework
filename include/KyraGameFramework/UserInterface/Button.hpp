#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_BUTTON_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_BUTTON_HPP


#include <KyraGameFramework/UserInterface/DLL.hpp>
#include <KyraGameFramework/UserInterface/Widget.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ISprite.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRectangleShape.hpp>
#include <KyraGameFramework/RenderDeviceGL/Text.hpp>


#include <iostream>

namespace kyra {
	
	namespace ui {
				
		class KYRA_USERINTERFACE_API Button : public Widget {
			
			IText::Ptr m_Text;
			IRectangleShape::Ptr m_Shape;
						
			Button(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice);

			public:
			~Button();
			
			typedef std::shared_ptr<Button> Ptr;
			
			constexpr virtual bool hasChildElements() const final {
				return false;
			}
			
			virtual Widget::Ptr getHoveredChild( const math::Vector2<float>& vec) {
				return Widget::Ptr(nullptr);
			}
			
			
			void setPosition(const math::Vector3<float>& position);
			
			void setSize(const math::Vector2<float>& size);
			
			void setColor(const math::Vector4<float>& color);
			
			math::Vector2<float> getSize() const final;
			
			bool contains(const math::Vector2<float>& vec) const final;
			
			static Button::Ptr create(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice);
			
			void draw(IRenderDevice& device) final;
		};
		
	}
}

#endif