#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_PROGRAM_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_PROGRAM_HPP

#include <KyraGameFramework/RenderDeviceGL/Shader.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IProgram.hpp>

namespace kyra {

	class KYRA_RENDERDEVICEGL_API Program : public IProgram {
		
		GLuint m_Id;
		
		public:
		Program();
		~Program();
		
		bool linkFromMemory(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) final;
		void use() final;
		
	};

}

#endif