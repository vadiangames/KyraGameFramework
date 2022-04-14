#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXBUFFER_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXBUFFER_HPP


#include <KyraGameFramework/AbstractRenderDevice/IVertexArray.hpp>

namespace kyra {
	
	class IVertexBuffer {
		
		public:
		
		virtual size_t getElementCount() const = 0;
		
		virtual void create(size_t elementCount, size_t size, void* data) = 0;
		virtual void create(IVertexArray& vertexArray) = 0;
		virtual void update(size_t size, void* data) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;		
	};
	
}

#endif