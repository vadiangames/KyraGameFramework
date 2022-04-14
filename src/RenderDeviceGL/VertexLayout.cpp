#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>

#include <list>
#include <algorithm>

namespace kyra {
	
	KYRA_RENDERDEVICEGL_API VertexLayout::VertexLayout() : m_TotalSize(0),m_NextId(0) {
			
	}
		
	KYRA_RENDERDEVICEGL_API VertexLayout::~VertexLayout() {
			
	}
		
	void KYRA_RENDERDEVICEGL_API VertexLayout::add(size_t elements, size_t size, int type) {			
		VertexLayoutEntry entry;
			entry.id = m_NextId;
			entry.size = elements;
			entry.type = type;
			entry.stride = m_TotalSize;
	
		m_Entries.push_back(entry);
			
		m_NextId++;
		m_TotalSize += size;
	}
		
	void KYRA_RENDERDEVICEGL_API VertexLayout::bind() {
			
		std::for_each(m_Entries.begin(), m_Entries.end(), [&](const VertexLayoutEntry& entry) {
			glVertexAttribPointer(entry.id,entry.size,entry.type,GL_FALSE, m_TotalSize, (void*)entry.stride);
			glEnableVertexAttribArray(entry.id);
		});
			
	}
	
}
