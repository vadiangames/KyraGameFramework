
add_library(KyraUserInterface SHARED Widget.cpp
									 Context.cpp )
									 
target_compile_definitions(KyraUserInterface PRIVATE -DKYRA_USERINTERFACE_EXPORTS)
target_compile_options(KyraUserInterface PRIVATE -Wall -O3 -Winline)
target_link_libraries(KyraUserInterface PRIVATE KyraWindow)

install(TARGETS KyraUserInterface RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraUserInterface ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)