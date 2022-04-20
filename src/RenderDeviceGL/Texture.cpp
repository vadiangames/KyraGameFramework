#include <KyraGameFramework/RenderDeviceGL/Texture.hpp>

namespace kyra {

	KYRA_RENDERDEVICEGL_API Texture::Texture() : m_Id(0) {

	}
		
	KYRA_RENDERDEVICEGL_API Texture::~Texture() {
		if(m_Id) {
			glDeleteTextures(1,&m_Id);
		}
	}
		
	void KYRA_RENDERDEVICEGL_API Texture::loadFromFile(const std::filesystem::path& path) {
		std::cout << __FILE__ << " " << __LINE__ << __PRETTY_FUNCTION__ << std::endl;
		
		if(m_Id) {
			glDeleteTextures(1,&m_Id);
			m_Id = 0;
		}
		
		Image image;
		if(image.load(path) == false) { 
			std::cout << "[ERROR] Can not load image " << path.string() << std::endl;
		}
		
		GL_CHECK(glGenTextures(1,&m_Id));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_Id));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, image.getWidth(), image.getHeight(),0,GL_RGBA, GL_UNSIGNED_BYTE,image.getData()));
		GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
			
	}
		
	void KYRA_RENDERDEVICEGL_API Texture::bind() {
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_Id));
	}

}
