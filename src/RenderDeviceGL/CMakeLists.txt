
add_library(KyraRenderDeviceGL SHARED RenderDeviceGL.cpp)
target_link_libraries(KyraRenderDeviceGL PRIVATE KyraAbstractRenderDevice opengl32 gdi32)							  
target_compile_definitions(KyraRenderDeviceGL PRIVATE -DKYRA_RENDERDEVICEGL_EXPORTS)

install(TARGETS KyraRenderDeviceGL RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraRenderDeviceGL ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)