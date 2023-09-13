target_link_libraries(${ASTER_LIB}
    PRIVATE
        OpenGL::OpenGL
        ${SDL2_LIBRARY}
        ${SDL2TTF_LIBRARIES}
        ${BASS_LIBRARIES}
)
add_subdirectory(aster)
add_subdirectory(gl)
add_subdirectory(log)
add_subdirectory(sdl)
add_subdirectory(ui)

target_sources(${ASTER_EXE}
    PRIVATE
        Asteroids.cpp
)
target_link_libraries(${ASTER_EXE} ${ASTER_LIB})
