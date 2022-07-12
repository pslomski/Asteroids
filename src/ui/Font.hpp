#pragma once
#include <SDL_ttf.h>
#include <string>
#include "engine/Types.h"
#include "ui/Rectangle.h"

namespace ui
{
class Font
{
public:
    struct Size
    {
        int width;
        int height;
    };

    Font(const std::string& fontFace, const int height);
    ~Font();

    void drawText(const std::string& text, const int x, const int y, const GLColor& color);
    void drawFmtText(const int x, const int y, const GLColor& color, const char* fmt, ...);
    Size getTextSize(const std::string& text);
private:
    Font() {};
    void createFont(const std::string& fontFace, const int height);
    TTF_Font* font{nullptr};
};
} // namespace ui
