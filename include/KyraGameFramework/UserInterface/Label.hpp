#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_LABEL_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_LABEL_HPP

#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>

namespace kyra {
	
	namespace ui {
	
		class Label : public Widget {
			
			IText::Ptr m_Text;
			
			
			Label(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
				m_Text = IText::Ptr(new Text());
				m_Text->setText(font, text, *renderDevice);
			}

			public:
			~Label() {}
			
			typedef std::shared_ptr<Label> Ptr;
			
			static Label::Ptr create(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
				Label::Ptr label = Label::Ptr(new Label(font, text, renderDevice));
				return label;
			}

			void setPosition(const math::Vector3<float>& vec) {
				m_Text->setPosition(vec);
			}
			
			void draw(IRenderDevice& device) final {
				device.draw(m_Text);
			}
		};
	}
}

#endif