
add_executable(RendererGL_Example_FontRendering main.cpp)
target_link_libraries(RendererGL_Example_FontRendering PRIVATE KyraWindow KyraGLExtensionLoader KyraRenderDeviceGL opengl32 freetype)

install(TARGETS RendererGL_Example_FontRendering RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)