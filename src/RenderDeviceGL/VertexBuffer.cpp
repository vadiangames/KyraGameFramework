#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>

namespace kyra {

	KYRA_RENDERDEVICEGL_API VertexBuffer::VertexBuffer() : m_Id(0), m_ElementCount(0) {
			
	}
		
	KYRA_RENDERDEVICEGL_API VertexBuffer::~VertexBuffer() {
		if(m_Id) {
			GL_CHECK(glDeleteBuffers(1,&m_Id));
		}
	}
		
	size_t KYRA_RENDERDEVICEGL_API VertexBuffer::getElementCount() const {
		return m_ElementCount;
	}
		
	void KYRA_RENDERDEVICEGL_API VertexBuffer::create(PrimitiveType type, size_t elementCount, size_t size, void* data) {
		if(m_Id) {
			GL_CHECK(glDeleteBuffers(1,&m_Id));
			m_Id = 0;
		}			
		m_PrimitiveType = type;
		m_ElementCount = elementCount;
		GL_CHECK(glGenBuffers(1,&m_Id));
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}
		
	void KYRA_RENDERDEVICEGL_API VertexBuffer::create(IVertexArray& vertexArray) {
		if(m_Id) {
			GL_CHECK(glDeleteBuffers(1,&m_Id));
			m_Id = 0;
		}
		m_ElementCount = vertexArray.count();
		m_PrimitiveType = vertexArray.getPrimitiveType();
		GL_CHECK(glGenBuffers(1,&m_Id));
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertexArray.getSize(), vertexArray.getData(), GL_STATIC_DRAW));
	}
		
	void KYRA_RENDERDEVICEGL_API VertexBuffer::bind() {
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
	}
		
	void KYRA_RENDERDEVICEGL_API VertexBuffer::update(size_t size, void* data) {
		GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0,size, data));
	}
		
	void KYRA_RENDERDEVICEGL_API VertexBuffer::unbind() {
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
	
	PrimitiveType KYRA_RENDERDEVICEGL_API VertexBuffer::getPrimitiveType() const {
		return m_PrimitiveType;
	}
		
}
