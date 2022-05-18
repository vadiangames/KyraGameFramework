#include <KyraGameFramework/UserInterface/ImageButton.hpp>

#include <iostream>

namespace kyra {
	
	namespace ui {
		
		KYRA_USERINTERFACE_API ImageButton::ImageButton(IFont::Ptr font, const std::string& text, ITexture::Ptr texture, IRenderDevice::Ptr renderDevice) {
			m_Text = IText::Ptr(new Text());
			m_Text->setText(font, text, *renderDevice);
			m_Texture = texture;
			m_Sprite = renderDevice->createSprite(texture);
		}

		KYRA_USERINTERFACE_API ImageButton::~ImageButton() {
				
		}
			
		void KYRA_USERINTERFACE_API ImageButton::setPosition(const math::Vector3<float>& position){
			m_Sprite->setPosition(position);
			m_Text->setPosition(position);
		}
			
		void KYRA_USERINTERFACE_API ImageButton::setSize(const math::Vector2<float>& size) {
		
		}
		
		void KYRA_USERINTERFACE_API ImageButton::setTexture( ITexture::Ptr texture ) {
			m_Sprite->setTexture(texture);
		}
			
		void KYRA_USERINTERFACE_API ImageButton::setColor(const math::Vector4<float>& color) {
			m_Sprite->setColor(color);
		}
			
		math::Vector2<float> KYRA_USERINTERFACE_API ImageButton::getSize() const {
			return m_Texture->getSize();
		}
			
		bool KYRA_USERINTERFACE_API ImageButton::contains(const math::Vector2<float>& vec) const {
				
			kyra::math::Vector3<float> pos1 = m_Sprite->getPosition();
			kyra::math::Vector3<float> pos2 = m_Sprite->getPosition() + m_Texture->getSize();

			if( vec.get(0) >= pos1.get(0) && vec.get(0) <= pos2.get(0)) {
				if( vec.get(1) >= pos1.get(1) && vec.get(1) <= pos2.get(1)) {
					return true;
				}				
			}
								
			return false;
		}
			
		ImageButton::Ptr KYRA_USERINTERFACE_API ImageButton::create(IFont::Ptr font, const std::string& text, ITexture::Ptr texture, IRenderDevice::Ptr renderDevice) {
			return ImageButton::Ptr(new ImageButton(font, text, texture, renderDevice));;
		} 
			
		void KYRA_USERINTERFACE_API ImageButton::draw(IRenderDevice& device) {
			device.draw(m_Sprite);
			device.draw(m_Text);
		}
		
		
	}
}
