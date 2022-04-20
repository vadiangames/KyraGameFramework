#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXARRAY_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXARRAY_HPP


#include <KyraGameFramework/AbstractRenderDevice/Types.hpp>

namespace kyra {
	
	class IVertexArray {
		
		public:

		virtual void create(PrimitiveType type, size_t size) = 0;	
		virtual void setPrimitiveType(PrimitiveType type) = 0;
		virtual PrimitiveType getPrimitiveType() const = 0;
		virtual size_t getSize() const = 0;
		virtual size_t count() const = 0;
		virtual void resize(size_t size) = 0;
		virtual void* getData() = 0;

	};
	
}

#endif