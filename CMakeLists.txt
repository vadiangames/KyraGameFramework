cmake_minimum_required(VERSION 3.14)

project(KyraGameFramework)

include_directories( ${PROJECT_SOURCE_DIR}/include
					 ${PROJECT_SOURCE_DIR}/3rdparty/glm
					 ${PROJECT_SOURCE_DIR}/3rdparty/stb)
					 
link_directories( ${PROJECT_SOURCE_DIR}/lib )
					 
add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(examples)
