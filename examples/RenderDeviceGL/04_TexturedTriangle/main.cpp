#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>
#include <KyraGameFramework/RenderDeviceGL/Shader.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>
#include <KyraGameFramework/RenderDeviceGL/Texture.hpp>
#include <KyraGameFramework/Math/Vector3.hpp>
#include <KyraGameFramework/Math/Vector2.hpp>
#include <KyraGameFramework/AbstractRenderDevice/VertexArray.hpp>

#include <iostream>
#include <filesystem>

std::string vertexShaderSrc = "#version 330 core\n"
							  "layout (location = 0) in vec3 aPos;\n"
							  "layout (location = 1) in vec3 aColor;\n"
							  "layout (location = 2) in vec2 aTexCoord;\n"
							  "out vec3 nColor;\n"
							  "out vec2 texCoord;\n"
							  "void main()\n"
							  "{\n"
							  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
							  "nColor = aColor;\n"
							  "texCoord = aTexCoord;\n"
							  "}";
							  
std::string fragmentShaderSrc = "#version 330 core\n"
								"in vec3 nColor;\n"
								"in vec2 texCoord;\n"
								"out vec4 FragColor;\n"
								"uniform sampler2D ourTexture;\n"
								"void main()\n"
								"{\n"
								"FragColor = texture(ourTexture, texCoord);\n"
								"}\n"; 


typedef struct {
	kyra::Vector3<float> position;
	kyra::Vector3<float> color;
	kyra::Vector2<float> uv;
}ColorVertex;

class MyApplication : public kyra::SystemEventListener {

	kyra::Window m_Window;
	kyra::RenderDeviceGL m_Renderer;
	
	public:
	MyApplication() {}
	~MyApplication() {}
	
	
	//! Implementation of kyra::SystemEventListener::onClose()
	virtual void onClose() override {
		m_Window.close();
	}
		
	void run() {
		
		kyra::WindowSettings windowSettings;
		windowSettings.width = 800;
		windowSettings.height = 600;
		windowSettings.title = L"KyraGameFramework - Window - 03_ColoredTrinagle";
		
		if(m_Window.create(windowSettings)) {
			
			m_Window.addListener(this);
			
			if(m_Renderer.create(m_Window)) {
				
				if(kyra::GLExtensionLoader::init() == false) {
					std::cout << "[ERROR] GLExtensionLoader::init() failed" << std::endl;
					return;
				}
				
				kyra::Texture texture;
					texture.loadFromFile("Test.png");
				
				kyra::VertexArray<ColorVertex> vertexArray(kyra::PrimitiveType::TRIANGLES,3);
					vertexArray[0].position = kyra::Vector3<float>(-0.5f,-0.5f,0.0f);
					vertexArray[0].color    = kyra::Vector3<float>(1.0f,0.0f,0.0f);
					vertexArray[0].uv       = kyra::Vector2<float>(0,0);
					vertexArray[1].position = kyra::Vector3<float>(0.5f,-0.5f,0.0f);
					vertexArray[1].color    = kyra::Vector3<float>(0.0f,1.0f,0.0f);
					vertexArray[1].uv       = kyra::Vector2<float>(1,0);
					vertexArray[2].position = kyra::Vector3<float>(0.0f,0.5f,0.0f);
					vertexArray[2].color    = kyra::Vector3<float>(0.0f,0.0f,1.0f);
					vertexArray[2].uv       = kyra::Vector2<float>(1,1);					
					
					
				kyra::IVertexBuffer::Ptr vertexBuffer = m_Renderer.createVertexBuffer();
					vertexBuffer->create(vertexArray);
				
				kyra::IProgram::Ptr program = m_Renderer.createProgramFromMemory(vertexShaderSrc, fragmentShaderSrc);
				
				kyra::IVertexLayout::Ptr vertexLayout = m_Renderer.createVertexLayout();
					vertexLayout->add(3, 3*sizeof(float), GL_FLOAT);
					vertexLayout->add(3, 3*sizeof(float), GL_FLOAT);
					vertexLayout->add(2, 2*sizeof(float), GL_FLOAT);
					
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