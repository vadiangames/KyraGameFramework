#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IINDEXBUFFER_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IINDEXBUFFER_HPP

#include <memory>
#include <KyraGameFramework/AbstractRenderDevice/Types.hpp>

namespace kyra {
	
	class IIndexBuffer {
		
		public:
		
		typedef std::shared_ptr<IIndexBuffer> Ptr;
		
		virtual size_t getElementCount() const = 0;
		virtual void create(size_t indizes, size_t totalSize, void* data, BufferType type ) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;

	};
	
}

#endif