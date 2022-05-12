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
		
		void setInteger(const std::string& id, int value) final;
		void setMatrix4(const std::string& id, const kyra::math::Matrix4<float>& matrix) final;
		void setVector3(const std::string& id, const kyra::math::Vector3<float>& vec) final;
		void setVector4(const std::string& id, const kyra::math::Vector4<float>& vec) final;
		
		bool linkFromMemory(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) final;
		bool linkFromFile(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader) final;
		void use() final;
		
	};

}

#endif