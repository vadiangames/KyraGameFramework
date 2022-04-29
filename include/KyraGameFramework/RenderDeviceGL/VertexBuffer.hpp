#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_VERTEXBUFFER_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_VERTEXBUFFER_HPP

#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>

namespace kyra {
	
	class KYRA_RENDERDEVICEGL_API VertexBuffer : public IVertexBuffer {
		
		GLuint m_Id;
		size_t m_ElementCount;
		PrimitiveType m_PrimitiveType;
		
		public:
		VertexBuffer();
		~VertexBuffer();
		
		virtual size_t getElementCount() const final;
		
		void create(PrimitiveType primitiveType, size_t elementCount, size_t size, void* data, VertexBufferType type) final;
		
		virtual void create(IVertexArray& vertexArray) final;
		
		void bind() final;
		
		void update(size_t size, void* data) final;
		
		void unbind() final;
		
		PrimitiveType getPrimitiveType() const final;
		
	};
}

#endif