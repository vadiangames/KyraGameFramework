#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>
#include <KyraGameFramework/RenderDeviceGL/Shader.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>
#include <KyraGameFramework/Math/Vector3.hpp>
#include <KyraGameFramework/Graphics/VertexArray.hpp>
#include <KyraGameFramework/AssetManager/ImageFileBMP.hpp>

#include <iostream>

std::string vertexShaderSrc = "#version 330 core\n"
							  "layout (location = 0) in vec3 aPos;\n"
							  "layout (location = 1) in vec3 aColor;\n"
							  "out vec3 nColor;\n"
							  "void main()\n"
							  "{\n"
							  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
							  "nColor = aColor;\n"
							  "}";
							  
std::string fragmentShaderSrc = "#version 330 core\n"
								"in vec3 nColor;\n"
								"out vec4 FragColor;\n"
								"void main()\n"
								"{\n"
								"FragColor = vec4(nColor.x,nColor.y,nColor.z, 1.0f);\n"
								"}\n"; 


typedef struct {
	kyra::Vector3<float> position;
	kyra::Vector3<float> color;
}ColorVertex;
								
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
		windowSettings.title = L"KyraGameFramework - Window - 03_ColoredTrinagle";
		
		if(m_Window.create(windowSettings)) {
			
			m_Window.addListener(this);
			
			if(m_Renderer.create(m_Window)) {
				
				if(kyra::GLExtensionLoader::init() == false) {
					std::cout << "[ERROR] GLExtensionLoader::init() failed" << std::endl;
					return;
				}
				
				kyra::VertexArray<ColorVertex> vertexArray(3,GL_TRIANGLES);
					vertexArray[0].position = kyra::Vector3<float>(-0.5f,-0.5f,0.0f);
					vertexArray[0].color    = kyra::Vector3<float>(1.0f,0.0f,0.0f);
					vertexArray[1].position = kyra::Vector3<float>(0.5f,-0.5f,0.0f);
					vertexArray[1].color    = kyra::Vector3<float>(0.0f,1.0f,0.0f);
					vertexArray[2].position = kyra::Vector3<float>(0.0f,0.5f,0.0f);
					vertexArray[2].color    = kyra::Vector3<float>(0.0f,0.0f,1.0f);
				
				kyra::VertexBuffer vertexBuffer;
					vertexBuffer.create(vertexArray.count(),vertexArray.getSize(), &vertexArray[0]);
				
				kyra::Program program;
					program.linkFromMemory(vertexShaderSrc, fragmentShaderSrc);
				
				kyra::VertexLayout vertexLayout;
					vertexLayout.add(3, 3*sizeof(float), GL_FLOAT);
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

	kyra::ImageFileBMP image;
	image.load("../assets/Test.bmp");
	image.write("NewBMP.bmp");
	
	kyra::ImageFileBMP image2;
	image2.create(100,100);
	// Modify the pixel data:
	int channels = 24 / 8;
	for(int y =0; y < 100; ++y) {
         for(int x = 0; x < 100; ++x) {
             image2.m_Data[channels * (y * image2.m_InfoHeader.width + x) + 0] = 0;   // B
             image2.m_Data[channels * (y * image2.m_InfoHeader.width + x) + 1] = 0;   // G
             image2.m_Data[channels * (y * image2.m_InfoHeader.width + x) + 2] = 255; // R
             if(channels == 4) {
                 image2.m_Data[channels * (y * image2.m_InfoHeader.width + x) + 3] = 255; // A
             }
         }
    }
	image2.write("Image2.bmp");
	
	MyApplication().run();
	
	return 0;
}