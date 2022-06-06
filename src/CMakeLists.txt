set(LIBS opengl32 ${SDL2_LIBRARY} ${SDL2TTF_LIBRARIES} ${BASS_LIBRARIES})

target_link_libraries(${ASTER_LIB} ${LIBS})
add_subdirectory(engine)
add_subdirectory(sdl)
add_subdirectory(ui)

target_sources(${ASTER_EXE}
    PRIVATE
        Asteroids.cpp
        Exception.h
        Log.cpp Log.h
)
target_link_libraries(${ASTER_EXE} ${ASTER_LIB})
