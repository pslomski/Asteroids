cmake_minimum_required(VERSION 3.23)

project(Asteroids)

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

set(LIBS opengl32 ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} ${BASS_LIBRARIES})

add_executable(${PROJECT_NAME} "")
add_subdirectory(src)
include_directories(src)
target_link_libraries(${PROJECT_NAME} ${LIBS})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
