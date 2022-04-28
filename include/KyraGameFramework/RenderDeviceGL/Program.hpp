#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_PROGRAM_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_PROGRAM_HPP

#include <KyraGameFramework/RenderDeviceGL/Shader.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IProgram.hpp>


#include <string>

namespace kyra {

	class KYRA_RENDERDEVICEGL_API Program : public IProgram {
		
		GLuint m_Id;
		
		public:
		Program();
		~Program();
		
		void setInteger(const std::string& id, int value);
		void setMatrix4(const std::string& id, const glm::mat4& matrix);
		void setVector3(const std::string& id, const glm::vec3& vec);
		void setVector4(const std::string& id, const glm::vec4& vec);
		
		bool linkFromMemory(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) final;
		bool linkFromFile(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader) final;
		void use() final;
		
	};

}

#endif