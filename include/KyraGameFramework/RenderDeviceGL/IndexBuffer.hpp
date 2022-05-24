#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_INDEXBUFFER_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_INDEXBUFFER_HPP


#include <KyraGameFramework/AbstractRenderDevice/IIndexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/Types.hpp>
#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>


namespace kyra {
	
	class KYRA_RENDERDEVICEGL_API IndexBuffer : public IIndexBuffer {
		
		unsigned int m_Id;
		size_t m_Elements;
		
		public:
		IndexBuffer();
		
		~IndexBuffer();
		
		size_t getElementCount() const final;
		
		void create(size_t indizes, size_t totalSize, void* data, BufferType type ) final;
		
		void bind() final;
		
		void unbind() final;
				
	};
	
}

#endif