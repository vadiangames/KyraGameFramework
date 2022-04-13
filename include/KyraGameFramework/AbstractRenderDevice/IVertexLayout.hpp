#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXLAYOUT_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXLAYOUT_HPP

namespace kyra {
	
	class IVertexLayout {
		
		public:
		
		virtual void add(size_t elements, size_t size, int type) = 0;
		virtual void bind() = 0; 	
	};
	
}

#endif