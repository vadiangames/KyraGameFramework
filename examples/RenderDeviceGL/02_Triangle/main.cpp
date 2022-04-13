#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/Window/Windows/WindowWin32.hpp>
#include <KyraGameFramework/Window/SystemEventListener.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGl.hpp>

#include <iostream>
#include <vector>

#define GL_CHECK(x) x; if(glGetError() != GL_NO_ERROR) {std::cout <<"[ERROR] Error in OpenGL-Function: " << #x << std::endl;}

namespace kyra {
	
	template<class T>
	class Vector3 {
	
		T m_Data[3];
		
		public:
		Vector3() : m_Data{0,0,0} {}
		Vector3(T x, T y, T z) : m_Data{x,y,z} {}
		
		void* getData() {
			return (void*)(&m_Data[0]);
		}
		
	};
	
	template<class VertexType>
	class VertexArray {
		
		std::vector<VertexType> m_Data;
		int m_Type;
		
		public:
		VertexArray() : m_Type(0) {
			
		}
		
		VertexArray(int type, size_t size) : m_Type(type) {
			resize(size);
		}
			
		~VertexArray() {
			
		}

		void create(int type, size_t size) {
			m_Type = type;
		    resize(size);
		}	
		
		void setType(int type) {
			m_Type = type;
		}
		
		int getType() const {
			return m_Type;
		}
		
		size_t getSize() const {
			return m_Data.size() * sizeof(VertexType);
		}
		
		size_t count() const {
			return m_Data.size();
		}
		
		void resize(size_t size) {
			m_Data.resize(size);
		}
		
		VertexType& operator[](size_t index) {
			return m_Data[index];
		}
		
	};
	
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
	
	class Program : public IProgram {
		
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
	
	class VertexBuffer : public IVertexBuffer {
		
		GLuint m_Id;
		
		public:
		VertexBuffer() : m_Id(0){
			
		}
		
		~VertexBuffer() {
			if(m_Id) {
				GL_CHECK(glDeleteBuffers(1,&m_Id));
			}
		}
		
		void create(size_t size, void* data) {
			if(m_Id) {
				GL_CHECK(glDeleteBuffers(1,&m_Id));
				m_Id = 0;
			}			
			GL_CHECK(glGenBuffers(1,&m_Id));
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
			GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		}
		
		void bind() {
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
		}
		
		void update(size_t size, void* data) {
			GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0,size, data));
		}
		
		void unbind() {
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}
		
	};
	
	typedef struct {
		int id;
		size_t size;
		int type;
		size_t stride;
	}VertexLayoutEntry;
	
	class VertexLayout : public IVertexLayout {
		
		std::list<VertexLayoutEntry> m_Entries;
		size_t m_TotalSize;
		uint32_t m_NextId;
		
		public:
		VertexLayout() : m_TotalSize(0),m_NextId(0) {
			
		}
		
		~VertexLayout() {
			
		}
		
		void add(size_t elements, size_t size, int type) {			
			VertexLayoutEntry entry;
			entry.id = m_NextId;
			entry.size = elements;
			entry.type = type;
			entry.stride = m_TotalSize;
			m_Entries.push_back(entry);
			
			m_NextId++;
			m_TotalSize += size;
		}
		
		void bind() {
			for(auto& entry : m_Entries) {
				glVertexAttribPointer(entry.id,entry.size,entry.type,GL_FALSE, m_TotalSize, (void*)entry.stride);
				glEnableVertexAttribArray(entry.id);
			}
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
		windowSettings.title = L"KyraGameFramework - Window - 01_Hello World";
		
		if(m_Window.create(windowSettings)) {
			
			m_Window.addListener(this);
			
			if(m_Renderer.create(m_Window)) {
				
				if(kyra::GLExtensionLoader::init() == false) {
					std::cout << "[ERROR] GLExtensionLoader::init() failed" << std::endl;
					return;
				}
				
				kyra::VertexArray<Vertex> vertexArray(GL_TRIANGLES, 3);
				vertexArray[0].position = kyra::Vector3<float>(-0.5f,-0.5f,0.0f);
				vertexArray[1].position = kyra::Vector3<float>(0.5f,-0.5f,0.0f);
				vertexArray[2].position = kyra::Vector3<float>(0.0f,0.5f,0.0f);
				
				kyra::Program program;
					program.linkFromMemory(vertexShaderSrc, fragmentShaderSrc);
								
				kyra::VertexBuffer vertexBuffer;
					vertexBuffer.create( vertexArray.getSize(), &vertexArray[0]);
					
				kyra::VertexLayout vertexLayout;
					vertexLayout.add(3, 3*sizeof(float), GL_FLOAT);
				
				while(m_Window.isOpen()) {
					m_Window.processEvents();
					m_Renderer.clear();
						vertexBuffer.bind();
						vertexLayout.bind();
						program.use();
						glDrawArrays(GL_TRIANGLES,0,vertexArray.count());
						vertexBuffer.unbind();
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