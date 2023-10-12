#pragma once
#include <GL/gl.h>

namespace gl
{
class Texture
{
public:
    Texture();
    ~Texture();

private:
    GLuint id;
};
} // namespace gl
