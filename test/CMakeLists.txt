add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

set(TEST_EXE TestAsteroids)
add_executable(${TEST_EXE})
target_link_libraries(${TEST_EXE}
    PRIVATE
        GTest::GTest
        ${ASTER_LIB}
        ${SDL2_LIBRARIES}
        SDL2_ttf::SDL2_ttf
)
add_subdirectory(aster)
add_subdirectory(sdl)
add_subdirectory(sdlttf)
add_subdirectory(ui)
