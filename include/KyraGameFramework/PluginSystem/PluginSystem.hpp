#ifndef KYRAGAMEFRAMEWORK_PLUGINSYSTEM_PLUGINSYSTEM_HPP
#define KYRAGAMEFRAMEWORK_PLUGINSYSTEM_PLUGINSYSTEM_HPP

#include <KyraGameFramework/PluginSystem/Plugin.hpp>
#include <KyraGameFramework/Core/Filesystem.hpp>

namespace kyra {
	
	class PluginSystem {
	
		public:
		
		template<class T>
		Plugin<T> load(const std::filesystem::path& path) {
			Plugin<T> plugin;
			
			#if defined(__WIN32__) || defined(__WIN64__)
				HMODULE module = LoadLibrary(path.string().c_str());
				if(module) {
					plugin.init( reinterpret_cast<size_t>(module) );
				}
			#endif
			
			return plugin;
		}
		
	};
}



#endif