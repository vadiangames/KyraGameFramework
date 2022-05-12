#ifndef KYRAGAMEFRAMEWORK_CORE_SMARTPOINTER_HPP
#define KYRAGAMEFRAMEWORK_CORE_SMARTPOINTER_HPP

namespace kyra {
	namespace core {
		
		/// \brief A simple and fast SmartPointer class
		/// Should be used instead of the STL SmartPointers 
		template<class T>
		class SmartPointer {
			
			/// \brief The pointer to the owning project
			T* m_Object;
			
			public:
			/// \brief Default constructor, sets m_Object to nullptr
			SmartPointer() : m_Object(nullptr) {
				
			}
			
			/// \brief Deleted Copy-Constructor
			/// \brief Prevents the SmartPointer from being copied
			SmartPointer(const SmartPointer<T>& obj) = delete;
			
			/// \brief Destructor
			/// \brief If the SmartPointer owns a pointer, the pointer get freed
			~SmartPointer() {
				if(m_Object) {
					delete m_Object;
					m_Object = nullptr;
				}
			}
			
			/// \brief Returns a reference to the owned object
			/// \brief In Debug-Mode you get an error-message if you try to access a nullptr
			T& getRef() {
				#ifdef KYRA_DEBUG
					if(m_Object == nullptr) {
						std::cout << "[ERROR] " << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << ": Try to access nullptr" << std::endl;
					}
				#endif
				return (*m_Object);
			}
			
			/// \brief Returns a copy of the object 
			/// \brief In Debug-Mode, a error-message is written if the object-pointer is nullptr
			T get() const {
				#ifdef KYRA_DEBUG
					if(m_Object == nullptr) {
						std::cout << "[ERROR] " << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << ": Try to access nullptr" << std::endl;
					}
				#endif
				return *m_Object;
			}
			
			/// \brief Returns the owned pointer
			T* getPtr() {
				return m_Object;
			}
			
			/// \brief Checks if the owner Pointer is nullptr
			bool isNull() const {
				return m_Object == nullptr;
			}
			
			/// \brief Access to the pointer
			/// \brief In Debug-Mode, a error-message is written if the object-pointer is nullptr
			T* operator ->() {
				#ifdef KYRA_DEBUG
					if(m_Object == nullptr) {
						std::cout << "[ERROR] " << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << ": Try to access nullptr" << std::endl;
					}
				#endif
				return m_Object;
			}
			
			/// \brief Deference the pointer
			T& operator *() {
				return *m_Object;
			}
			
		};
	}
}

#endif