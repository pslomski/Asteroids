target_sources(${TESTSDL_EXE}
    PRIVATE
        TestSDL.cpp
        TestState.cpp TestState.hpp
)

set(LIBS opengl32 ${SDL2_LIBRARY} ${SDL2TTF_LIBRARIES} ${ASTER_LIB})
target_link_libraries(${TESTSDL_EXE} ${LIBS})
