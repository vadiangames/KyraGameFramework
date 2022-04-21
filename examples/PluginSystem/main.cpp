#include <windows.h>
#include <functional>
#include <iostream>

#include <KyraGameFramework/PluginSystem/PluginSystem.hpp>
#include "TestPluginInterface.hpp"
#include <filesystem>
#include <memory>

int main(int argc, char** argv) {


	kyra::PluginSystem pluginSystem;
	
	kyra::Plugin<TestPluginInterface> myPlugin = pluginSystem.load<TestPluginInterface>("libTestPlugin.dll");
	if(myPlugin.isLoaded()) {
		std::cout << myPlugin.getInstance()->getDescription() << std::endl;
	}
	
	return 0;
}