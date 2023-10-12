#include <SDL_ttf.h>
#include <gtest/gtest.h>


#include "ui/Font.hpp"

namespace ui
{
class FontTest : public ::testing::Test
{
public:
    void SetUp() { TTF_Init(); }

    void TearDown() { TTF_Quit(); }
};

TEST_F(FontTest, testGetTextSize)
{
    Font font{"vector battle", 20};

    Font::Size size = font.getTextSize("0123456789");

    ASSERT_EQ(150, size.width);
    ASSERT_EQ(24, size.height);
}
} // namespace ui
