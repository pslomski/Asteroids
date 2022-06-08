#pragma once

#include <SDL_ttf.h>
#include <string>

#include "engine/Types.h"

#include "Rectangle.h"

namespace ui
{
// Utility class used to draw text on the screen using a specific font.
class Font
{
public:
    static SDL_Renderer* renderer;
    struct Size
    {
        int width;
        int height;
    };

    Font(const std::string& fontFace, const int height);
    ~Font();

    // Draw text on the screen at the specified location with the specified color.
    void drawText(const std::string& text, const int x, const int y, const GLColor& color);
    void drawFmtText(const int x, const int y, const GLColor& color, const char* fmt, ...);

    // Returns the size of the text. The top and right fields
    // of the returned rectangle are set to 0.
    Size getTextSize(const std::string& text);
private:
    Font() {};

    // Create the font with a specific height.
    void createFont(const std::string& fontFace, const int height);

    TTF_Font* font{nullptr};
};
} // namespace ui
