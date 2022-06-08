#include <assert.h>

#include "engine/Renderer.h"
#include "Exception.h"
#include "Font.h"


namespace ui
{
const std::string fontFileName = "vectorb.ttf";
SDL_Renderer* Font::renderer = nullptr;

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
        throw SDLException("Couldn't load font");

    // TTF_HINTING_MONO gives best result for vectorb font
    TTF_SetFontHinting(font, TTF_HINTING_MONO);
}

Font::Size Font::getTextSize(const std::string& strText)
{
    int width, height;
    TTF_SizeText(font, strText.c_str(), &width, &height);
    return Size{width: width, height: height};
}
/*
void Font::drawText(const std::string& text, const int x, const int y, const GLColor& color)
{
    glColor4fv(color);
    constexpr SDL_Color sdlcolorWhite{0xFF, 0xFF, 0xFF, 0};
    SDL_Color white = sdlcolorWhite;
    // TTF_RenderText_Solid gives best result for vectorb font
    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), white);
    if (surf == nullptr)
        throw SDLException("Couldn't render text");

    // Convert the text into an OpenGL texture
    GLenum gl_error;
    GLfloat texcoord[4];
    glGetError();
    GLuint texture = ast::Renderer::loadTexture(surf, texcoord);
    if ((gl_error = glGetError()) != GL_NO_ERROR)
        // If this failed, the text may exceed texture size limits
        throw std::runtime_error("Warning: Couldn't create texture");

    // Make texture coordinates easy to understand
    GLfloat texMinX = texcoord[0];
    GLfloat texMinY = texcoord[1];
    GLfloat texMaxX = texcoord[2];
    GLfloat texMaxY = texcoord[3];
    int w = surf->w;
    int h = surf->h;

    // We don't need the original text surface anymore
    SDL_FreeSurface(surf);

    // Show the text on the screen
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(texMinX, texMinY); glVertex2i(x, y);
    glTexCoord2f(texMaxX, texMinY); glVertex2i(x + w, y);
    glTexCoord2f(texMinX, texMaxY); glVertex2i(x, y + h);
    glTexCoord2f(texMaxX, texMaxY); glVertex2i(x + w, y + h);
    glEnd();
}
*/
void Font::drawText(const std::string& text, const int x, const int y, const GLColor& color)
{
    assert(renderer != nullptr);
    if (renderer == nullptr)
    {
        return;
    }
    glColor4fv(color);
    constexpr SDL_Color sdlcolorWhite{0xFF, 0xFF, 0xFF, 0};
    SDL_Color white = sdlcolorWhite;
    // TTF_RenderText_Solid gives best result for vectorb font
    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), white);
    if (surf == nullptr)
        throw SDLException("Couldn't render text");
    // Setup the texture
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surf);
    if (textureText == nullptr)
        throw SDLException("Couldn't create textureText");
    // Free the surface
    // We are done with it after we have uploaded to the texture
    SDL_FreeSurface(surf);
    SDL_Rect rectangle{x, y, surf->w, surf->h};
    // Render our text on a rectangle
    SDL_RenderCopy(renderer, textureText, nullptr, &rectangle);
    // Destroy our textured text
    SDL_DestroyTexture(textureText);
}

void Font::drawFmtText(const int x, const int y, const GLColor& color, const char* fmt, ...)	// Custom GL "Print" Routine
{
    if (fmt == nullptr)                         // If There's No Text
        return;                                 // Do Nothing

    char text[256];                             // Holds Our String
    va_list	ap;                                 // Pointer To List Of Arguments
    va_start(ap, fmt);                          // Parses The String For Variables
    int len = vsprintf_s(text, fmt, ap);        // And Converts Symbols To Actual Numbers
    va_end(ap);                                 // Results Are Stored In Text

    drawText(text, x, y, color);
}
} // namespace ui
