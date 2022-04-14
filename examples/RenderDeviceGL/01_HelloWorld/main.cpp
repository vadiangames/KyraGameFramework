#include <KyraGameFramework/Window/Windows/WindowWin32.hpp>
#include <KyraGameFramework/Window/SystemEventListener.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGl.hpp>


class MyApplication : public kyra::SystemEventListener {

	kyra::Window m_Window;
	kyra::RenderDeviceGL m_Renderer;
	
	public:
	MyApplication() {}
	~MyApplication() {}
	
	
	//! Implementation of kyra::SystemEventListener::onClose()
	virtual void onClose() final {
		m_Window.close();
	}
		
	void run() {
	
		kyra::WindowSettings windowSettings;
		windowSettings.width = 800;
		windowSettings.height = 600;
		windowSettings.title = L"KyraGameFramework - Window - 01_Hello World";
		
		if(m_Window.create(windowSettings)) {
			
			m_Window.addListener(this);
			
			if(m_Renderer.create(m_Window)) {
				while(m_Window.isOpen()) {
					m_Window.processEvents();
					m_Renderer.clear();
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