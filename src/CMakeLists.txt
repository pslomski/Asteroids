target_sources(Asteroids
    PRIVATE
        Asteroids.cpp
        Exception.h
        Log.cpp Log.h
        SDLApplication.cpp SDLApplication.h
        SDLTools.h
        SDLWindow.cpp SDLWindow.h
        splitpath.cpp splitpath.h 
)

add_subdirectory(engine)
add_subdirectory(menu)
