#include <iostream>
#include "gl/Texture.hpp"

namespace gl
{
Texture::Texture():
    id(0)
{
}

Texture::~Texture()
{
    if(id != 0)
    {
        glDeleteTextures(1, &id);
        id = 0;
    }
}
}
