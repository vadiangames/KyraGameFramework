
add_library(KyraWindow SHARED IWindow.cpp
							  SystemEventListener.cpp
							  SystemEventDispatcher.cpp
							  ./Windows/WindowWin32.cpp)
							  
target_compile_definitions(KyraWindow PRIVATE -DKYRA_WINDOW_EXPORTS)
target_compile_options(KyraWindow PRIVATE -Wall -O3 -Winline)


install(TARGETS KyraWindow RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraWindow ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)