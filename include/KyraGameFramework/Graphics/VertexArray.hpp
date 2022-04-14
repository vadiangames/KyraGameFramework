#ifndef KYRAGAMEFRAMEWORK_GRAPHICS_VERTEXARRAY_HPP
#define KYRAGAMEFRAMEWORK_GRAPHICS_VERTEXARRAY_HPP

#include <vector>

namespace kyra {
	template<class VertexType>
	class VertexArray : public IVertexArray {
		
		std::vector<VertexType> m_Data;
		int m_Type;
		
		public:
		VertexArray() : m_Type(0) {
			
		}
		
		VertexArray(int type, size_t size) : m_Type(type) {
			resize(size);
		}
			
		~VertexArray() {
			
		}

		void create(int type, size_t size) {
			m_Type = type;
		    resize(size);
		}	
		
		void setType(int type) {
			m_Type = type;
		}
		
		int getType() const {
			return m_Type;
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
		
	};
}

#endif