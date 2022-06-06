cmake_minimum_required(VERSION 3.23)

project(Asteroids)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

set(SDL2_DIR d:/dev/SDL2-2.0.22)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SDL2TTF_DIR d:/dev/SDL2_ttf-2.0.15)
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2TTF_INCLUDE_DIRS})

set(BASS_DIR d:/dev/Bass)
find_package(BASS REQUIRED)
include_directories(${BASS_INCLUDE_DIRS})

set(ASTER_LIB aster)
add_library(${ASTER_LIB})

set(ASTER_EXE asteroids)
add_executable(${ASTER_EXE})

set(TEST_EXE test)
add_executable(${TEST_EXE})

include_directories(src)
add_subdirectory(src)
add_subdirectory(gtest)
add_subdirectory(test)
