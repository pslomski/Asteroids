include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

set(TEST_EXE TestAsteroids)
add_executable(${TEST_EXE})
target_link_libraries(${TEST_EXE}
    PRIVATE
        GTest::GTest
        ${ASTER_LIB}
)
add_subdirectory(aster)
add_subdirectory(sdl)
add_subdirectory(sdlttf)
add_subdirectory(ui)

add_test(Tools TestTools)