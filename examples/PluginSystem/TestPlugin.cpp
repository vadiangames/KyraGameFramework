

#include "TestPlugin.hpp"

KYRA_TESTPLUGIN_API MyPlugin::MyPlugin() {
	
}

KYRA_TESTPLUGIN_API MyPlugin::~MyPlugin() {
	
}
	
std::string KYRA_TESTPLUGIN_API MyPlugin::getDescription() const {
		return "This is a message from the test-plugin";
}

extern "C" {
	//KYRA_TESTPLUGIN_API PLUGIN_IMPLEMENTATION(MyPlugin);
	IMPLEMENT_PLUGIN(KYRA_TESTPLUGIN_API, MyPlugin);
}