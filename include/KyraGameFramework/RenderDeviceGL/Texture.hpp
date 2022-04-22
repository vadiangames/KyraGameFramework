#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_TEXTURE_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_TEXTURE_HPP

#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/RenderDeviceGL/Image.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ITexture.hpp>

#include <filesystem>

namespace kyra {

	class KYRA_RENDERDEVICEGL_API Texture : public ITexture {
		
		GLuint m_Id;
		int m_Width;
		int m_Height;
		
		public:
		Texture();
		
		~Texture();
		
		virtual glm::vec2 getSize() const;
		void loadFromFile(const std::filesystem::path& path);
		void bind(uint32_t slot = 0);
		
	};

}

#endif