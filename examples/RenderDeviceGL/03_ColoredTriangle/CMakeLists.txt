
add_executable(RendererGL_Example_ColoredTriangle main.cpp)
target_link_libraries(RendererGL_Example_ColoredTriangle PRIVATE KyraWindow KyraGLExtensionLoader KyraRenderDeviceGL opengl32)

install(TARGETS RendererGL_Example_ColoredTriangle RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)