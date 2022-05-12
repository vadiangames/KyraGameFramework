
add_library(KyraUserInterface SHARED Widget.cpp)
target_compile_definitions(KyraUserInterface PRIVATE -DKYRA_USERINTERFACE_EXPORTS)
target_compile_options(KyraUserInterface PRIVATE -Wall -O3 -Winline)

install(TARGETS KyraUserInterface RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraUserInterface ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)