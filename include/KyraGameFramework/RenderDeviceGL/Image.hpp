#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_IMAGE_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_IMAGE_HPP

#include <filesystem>

#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>

namespace kyra {

	class KYRA_RENDERDEVICEGL_API Image {
		
		int m_Width;
		int m_Height;
		int m_Channels;
		unsigned char* m_Data;
		
		public:
		Image();
		
		~Image();
		
		int getWidth() const;
		
		int getHeight() const;
		
		int getChannels() const;
		
		bool load(const std::filesystem::path& path);
		
		void save(const std::filesystem::path& path);
		
		unsigned char* getData();
	};
	

}

#endif