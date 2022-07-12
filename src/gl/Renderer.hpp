#pragma once

#include <GL/gl.h>
#include <SDL_ttf.h>

namespace gl
{
class Renderer
{
public:
    static void setWindowSize(int width, int height);
    static void enter2DMode(int width, int height);
    static void leave2DMode();
    static GLuint loadTexture(SDL_Surface* surface, GLfloat* texcoord);
};

class DrawMode2DText
{
public:
    DrawMode2DText(int width, int height);
    ~DrawMode2DText();
};
} // namespace gl
