target_sources(Asteroids
    PRIVATE
        GameFont.cpp GameFont.h
        Rectangle.h
        TextControl.cpp TextControl.h
)

add_subdirectory(gstate)
