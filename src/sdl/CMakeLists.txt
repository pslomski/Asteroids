target_sources(${ASTER_LIB}
    PRIVATE
        Application.cpp Application.hpp
        Exception.hpp
        SDLTools.h
        Window.cpp Window.hpp
)

target_sources(${ASTERTEST_EXE}
    PRIVATE
        ut/TestApplication.cpp
)
