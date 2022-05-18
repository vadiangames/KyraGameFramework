
add_library(KyraGLExtensionLoader SHARED GLExtensionLoader.cpp)
target_link_libraries(KyraGLExtensionLoader PRIVATE opengl32)							  
target_compile_definitions(KyraGLExtensionLoader PRIVATE -DKYRA_GLEXTENSIONLOADER_EXPORTS)

if(${KYRA_COMPILER_IS_GCC} EQUAL true)
	target_compile_options(KyraGLExtensionLoader PRIVATE -Wall -O3 -Winline)
endif()



install(TARGETS KyraGLExtensionLoader RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraGLExtensionLoader ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)