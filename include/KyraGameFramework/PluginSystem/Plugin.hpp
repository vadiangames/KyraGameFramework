#ifndef KYRAGAMEFRAMEWORK_PLUGINSYSTEM_PLUGIN_HPP
#define KYRAGAMEFRAMEWORK_PLUGINSYSTEM_PLUGIN_HPP

#include <functional>
#include <memory>
#include <filesystem>

#if defined(__WIN32__) || defined(__WIN64__)
	#include <windows.h>
#endif 

namespace kyra {
	namespace internal {
		template<class T> 
		std::function<T> functional_cast(FARPROC proc) {
			return std::function<T>(reinterpret_cast<__stdcall T*>(proc));
		}
	}

	template<class T>
	class Plugin {
		
		#if defined(__WIN32__) || defined(__WIN64__)
			HMODULE m_Module;
		#endif 
		
		std::shared_ptr<T> m_Instance;
		
		public:
		#if defined(__WIN32__) || defined(__WIN64__)
			Plugin() : m_Module(NULL) {
			
			}
		#else
			Plugin() {
			
			}
		#endif
		
		virtual ~Plugin() {
			
		}
		
		bool isLoaded() const {
			#if defined(__WIN32__) || defined(__WIN64__)
				return (m_Module && (m_Instance.get() != nullptr));
			#endif
		}
		

		#if defined(__WIN32__) || defined(__WIN64__)
		template<class FuncType>
		std::function<FuncType> getFunction(const std::string& name) {
			FARPROC function = GetProcAddress(m_Module, name.c_str());
			if(!function) {
				return std::function<FuncType>();
			}
			return internal::functional_cast<FuncType>(function);
		}
		#endif
		
		
		#if defined(__WIN32__) || defined(__WIN64__)
		bool init(size_t module) {
			m_Module =  reinterpret_cast<HMODULE>(module);
			std::function<void*()> createFunc = getFunction<void*()>("kyra_plugin_interface_get");
			if(createFunc) {
				m_Instance = std::shared_ptr<T>(reinterpret_cast<T*>( createFunc() ));
			}
			return (m_Instance.get() != nullptr);
		}
		#endif
		
		std::shared_ptr<T>& getInstance() {
			return m_Instance;
		}

	};	

}

	
#define DEFINE_PLUGIN(x)  extern void* x kyra_plugin_interface_get();
#define IMPLEMENT_PLUGIN(x,y) void* x kyra_plugin_interface_get() {return new y();}


#endif