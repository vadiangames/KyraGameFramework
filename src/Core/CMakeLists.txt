
add_library(KyraCore SHARED CommandLine.cpp
							CmdParameterValue.cpp)
									 
target_compile_definitions(KyraCore PRIVATE -DKYRA_CORE_EXPORTS)

if(${KYRA_COMPILER_IS_GCC} EQUAL true)
	target_compile_options(KyraCore PRIVATE -Wall -O3 -Winline)
endif()

install(TARGETS KyraCore RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraCore ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)