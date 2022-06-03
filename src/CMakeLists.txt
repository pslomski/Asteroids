target_sources(Asteroids
    PRIVATE
        Asteroids.cpp
        Exception.h
        Log.cpp Log.h
)

add_subdirectory(engine)
add_subdirectory(sdl)
add_subdirectory(ui)
