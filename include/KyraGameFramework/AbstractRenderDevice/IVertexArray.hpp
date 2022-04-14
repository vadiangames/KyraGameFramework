#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXARRAY_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IVERTEXARRAY_HPP


namespace kyra {
	
	class IVertexArray {
		
		public:

		virtual void create(int type, size_t size) = 0;	
		virtual void setType(int type) = 0;
		virtual int getType() const = 0;
		virtual size_t getSize() const = 0;
		virtual size_t count() const = 0;
		virtual void resize(size_t size) = 0;
		virtual void* getData() = 0;

	};
	
}

#endif