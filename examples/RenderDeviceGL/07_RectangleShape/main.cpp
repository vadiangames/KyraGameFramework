
#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>
#include <KyraGameFramework/RenderDeviceGL/RectangleShape.hpp>


class MyApplication : public kyra::SystemEventListener {
	
	kyra::Window m_Window;
	kyra::RenderDeviceGL m_Renderer;
	kyra::IRectangleShape::Ptr m_Shape;
	
	public:
	MyApplication() {}
	~MyApplication() {}
	
	virtual void onClose() {
		m_Window.close();
	}
	
	void run() {
		
		kyra::WindowSettings windowSettings;
		windowSettings.width = 800;
		windowSettings.height = 600;
		windowSettings.title = L"KyraGameFramework - Camera Example";
				
		if(!m_Window.create(windowSettings)) {
			return;
		}
		
		m_Window.addListener(this);
		
		if(!m_Renderer.create(m_Window)) {
			return;
		}
		
		m_Shape = kyra::IRectangleShape::Ptr( new kyra::RectangleShape() );
		m_Shape->create(m_Renderer);
			m_Shape->setSize( kyra::math::Vector2<float>(100.0f,100.0f) );
			m_Shape->setPosition( kyra::math::Vector3<float>(10.f,10.f,0.0f));
			m_Shape->setColor( kyra::math::Vector4<float>(1.0f,1.0f,0.0f,0.5f));
				
		while(m_Window.isOpen()) {
			m_Window.processEvents();
			m_Renderer.clear();
				m_Renderer.draw(m_Shape);
			m_Renderer.display();
		}
		
	}
	
};


int main(int argc, char** argv) {
	
	MyApplication().run();
	
	return 0;
}