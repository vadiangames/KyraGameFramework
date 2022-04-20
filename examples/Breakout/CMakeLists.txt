
add_executable(Breakout main.cpp)
target_link_libraries(Breakout PRIVATE KyraWindow KyraGLExtensionLoader KyraRenderDeviceGL opengl32)

install(TARGETS Breakout RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)