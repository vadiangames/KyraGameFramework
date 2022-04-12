
#include <KyraGameFramework/Window/Windows/WindowWin32.hpp>
#include <KyraGameFramework/Window/SystemEventListener.hpp>

#include <iostream>

class MyApplication : public kyra::SystemEventListener {

	kyra::Window window;
	
	public:
	MyApplication() {}
	~MyApplication() {}
	
	
	//! Implementation of kyra::SystemEventListener::onClose()
	virtual void onClose() {
		window.close();
	}
	
	//! Implementation of kyra::SystemEventListener::onResize()
	virtual void onResize(uint32_t windowWidth, uint32_t windowHeight) {
		std::cout << "New window size: " << windowWidth << " " << windowHeight << std::endl;
	}

	void run() {
	
		kyra::WindowSettings windowSettings;
		windowSettings.width = 800;
		windowSettings.height = 600;
		windowSettings.title = L"KyraGameFramework - Window - 01_Hello World";
		
		if(window.create(windowSettings)) {
			
			window.addListener(this);
			
			while(window.isOpen()) {
				window.processEvents();
			}

		}
		
	}

};

int main(int argc, char** argv) {
	
	MyApplication().run();
	
	return 0;
}