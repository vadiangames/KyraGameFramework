#ifndef KYRAGAMEFRAMEWORK_EXAMPLES_PLUGINSYSTEM_TESTPLUGININTERFACE_HPP
#define KYRAGAMEFRAMEWORK_EXAMPLES_PLUGINSYSTEM_TESTPLUGININTERFACE_HPP

#include <windows.h>
#include <filesystem>
#include <functional>

#include <KyraGameFramework/PluginSystem/PluginSystem.hpp>

class TestPluginInterface  {
	
	public:
	/*TestPluginInterface() {
		
	}
	
	~TestPluginInterface() {
		
	}*/
	
	virtual std::string getDescription() const = 0;
	
};

#endif