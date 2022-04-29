#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXLAYOUT_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXLAYOUT_HPP

#include <memory>

namespace kyra {
	
	class IVertexLayout {
		
		public:
		typedef std::shared_ptr<IVertexLayout> Ptr;		
		
		virtual void add(size_t elements, size_t size, int type) = 0;
		virtual void bind() = 0; 
		virtual void unbind() = 0;		
	};
	
}

#endif