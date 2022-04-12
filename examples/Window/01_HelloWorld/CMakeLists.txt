
add_executable(Window_Example_HelloWorld main.cpp)
target_link_libraries(Window_Example_HelloWorld PRIVATE KyraWindow)

install(TARGETS Window_Example_HelloWorld RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)