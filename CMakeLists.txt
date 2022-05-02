cmake_minimum_required(VERSION 3.14)

project(KyraGameFramework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories( ${PROJECT_SOURCE_DIR}/include
					 ${PROJECT_SOURCE_DIR}/deps/include
					 ${PROJECT_SOURCE_DIR}/3rdparty/stb
					 ${PROJECT_SOURCE_DIR}/deps/include/freetype2)
					 
link_directories( ${PROJECT_SOURCE_DIR}/deps/lib )
					 
add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(examples)
