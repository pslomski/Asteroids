#pragma once

#include <SDL_ttf.h>
#include <string>

#include "engine/Types.h"

#include "Rectangle.h"

namespace ui
{
// Utility class used to draw text on the screen using a specific font.
class GameFont {
public:
    using Rect = ui::Rectanglei;

    GameFont();
    GameFont(const std::string& fontFace, int height) {
        createFont(fontFace, height);
    }
    ~GameFont();

    // Draw text on the screen at the specified location with
    // the specified color.
    void drawText(const std::string& text, int x, int y, GLColor& color);
    void drawFmtText(int x, int y, GLColor& color, const char* fmt, ...);

    // Returns the size of the text. The top and right fields
    // of the returned rectangle are set to 0.
    Rect getTextSize(const std::string& text);
private:
    // Create the font with a specific height.
    void createFont(const std::string& fontFace, int height);

    TTF_Font* ptrFont_;
};
} // namespace ui
