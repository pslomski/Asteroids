cmake_minimum_required(VERSION 3.22.1)
project(Asteroids VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-O0")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "-Wextra")
set(CMAKE_CXX_FLAGS "-Werror")
set(CMAKE_CXX_FLAGS "-pedantic")
set(CMAKE_CXX_FLAGS "-m64")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

enable_testing()

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_MODULE_PATH)

find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
cmake_print_variables(SDL2_INCLUDE_DIRS)
cmake_print_variables(SDL2_LIBRARIES)

#set(SDL2TTF_DIR d:/dev/SDL2_ttf-2.0.15)
#find_package(SDL2TTF REQUIRED)
#INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
#include_directories(${SDL2TTF_INCLUDE_DIRS})

set(BASS_DIR d:/dev/Bass)
#set(BASS_DIR /mnt/d/dev/bass24-linux)
find_package(BASS REQUIRED)

cmake_print_variables(BASS_INCLUDE_DIRS)
include_directories(${BASS_INCLUDE_DIRS})

include(FetchContent)

#FetchContent_Declare(
#  SDL
#  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
#  GIT_TAG        release-2.28.3
#)
#FetchContent_MakeAvailable(SDL)

set(FT_REQUIRE_PNG FALSE)
set(FT_DISABLE_HARFBUZZ TRUE)
FetchContent_Declare(
  Freetype
  GIT_REPOSITORY https://github.com/freetype/freetype.git
  GIT_TAG        VER-2-13-2
)
FetchContent_MakeAvailable(Freetype)

FetchContent_Declare(
  SDL_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG        release-2.20.2
)
FetchContent_MakeAvailable(SDL_ttf)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

include_directories(src)

set(ASTER_LIB aster)
add_library(${ASTER_LIB})

set(ASTER_EXE Asteroids)
add_executable(${ASTER_EXE})

add_subdirectory(src)
add_subdirectory(test)

include(GoogleTest)
