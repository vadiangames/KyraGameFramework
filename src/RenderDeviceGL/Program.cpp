
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>

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
		
	void KYRA_RENDERDEVICEGL_API Program::use()  {
		GL_CHECK(glUseProgram(m_Id));
	}
	
}