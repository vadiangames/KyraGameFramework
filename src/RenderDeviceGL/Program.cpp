
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <fstream>
#include <string>

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
				
		m_Id = GL_CHECK(glCreateProgram());
			GL_CHECK(glAttachShader(m_Id, vertexShader.getId()));
			GL_CHECK(glAttachShader(m_Id, fragmentShader.getId()));
			GL_CHECK(glLinkProgram(m_Id));			
			
		int success = 0;
		GL_CHECK(glGetProgramiv(m_Id, GL_LINK_STATUS,&success));
		if(!success) {
			char infoLog[512];
			GL_CHECK(glGetProgramInfoLog(m_Id,512, NULL,infoLog));
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
	
	void KYRA_RENDERDEVICEGL_API Program::setMatrix4(const std::string& id, const math::Matrix4<float>& matrix) {
		use();
		GLint location = GL_CHECK(glGetUniformLocation(m_Id,id.c_str()));
		if(location == -1) {
			std::cout << "[ERROR] Can not find uniform location " << id << std::endl;
		}
		GL_CHECK(glUniformMatrix4fv(location,1,GL_FALSE,(float*)(&matrix)));
	}
	
	void KYRA_RENDERDEVICEGL_API Program::setVector3(const std::string& id, const math::Vector3<float>& vec) {
		use();
		GLint location = GL_CHECK(glGetUniformLocation(m_Id,id.c_str()));
		if(location == -1) {
			std::cout << "[ERROR] Can not find uniform location " << id << std::endl;
		}
		GL_CHECK(glUniform3fv(location,1,(float*)(&vec)));
	}
	
	void KYRA_RENDERDEVICEGL_API Program::setVector4(const std::string& id, const math::Vector4<float>& vec) {
		use();
		GLint location = GL_CHECK(glGetUniformLocation(m_Id,id.c_str()));
		if(location == -1) {
			std::cout << "[ERROR] Can not find uniform location " << id << std::endl;
		}
		GL_CHECK(glUniform4fv(location,1,(float*)(&vec)));
	}
	
	void KYRA_RENDERDEVICEGL_API Program::use()  {
		GL_CHECK(glUseProgram(m_Id));
	}
	
}