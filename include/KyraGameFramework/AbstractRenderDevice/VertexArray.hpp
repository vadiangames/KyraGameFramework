#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_VERTEXARRAY_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_VERTEXARRAY_HPP

#include <vector>

namespace kyra {
	
	/// \brief A template for all VertexArrays
	template<class VertexType>
	class VertexArray : public IVertexArray {
		
		
		/// \brief holds the vertices of the vertexarray
		std::vector<VertexType> m_Data;
		
		/// \brief the PrimitiveType of the vertexarray
		PrimitiveType m_PrimitiveType;
		
		public:
		/// \brief default constructor
		VertexArray() : m_PrimitiveType(PrimitiveType::UNKNOWN) {
			
		}
		
		/// \brief constructor
		/// \param type the PrimitiveType of the vertexarray
		/// \param the number of elements of the vertexarray
		VertexArray(PrimitiveType type, size_t size) : m_PrimitiveType(type) {
			resize(size);
		}
		
		/// \brief default destructor
		~VertexArray() {
			
		}

		/// \brief creates the vertexarray
		/// \param the primitive type of the vertexarray
		/// \param the number of entries in the vertexarray
		void create(PrimitiveType type, size_t size) final {
			m_PrimitiveType = type;
		    resize(size);
		}	
				
		/// \brief returns the total size of the vertices data
		size_t getSize() const final {
			return m_Data.size() * sizeof(VertexType);
		}
		
		/// \brief returns the number of entries in the vertexarray
		size_t count() const final {
			return m_Data.size();
		}
		
		/// \brief resizes the vertexarray to the given size
		void resize(size_t size) final {
			m_Data.resize(size);
		}
		
		/// \brief returns a pointer to the first entry of the vertices-data
		void* getData() final {
			return &m_Data[0];
		}
		
		/// \brief returns the Vertex of the vertexArray on the given index
		VertexType& operator[](size_t index) {
			return m_Data[index];
		}
		
		/// \brief changes the PrimitiveType
		void setPrimitiveType(PrimitiveType type) final {
			m_PrimitiveType = type;
		}
		
		/// \brief returns the PrimitiveType
		PrimitiveType getPrimitiveType() const final {
			return m_PrimitiveType;
		}
		
	};
}

#endif