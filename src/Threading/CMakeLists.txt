
add_library(KyraThreading SHARED Task.cpp 
								 Thread.cpp)
									 
target_compile_definitions(KyraThreading PRIVATE -DKYRA_THREADING_EXPORTS)

if(${KYRA_COMPILER_IS_GCC} EQUAL true)
	target_compile_options(KyraThreading PRIVATE -Wall -O3 -Winline)
endif()

install(TARGETS KyraThreading RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraThreading ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)