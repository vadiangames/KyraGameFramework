
add_library(KyraGLExtensionLoader SHARED GLExtensionLoader.cpp)
target_link_libraries(KyraGLExtensionLoader PRIVATE opengl32)							  
target_compile_definitions(KyraGLExtensionLoader PRIVATE -DKYRA_GLEXTENSIONLOADER_EXPORTS)
target_compile_options(KyraGLExtensionLoader PRIVATE -Wall)

install(TARGETS KyraGLExtensionLoader RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraGLExtensionLoader ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)