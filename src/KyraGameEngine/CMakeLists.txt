
add_executable(KyraGameEngine main.cpp)
target_link_libraries(KyraGameEngine PRIVATE KyraWindow KyraGLExtensionLoader KyraRenderDeviceGL KyraUserInterface opengl32 freetype)

install(TARGETS KyraGameEngine RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)