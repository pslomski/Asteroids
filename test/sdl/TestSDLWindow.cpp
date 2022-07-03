#include <gtest/gtest.h>

#include "sdl/SDLWindow.h"

TEST(SDLWindow, shouldCreate)
{
    SDLWindow* window = SDLWindow::create(nullptr, 100, 100);
    ASSERT_TRUE(window != nullptr);
    SDLWindow::destroy(window);
    ASSERT_TRUE(window == nullptr);
}