#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_SHADER_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_SHADER_HPP

#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>

namespace kyra {

	enum class ShaderType {
		UNKNOWN,
		VERTEX,
		FRAGMENT
	};
	
	class KYRA_RENDERDEVICEGL_API Shader {
		
		int m_Id;
		ShaderType m_Type;
		
		public:
		Shader();
		~Shader();
		
		bool create(ShaderType type, const std::string& src);
		int getId() const;
		
	};

}

#endif