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

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_MODULE_PATH)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2_ttf REQUIRED)

set(BASS_DIR d:/dev/Bass)
#set(BASS_DIR /mnt/d/dev/bass24-linux)
find_package(BASS REQUIRED)
include_directories(${BASS_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)
enable_testing()
  
include_directories(src)
  
set(ASTER_LIB aster)
add_library(${ASTER_LIB})
  
set(ASTER_EXE Asteroids)
add_executable(${ASTER_EXE})

set(ASTERTEST_EXE AsteroidsTest)
add_executable(${ASTERTEST_EXE})
target_link_libraries(
  ${ASTERTEST_EXE}
  ${ASTER_LIB}
  GTest::gtest_main
  GTest::gmock_main
)

add_subdirectory(src)
# add_subdirectory(test)
  
include(GoogleTest)
gtest_discover_tests(${ASTERTEST_EXE})
