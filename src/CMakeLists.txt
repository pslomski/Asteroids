set(LIBS OpenGL::OpenGL ${SDL2_LIBRARY} ${SDL2TTF_LIBRARIES} ${BASS_LIBRARIES})

target_link_libraries(${ASTER_LIB} ${LIBS})
add_subdirectory(aster)
add_subdirectory(gl)
add_subdirectory(log)
add_subdirectory(sdl)
add_subdirectory(ui)

target_sources(${ASTER_EXE}
    PRIVATE
        Asteroids.cpp
        Exception.h
)
target_link_libraries(${ASTER_EXE} ${ASTER_LIB})
