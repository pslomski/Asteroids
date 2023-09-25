#include <gtest/gtest.h>

#include "sdl/Application.hpp"
#include "sound/ut/mock/MockSoundEngine.hpp"

namespace testing
{
TEST(TestApplication, shouldCreateApplication)
{
    sound::MockSoundEngine soundEngine;
    sdl::Application app{soundEngine};
}
}
