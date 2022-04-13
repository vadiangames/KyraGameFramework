#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/Window/Windows/WindowWin32.hpp>
#include <KyraGameFramework/Window/SystemEventListener.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGl.hpp>


#include <iostream>

#define GL_CHECK(x) x; if(glGetError() != GL_NO_ERROR) {std::cout <<"[ERROR] Error in OpenGL-Function: " << #x << std::endl;}

namespace kyra {
	
	enum class ShaderType {
		VERTEX,
		FRAGMENT
	};
	
	class Shader {
		
		int m_Id;
		ShaderType m_Type;
		
		public:
		Shader() : m_Id(0) {
			
		}
		
		~Shader() {
			if(m_Id) {
				GL_CHECK(glDeleteShader(m_Id));
				m_Id = 0;
			}
		}
		
		bool create(ShaderType type, const std::string& src) {
			
			if(m_Id) {
				GL_CHECK(glDeleteShader(m_Id));
				m_Id = 0;
			}
			
			if(type == ShaderType::VERTEX) {
				m_Id = GL_CHECK(glCreateShader(GL_VERTEX_SHADER));
			} else if(type == ShaderType::FRAGMENT) {
				m_Id = GL_CHECK(glCreateShader(GL_FRAGMENT_SHADER));
			}
			
			if(!m_Id) {	return false; }
			
			const char* sourceCode = src.c_str();
			GL_CHECK(glShaderSource(m_Id,1,&sourceCode,NULL));
			GL_CHECK(glCompileShader(m_Id));
			
			int success = 0;
			char infoLog[512];
			GL_CHECK(glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success));
			if(!success) {
				GL_CHECK(glGetShaderInfoLog(m_Id, 512, NULL, infoLog));
				std::cout << "ERROR::SHADER::COMPILATION_FAILED: " << infoLog << std::endl;
				return false;
			}
			return true;
		}
		
		int getId() const {
			return m_Id;
		}
		
	};
	
	class Program {
		
		GLuint m_Id;
		
		public:
		Program() {}
		~Program() {}
		
		bool linkFromMemory(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) {
			
			Shader vertexShader;
				vertexShader.create(ShaderType::VERTEX, vertexShaderSrc);
				
			Shader fragmentShader;
				fragmentShader.create(ShaderType::FRAGMENT, fragmentShaderSrc);
				
			m_Id = glCreateProgram();
			glAttachShader(m_Id, vertexShader.getId());
			glAttachShader(m_Id, fragmentShader.getId());
			glLinkProgram(m_Id);			
			
			int success = 0;
			char infoLog[512];
			glGetProgramiv(m_Id, GL_LINK_STATUS,&success);
			if(!success) {
				glGetProgramInfoLog(m_Id,512, NULL,infoLog);
				std::cout << "ERROR::PROGRAM::LINK_FAILED: " << infoLog << std::endl;
				return false; 
			}
			
			return true;
		}
		
		void use() {
			GL_CHECK(glUseProgram(m_Id));
		}
		
	};
	
}



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
		windowSettings.title = L"KyraGameFramework - Window - 01_Hello World";
		
		if(m_Window.create(windowSettings)) {
			
			m_Window.addListener(this);
			
			if(m_Renderer.create(m_Window)) {
				
				if(kyra::GLExtensionLoader::init() == false) {
					std::cout << "[ERROR] GLExtensionLoader::init() failed" << std::endl;
					return;
				}
				
				float vertices[] = {
					-0.5f, -0.5f, 0.0f,
					0.5f, -0.5f, 0.0f,
					0.0f,  0.5f, 0.0f
				}; 
			
				kyra::Program program;
					program.linkFromMemory(vertexShaderSrc, fragmentShaderSrc);
								
				unsigned int VBO;
				GL_CHECK(glGenBuffers(1,&VBO));
				GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
				GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
								
				while(m_Window.isOpen()) {
					m_Window.processEvents();
					m_Renderer.clear();
						glBindBuffer(GL_ARRAY_BUFFER,VBO);
						glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float), (void*)0);
						glEnableVertexAttribArray(0);
						program.use();
						glDrawArrays(GL_TRIANGLES,0,3);
						glBindBuffer(GL_ARRAY_BUFFER,0);
					m_Renderer.display();
				}
				
				glDeleteBuffers(1,&VBO);
			}
		}
		
	}

};

int main(int argc, char** argv) {
	
	MyApplication().run();
	
	return 0;
}