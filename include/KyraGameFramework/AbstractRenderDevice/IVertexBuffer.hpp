#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXBUFFER_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXBUFFER_HPP

namespace kyra {
	
	class IVertexBuffer {
		
		public:
		
		virtual void create(size_t size, void* data) = 0;
		virtual void update(size_t size, void* data) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;		
	};
	
}

#endif