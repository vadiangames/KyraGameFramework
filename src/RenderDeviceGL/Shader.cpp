
#include <KyraGameFramework/RenderDeviceGL/Shader.hpp>

namespace kyra {
	
	KYRA_RENDERDEVICEGL_API Shader::Shader() : m_Id(0), m_Type(ShaderType::UNKNOWN) {
			
	}
		
	KYRA_RENDERDEVICEGL_API Shader::~Shader() {
		if(m_Id) {
			GL_CHECK(glDeleteShader(m_Id));
			m_Id = 0;
		}
	}
		
	bool KYRA_RENDERDEVICEGL_API Shader::create(ShaderType type, const std::string& src) {
			
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
			std::cout << "SOURCE: " << src << std::endl;
			return false;
		}
		return true;
	}
		
	int KYRA_RENDERDEVICEGL_API Shader::getId() const {
		return m_Id;
	}
	
}