
add_library(KyraAnimation SHARED IAnimation.cpp )
									 
target_compile_definitions(KyraAnimation PRIVATE -DKYRA_ANIMATION_EXPORTS)

if(${KYRA_COMPILER_IS_GCC} EQUAL true)
	target_compile_options(KyraAnimation PRIVATE -Wall -O3 -Winline)
endif()

target_link_libraries(KyraAnimation PRIVATE KyraWindow)

install(TARGETS KyraAnimation RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraAnimation ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)