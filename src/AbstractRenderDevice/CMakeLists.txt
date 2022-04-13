
add_library(KyraAbstractRenderDevice SHARED IRenderDevice.cpp)
							  
target_compile_definitions(KyraAbstractRenderDevice PRIVATE -DKYRA_ARD_EXPORTS)

install(TARGETS KyraAbstractRenderDevice RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraAbstractRenderDevice ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)