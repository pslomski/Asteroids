target_sources(${ASTER_LIB}
    PRIVATE
        Font.cpp Font.h
        Rectangle.cpp Rectangle.h
        TextControl.cpp TextControl.h
)

add_subdirectory(gstate)
