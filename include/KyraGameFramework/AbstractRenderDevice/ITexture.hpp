#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXTURE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXTURE_HPP

#include <glm/glm.hpp>
#include <filesystem>

namespace kyra {
	
	class ITexture {
		
		public:
		ITexture() {}
		virtual ~ITexture() {}
		
		virtual void loadFromFile(const std::filesystem::path& path) = 0;
		virtual void bind(uint32_t slot = 0) = 0;
		virtual glm::vec2 getSize() const = 0;
	};
	
}

#endif