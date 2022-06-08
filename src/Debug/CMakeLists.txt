
add_library(KyraDebug SHARED Profiler.cpp )
									 
target_compile_definitions(KyraDebug PRIVATE -DKYRA_DEBUG_EXPORTS)

if(${KYRA_COMPILER_IS_GCC} EQUAL true)
	target_compile_options(KyraDebug PRIVATE -Wall -O3 -Winline)
endif()

install(TARGETS KyraDebug RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraDebug ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)