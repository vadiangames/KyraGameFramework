
#include <KyraGameFramework/RenderDeviceGL/IndexBuffer.hpp>

namespace kyra {

	KYRA_RENDERDEVICEGL_API IndexBuffer::IndexBuffer() : m_Id(0), m_Elements(0) {
			
	}
		
	KYRA_RENDERDEVICEGL_API IndexBuffer::~IndexBuffer() {
		if(m_Id) {
			GL_CHECK(glDeleteBuffers(1,&m_Id));
		}
	}
		
	size_t KYRA_RENDERDEVICEGL_API IndexBuffer::getElementCount() const {
		return m_Elements;
	}
		
	void KYRA_RENDERDEVICEGL_API IndexBuffer::create(size_t indizes, size_t totalSize, void* data, BufferType type ) {
		if(m_Id) {
			GL_CHECK(glDeleteBuffers(1,&m_Id));
			m_Id = 0;
		}
		GLuint glType = GL_STATIC_DRAW;
		if(type == BufferType::DYNAMIC_DRAW) {
			glType = GL_DYNAMIC_DRAW;
		}
		m_Elements = indizes;
		GL_CHECK(glGenBuffers(1,&m_Id));
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
		GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalSize, data, glType));
	}
		
	void KYRA_RENDERDEVICEGL_API IndexBuffer::bind() {
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
	}
		
	void KYRA_RENDERDEVICEGL_API IndexBuffer::unbind() {
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
	
}