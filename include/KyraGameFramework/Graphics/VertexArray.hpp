#ifndef KYRAGAMEFRAMEWORK_GRAPHICS_VERTEXARRAY_HPP
#define KYRAGAMEFRAMEWORK_GRAPHICS_VERTEXARRAY_HPP

#include <vector>

namespace kyra {
	template<class VertexType>
	class VertexArray : public IVertexArray {
		
		std::vector<VertexType> m_Data;
		PrimitiveType m_PrimitiveType;
		
		public:
		VertexArray() : m_PrimitiveType(PrimitiveType::UNKNOWN) {
			
		}
		
		VertexArray(PrimitiveType type, size_t size) : m_PrimitiveType(type) {
			resize(size);
		}
			
		~VertexArray() {
			
		}

		void create(PrimitiveType type, size_t size) {
			m_PrimitiveType = type;
		    resize(size);
		}	
				
		
		size_t getSize() const {
			return m_Data.size() * sizeof(VertexType);
		}
		
		size_t count() const {
			return m_Data.size();
		}
		
		void resize(size_t size) {
			m_Data.resize(size);
		}
		
		void* getData() {
			return &m_Data[0];
		}
		
		VertexType& operator[](size_t index) {
			return m_Data[index];
		}
		
		void setPrimitiveType(PrimitiveType type) {
			m_PrimitiveType = type;
		}
		
		PrimitiveType getPrimitiveType() const {
			return m_PrimitiveType;
		}
		
	};
}

#endif