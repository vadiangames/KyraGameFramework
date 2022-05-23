add_executable(01_GameStateHandling main.cpp)
target_link_libraries(01_GameStateHandling PRIVATE KyraWindow KyraRenderDeviceGL)

install( TARGETS 01_GameStateHandling RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)