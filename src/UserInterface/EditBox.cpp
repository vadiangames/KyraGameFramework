#include <KyraGameFramework/UserInterface/EditBox.hpp>

#include <iostream>

namespace kyra {
	
	namespace ui {
		
		KYRA_USERINTERFACE_API EditBox::EditBox(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) : Widget(renderDevice), m_Font(font), m_Text(IText::Ptr(new Text())){
			m_Text->setText(font, text, *renderDevice);
			m_Shape = renderDevice->createRectangleShape(math::Vector3(0.0f, 0.0f,0.0f), math::Vector2(0.0f,0.0f));
		}

		KYRA_USERINTERFACE_API EditBox::~EditBox() {
				
		}
			
		void KYRA_USERINTERFACE_API EditBox::setPosition(const math::Vector3<float>& position){
			m_Shape->setPosition(position);
			m_Text->setPosition(position);
		}
			
		void KYRA_USERINTERFACE_API EditBox::setSize(const math::Vector2<float>& size) {
			m_Shape->setSize(size);
		}
			
		void KYRA_USERINTERFACE_API EditBox::setColor(const math::Vector4<float>& color) {
			m_Shape->setColor(color);
		}
			
		math::Vector2<float> KYRA_USERINTERFACE_API EditBox::getSize() const {
			return m_Shape->getSize();
		}
			
		bool KYRA_USERINTERFACE_API EditBox::contains(const math::Vector2<float>& vec) const {
				
			kyra::math::Vector3<float> pos1 = m_Shape->getPosition();
			kyra::math::Vector3<float> pos2 = m_Shape->getPosition() + m_Shape->getSize();

			if( vec.get(0) >= pos1.get(0) && vec.get(0) <= pos2.get(0)) {
				if( vec.get(1) >= pos1.get(1) && vec.get(1) <= pos2.get(1)) {
					return true;
				}				
			}
								
			return false;
		}
			
		EditBox::Ptr KYRA_USERINTERFACE_API EditBox::create(IFont::Ptr font, const std::string& text, IRenderDevice::Ptr renderDevice) {
			return EditBox::Ptr(new EditBox(font, text, renderDevice));;
		} 
			
		void KYRA_USERINTERFACE_API EditBox::draw(IRenderDevice& device)  {
			device.draw(m_Shape);
			device.draw(m_Text);
		}
		
		
	}
}
