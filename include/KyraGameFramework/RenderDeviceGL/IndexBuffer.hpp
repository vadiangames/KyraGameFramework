#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_INDEXBUFFER_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_INDEXBUFFER_HPP


#include <KyraGameFramework/AbstractRenderDevice/IIndexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/Types.hpp>

namespace kyra {
	
	class IndexBuffer : public IIndexBuffer {
		
		unsigned int m_Id;
		size_t m_Elements;
		
		public:
		IndexBuffer() : m_Id(0) {
			
		}
		
		~IndexBuffer() {
			if(m_Id) {
				GL_CHECK(glDeleteBuffers(1,&m_Id));
			}
		}
		
		size_t getElementCount() const {
			return m_Elements;
		}
		
		void create(size_t indizes, size_t totalSize, void* data, BufferType type ) {
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
		
		void bind() {
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
		}
		
		void unbind() {
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}
				
	};
	
}

#endif