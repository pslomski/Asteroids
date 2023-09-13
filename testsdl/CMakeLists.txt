set(TESTSDL_EXE TestSdl)
add_executable(${TESTSDL_EXE})
target_sources(${TESTSDL_EXE}
    PRIVATE
        TestSDL.cpp
        TestState.cpp TestState.hpp
)
set(LIBS OpenGL::GL ${SDL2_LIBRARY} ${SDL2TTF_LIBRARIES} ${ASTER_LIB})
target_link_libraries(${TESTSDL_EXE} ${LIBS})
