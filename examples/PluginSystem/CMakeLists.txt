add_library(TestPlugin SHARED TestPlugin.cpp)
target_compile_definitions(TestPlugin PRIVATE -DKYRA_TESTPLUGIN_EXPORTS)
#target_compile_options(TestPlugin PRIVATE -fpic)

add_executable(PluginSystem_Example main.cpp)

install(TARGETS TestPlugin PluginSystem_Example RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
