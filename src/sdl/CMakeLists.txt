target_sources(${ASTER_LIB}
    PRIVATE
        Application.cpp Application.hpp
        Exception.hpp
        SDLTools.h
        Window.cpp Window.hpp
)

add_executable(
    TestApplication
    ut/TestApplication.cpp
    Application.cpp Application.hpp
)
target_link_libraries(
    TestApplication
    GTest::gtest_main
    GTest::gmock_main
    ${ASTER_LIB}
)
add_test(TestApplication TestApplication)