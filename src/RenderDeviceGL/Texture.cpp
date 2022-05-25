#include <KyraGameFramework/RenderDeviceGL/Texture.hpp>
#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/Math/Vector2.hpp>

namespace kyra {

	KYRA_RENDERDEVICEGL_API Texture::Texture() : m_Id(0), m_Width(0), m_Height(0) {

	}
		
	KYRA_RENDERDEVICEGL_API Texture::~Texture() {
		if(m_Id) {
			GL_CHECK(glDeleteTextures(1,&m_Id));
		}
	}
		
	void KYRA_RENDERDEVICEGL_API Texture::loadFromFile(const std::filesystem::path& path) {
		if(m_Id) {
			GL_CHECK(glDeleteTextures(1,&m_Id));
			m_Id = 0;
		}
		
		Image image;
		if(image.load(path) == false) { 
			std::cout << "[ERROR] Can not load image " << path.string() << std::endl;
			return;
		}
		
		m_Width = image.getWidth();
		m_Height = image.getHeight();
		
		GL_CHECK(glGenTextures(1,&m_Id));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_Id));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		if(image.getChannels() == 4) {
			GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, m_Width, m_Height,0,GL_RGBA, GL_UNSIGNED_BYTE,image.getData()));		} else if(image.getChannels() == 3) {
			GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, m_Width, m_Height,0,GL_RGB, GL_UNSIGNED_BYTE,image.getData()));
		}
		GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
			
	}
	
	void KYRA_RENDERDEVICEGL_API Texture::create(const math::Vector2<int>& size, void* data) {
		m_Width = size.get(0);
		m_Height = size.get(1);
		GL_CHECK(glGenTextures(1, &m_Id));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_Id));
		GL_CHECK(glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				size.get(0),
				size.get(1),
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				data
		));
								
		// set texture options
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	}
	
	math::Vector2<float> KYRA_RENDERDEVICEGL_API Texture::getSize() const {
		return math::Vector2<float>( static_cast<float>(m_Width), static_cast<float>(m_Height));
	}
		
	void KYRA_RENDERDEVICEGL_API Texture::bind(uint32_t slot) {
		GL_CHECK(glActiveTexture(GL_TEXTURE0 + slot));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_Id));
	}

}
