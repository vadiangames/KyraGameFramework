#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_LABEL_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_LABEL_HPP

#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>
#include <KyraGameFramework/RenderDeviceGL/Text.hpp>

namespace kyra {
	
	namespace ui {
	
		class Label : public Widget {
			
			IText::Ptr m_Text;
			
			
			Label(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) : Widget(renderDevice) {
				m_Text = IText::Ptr(new Text());
				m_Text->setText(font, text, *renderDevice);
			}

			public:
			~Label() {}
			
			typedef std::shared_ptr<Label> Ptr;
			
			static Label::Ptr create(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
				return Label::Ptr(new Label(font, text, renderDevice));
			}
			
			constexpr virtual bool hasChildElements() const final {
				return false;
			}
			
			virtual Widget::Ptr getHoveredChild( const math::Vector2<float>& vec) {
				return Widget::Ptr(nullptr);
			}
			
			
			math::Vector2<float> getSize() const final {
				return math::Vector2<float>(0,0);
			}
			
			bool contains(const math::Vector2<float>& vec) const final {
				return false;
			}

			void setPosition(const math::Vector3<float>& vec) {
				m_Text->setPosition(vec);
			}
			
			void setSize(const math::Vector2<float>& vec) {
				
			}
			
			void draw(IRenderDevice& device) final {
				device.draw(m_Text);
			}
		};
	}
}

#endif