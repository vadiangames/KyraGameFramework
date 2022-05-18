
add_library(KyraUserInterface SHARED Widget.cpp
									 Context.cpp 
									 Button.cpp
									 ImageButton.cpp
									 EditBox.cpp )
									 
target_compile_definitions(KyraUserInterface PRIVATE -DKYRA_USERINTERFACE_EXPORTS)

if(${KYRA_COMPILER_IS_GCC} EQUAL true)
	target_compile_options(KyraUserInterface PRIVATE -Wall -O3 -Winline)
endif()

target_link_libraries(KyraUserInterface PRIVATE KyraWindow KyraRenderDeviceGL)

install(TARGETS KyraUserInterface RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraUserInterface ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)