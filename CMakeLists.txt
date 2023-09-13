cmake_minimum_required(VERSION 3.22.1)
project(Asteroids VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-O0")
set(CMAKE_CXX_FLAGS "-m64")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(CMakePrintHelpers)

cmake_print_variables(CMAKE_MODULE_PATH)

find_package(OpenGL REQUIRED)

set(SDL2_DIR d:/dev/SDL2-2.0.22)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#set(SDL2TTF_DIR d:/dev/SDL2_ttf-2.0.15)
#find_package(SDL2TTF REQUIRED)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
include_directories(${SDL2TTF_INCLUDE_DIRS})

#set(BASS_DIR d:/dev/Bass)
set(BASS_DIR /mnt/d/dev/bass24-linux)
find_package(BASS REQUIRED)

cmake_print_variables(BASS_INCLUDE_DIRS)
include_directories(${BASS_INCLUDE_DIRS})

set(ASTER_LIB aster)
add_library(${ASTER_LIB})

set(ASTER_EXE Asteroids)
add_executable(${ASTER_EXE})

include_directories(src)
add_subdirectory(src)
add_subdirectory(gtest)
add_subdirectory(test)
add_subdirectory(testsdl)
