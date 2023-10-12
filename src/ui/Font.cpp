#include <assert.h>

#include "gl/Renderer.hpp"
#include "log/Log.hpp"

#include "Font.hpp"
#include "sdl/Exception.hpp"

namespace ui
{
const std::string fontFileName = "Vectorb.ttf";

Font::Font(const std::string& fontFace, const int height)
{
    createFont(fontFace, height);
}

Font::~Font()
{
    TTF_CloseFont(font);
}

void Font::createFont(const std::string& fontFace, const int height)
{
    font = TTF_OpenFont(fontFileName.c_str(), height);
    if (font == nullptr)
    {
        throw SDLException("Couldn't load font");
    }

    // TTF_HINTING_MONO gives best result for vectorb font
    TTF_SetFontHinting(font, TTF_HINTING_MONO);
}

Font::Size Font::getTextSize(const std::string& strText)
{
    int width, height;
    TTF_SizeText(font, strText.c_str(), &width, &height);
    return Size{.width = width, .height = height};
}

void Font::drawText(const std::string& text, const int x, const int y, const GLColor& color)
{
    if (text.empty())
    {
        return;
    }
    // LOG_INF("Font::drawText text:%s x:%d y:%d", text.c_str(), x, y);
    glColor4fv(color);
    constexpr SDL_Color colorWhite{0xFF, 0xFF, 0xFF, 0xFF};
    // TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), colorWhite);
    if (surface == nullptr)
    {
        throw SDLException("Couldn't render text");
    }
    // LOG_INF("surface bpp:%d, Bpp:%d, w:%d, h:%d",
    // surface->format->BitsPerPixel, surface->format->BytesPerPixel, surface->w, surface->h);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    int w = surface->w;
    int h = surface->h;
    SDL_FreeSurface(surface);

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 0);
    glVertex2i(x, y);
    glTexCoord2f(1, 0);
    glVertex2i(x + w, y);
    glTexCoord2f(0, 1);
    glVertex2i(x, y + h);
    glTexCoord2f(1, 1);
    glVertex2i(x + w, y + h);
    glEnd();
    glDeleteTextures(1, &texture);
}

void Font::drawFmtText(const int x, const int y, const GLColor& color, const char* fmt, ...)
{
    if (fmt == nullptr)
    {
        return;
    }
    char text[256];
    va_list ap;
    va_start(ap, fmt);
    int len = vsprintf(text, fmt, ap);
    va_end(ap);
    drawText(text, x, y, color);
}
} // namespace ui
