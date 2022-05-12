#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>
#include <KyraGameFramework/RenderDeviceGL/Font.hpp>
#include <KyraGameFramework/RenderDeviceGL/Text.hpp>

class MyApplication : public kyra::SystemEventListener {

	kyra::Window m_Window;
	kyra::RenderDeviceGL m_Renderer;
	
	public:
	MyApplication() {
	}
	
	~MyApplication() {
	}
	
	
	//! Implementation of kyra::SystemEventListener::onClose()
	virtual void onClose() {
		m_Window.close();
	}
		
	void run() {
		kyra::WindowSettings windowSettings;
			windowSettings.width = 800;
			windowSettings.height = 600;
			windowSettings.title = L"KyraGameFramework - Window - 05_FontRendering";
		
		if(m_Window.create(windowSettings)) {
			
			m_Window.addListener(this);
			
			if(m_Renderer.create(m_Window)) {
				
				kyra::IFont::Ptr font = kyra::IFont::Ptr(new kyra::Font());
				font->loadFromFile("Antonio-Regular.ttf",18);
			
				kyra::IText::Ptr txt = kyra::IText::Ptr(new kyra::Text());
				txt->setPosition(kyra::math::Vector3<float>(0,0,0));
				txt->setText(font, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", m_Renderer);
				
				kyra::IText::Ptr txt2 = kyra::IText::Ptr(new kyra::Text());
				txt2->setText(font, "abcdefghjklmnopqrstuvwxyz;:_+*ç%&/()=?{}[]", m_Renderer);
				txt2->setPosition(kyra::math::Vector3<float>(0,60,0));
				
				while(m_Window.isOpen()) {
					m_Window.processEvents();
					m_Renderer.clear();
						m_Renderer.draw(txt);
						m_Renderer.draw(txt2);
					m_Renderer.display();
				}
			}
					
		}

	}

};

int main(int argc, char** argv) {

	MyApplication().run();
	
	return 0;
}