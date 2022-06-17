cmake_minimum_required(VERSION 3.14)

project(KyraGameFramework)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#COMPILER DETECTION

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  SET(KYRA_COMPILER_IS_CLANG true)
  SET(KYRA_COMPILER_IS_GCC false)
  SET(KYRA_COMPILER_IS_INTEL false)
  SET(KYRA_COMPILER_IS_MSVC false)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  SET(KYRA_COMPILER_IS_CLANG false)
  SET(KYRA_COMPILER_IS_GCC true)
  SET(KYRA_COMPILER_IS_INTEL false)
  SET(KYRA_COMPILER_IS_MSVC false)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  SET(KYRA_COMPILER_IS_CLANG false)
  SET(KYRA_COMPILER_IS_GCC false)
  SET(KYRA_COMPILER_IS_INTEL true)
  SET(KYRA_COMPILER_IS_MSVC false)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  SET(KYRA_COMPILER_IS_CLANG false)
  SET(KYRA_COMPILER_IS_GCC false)
  SET(KYRA_COMPILER_IS_INTEL false)
  SET(KYRA_COMPILER_IS_MSVC true)
endif()

include_directories( ${PROJECT_SOURCE_DIR}/include
					 ${PROJECT_SOURCE_DIR}/deps/include
					 ${PROJECT_SOURCE_DIR}/3rdparty/stb
					 ${PROJECT_SOURCE_DIR}/deps/include/freetype2)
					 
link_directories( ${PROJECT_SOURCE_DIR}/deps/lib )
					 
add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(examples)
