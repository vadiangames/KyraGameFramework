#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXTURE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXTURE_HPP

#include <KyraGameFramework/Math/Vector2.hpp>
#include <filesystem>
#include <memory>

namespace kyra {
	
	class ITexture {
		
		public:
		ITexture() {}
		virtual ~ITexture() {}
		
		typedef std::shared_ptr<ITexture> Ptr;
		
		virtual void loadFromFile(const std::filesystem::path& path) = 0;
		virtual void bind(uint32_t slot = 0) = 0;
		virtual kyra::Vector2<float> getSize() const = 0;
	};
	
}

#endif