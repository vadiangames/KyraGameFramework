#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#define STBI_NO_FAILURE_STRINGS

#include <stb_image_write.h>

#include <iostream>

#include <KyraGameFramework/RenderDeviceGL/Image.hpp>

namespace kyra {

	KYRA_RENDERDEVICEGL_API Image::Image() : m_Width(0), m_Height(0), m_Channels(0), m_Data(nullptr) {
		
	}
		
	KYRA_RENDERDEVICEGL_API Image::~Image() {
		if(m_Data) {
			stbi_image_free(m_Data);
		}
	}
		
	int KYRA_RENDERDEVICEGL_API Image::getWidth() const {
		return m_Width;
	}
		
	int KYRA_RENDERDEVICEGL_API Image::getHeight() const {
		return m_Height;
	}
	
	int KYRA_RENDERDEVICEGL_API Image::getChannels() const {
		return m_Channels;
	}
		
	bool KYRA_RENDERDEVICEGL_API Image::load(const std::filesystem::path& path) {
		if(std::filesystem::exists(path) == false) {
			std::cout << "[ERROR] Can not find image " << path.string() << std::endl;
			return false;
		}
		m_Data = stbi_load(path.string().c_str(), &m_Width, &m_Height, &m_Channels, 0);
		if (!m_Data) {
			std::cout << "[ERROR] " << stbi_failure_reason() << std::endl;
			return false;
		}
		return true;
	}
		
	void KYRA_RENDERDEVICEGL_API Image::save(const std::filesystem::path& path) {
		if(path.extension() == ".png") {
			stbi_write_png(path.string().c_str(), m_Width, m_Height, m_Channels, m_Data, m_Width * m_Channels);
		} else if(path.extension() == ".jpg") {
			stbi_write_jpg(path.string().c_str(), m_Width, m_Height, m_Channels, m_Data, 100);
		} else {
			std::cout << "[ERROR] Unknown image file format " << path.extension() << std::endl;
		}
	}
		
	KYRA_RENDERDEVICEGL_API unsigned char*  Image::getData() {
		return m_Data;
	}

}

