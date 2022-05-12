#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_VERTEXLAYOUT_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_VERTEXLAYOUT_HPP

#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexLayout.hpp>
#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>

#include <list>

namespace kyra {
	
	typedef struct {
		int id;
		size_t size;
		int type;
		size_t stride;
	}VertexLayoutEntry;
	
	class KYRA_RENDERDEVICEGL_API VertexLayout : public IVertexLayout {
		
		std::list<VertexLayoutEntry> m_Entries;
		size_t m_TotalSize;
		uint32_t m_NextId;
		
		public:
		VertexLayout();
		~VertexLayout();
		
		void add(size_t elements, size_t size, int type) final;
		
		inline void bind() final;
		inline void unbind() final;
		
	};
}

#endif