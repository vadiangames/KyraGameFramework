
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <fstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

namespace kyra {
	
	KYRA_RENDERDEVICEGL_API Program::Program() : m_Id(0) {
		
	}
	
	KYRA_RENDERDEVICEGL_API Program::~Program() {
		
	}
		
	bool KYRA_RENDERDEVICEGL_API Program::linkFromMemory(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)  {
		
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
	
	bool KYRA_RENDERDEVICEGL_API Program::linkFromFile(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader) {
		
		//TODO CHECK IF FILE EXISTS
		
		std::ifstream vsf(vertexShader.string());
		std::string vs_content( (std::istreambuf_iterator<char>(vsf) ),
						   (std::istreambuf_iterator<char>()    ) );

		//TODO DUPLICATET CODE
		std::ifstream fsf(fragmentShader.string());
		std::string fs_content( (std::istreambuf_iterator<char>(fsf) ),
						   (std::istreambuf_iterator<char>()    ) );
		
		return linkFromMemory(vs_content, fs_content);
	}
	
	void KYRA_RENDERDEVICEGL_API Program::setInteger(const std::string& id, int value) {
		use();
		GLint location = GL_CHECK(glGetUniformLocation(m_Id,id.c_str()));
		if(location == -1) {
			std::cout << "[ERROR] Can not find uniform location " << id << std::endl;
		}
		GL_CHECK(glUniform1i(location, value));
	}
	
	void KYRA_RENDERDEVICEGL_API Program::setMatrix4(const std::string& id, const glm::mat4& matrix) {
		//TODO: Duplicated Code
		use();
		GLint location = GL_CHECK(glGetUniformLocation(m_Id,id.c_str()));
		if(location == -1) {
			std::cout << "[ERROR] Can not find uniform location " << id << std::endl;
		}
		GL_CHECK(glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(matrix)));
	}
		
	void KYRA_RENDERDEVICEGL_API Program::use()  {
		GL_CHECK(glUseProgram(m_Id));
	}
	
}