#include <gtest/gtest.h>

#include "sdl/Window.hpp"

TEST(Window, shouldCreate)
{
    sdl::Window* window = sdl::Window::create(nullptr, 100, 100);
    ASSERT_TRUE(window != nullptr);
    sdl::Window::destroy(window);
    ASSERT_TRUE(window == nullptr);
}