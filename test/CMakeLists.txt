target_link_libraries(${TEST_EXE}
    gtest_main ${ASTER_LIB}
)

add_subdirectory(aster)
add_subdirectory(sdl)
add_subdirectory(sdlttf)
add_subdirectory(ui)
