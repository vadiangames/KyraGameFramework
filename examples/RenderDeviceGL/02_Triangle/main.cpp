#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>
#include <KyraGameFramework/RenderDeviceGL/Shader.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>
#include <KyraGameFramework/Math/Vector3.hpp>
#include <KyraGameFramework/Graphics/VertexArray.hpp>

#include <iostream>

std::string vertexShaderSrc = "#version 330 core\n"
							  "layout (location = 0) in vec3 aPos;\n"
							  "void main()\n"
							  "{\n"
							  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
							  "}";
							  
std::string fragmentShaderSrc = "#version 330 core\n"
								"out vec4 FragColor;\n"
								"void main()\n"
								"{\n"
								"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
								"}\n"; 


typedef struct {
	kyra::Vector3<float> position;
}Vertex;
								
class MyApplication : public kyra::SystemEventListener {

	kyra::Window m_Window;
	kyra::RenderDeviceGL m_Renderer;
	
	public:
	MyApplication() {}
	~MyApplication() {}
	
	
	//! Implementation of kyra::SystemEventListener::onClose()
	virtual void onClose() {
		m_Window.close();
	}
		
	void run() {
		
		kyra::WindowSettings windowSettings;
		windowSettings.width = 800;
		windowSettings.height = 600;
		windowSettings.title = L"KyraGameFramework - Window - 02_Triangle";
		
		if(m_Window.create(windowSettings)) {
			
			m_Window.addListener(this);
			
			if(m_Renderer.create(m_Window)) {
				
				if(kyra::GLExtensionLoader::init() == false) {
					std::cout << "[ERROR] GLExtensionLoader::init() failed" << std::endl;
					return;
				}
				
				kyra::VertexArray<Vertex> vertexArray(kyra::PrimitiveType::TRIANGLES,3);
					vertexArray[0].position = kyra::Vector3<float>(-0.5f,-0.5f,0.0f);
					vertexArray[1].position = kyra::Vector3<float>(0.5f,-0.5f,0.0f);
					vertexArray[2].position = kyra::Vector3<float>(0.0f,0.5f,0.0f);
				
				kyra::VertexBuffer vertexBuffer;
					vertexBuffer.create(vertexArray);
				
				kyra::Program program;
					program.linkFromMemory(vertexShaderSrc, fragmentShaderSrc);
				
				kyra::VertexLayout vertexLayout;
					vertexLayout.add(3, 3*sizeof(float), GL_FLOAT);
					
				while(m_Window.isOpen()) {
					m_Window.processEvents();
					m_Renderer.clear();
						m_Renderer.draw(vertexBuffer, program, vertexLayout);
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