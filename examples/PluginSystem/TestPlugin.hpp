#ifndef KYRAGAMEFRAMEWORK_EXAMPLES_PLUGINSYSTEM_TESTPLUGIN_HPP
#define KYRAGAMEFRAMEWORK_EXAMPLES_PLUGINSYSTEM_TESTPLUGIN_HPP

#ifdef KYRA_TESTPLUGIN_EXPORTS
  #define KYRA_TESTPLUGIN_API __declspec(dllexport)
#else
  #define KYRA_TESTPLUGIN_API __declspec(dllimport)
#endif

#include <string>
#include "TestPluginInterface.hpp"


class KYRA_TESTPLUGIN_API MyPlugin : public TestPluginInterface {
	
	public:
	MyPlugin();
	~MyPlugin();
	
	
	virtual std::string getDescription() const;
};

extern "C" {
	//KYRA_TESTPLUGIN_API PLUGIN_DEFINITION();
	DEFINE_PLUGIN(KYRA_TESTPLUGIN_API);
}



#endif