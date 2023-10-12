#include "gl/Texture.hpp"
#include <iostream>

namespace gl
{
Texture::Texture() : id(0) {}

Texture::~Texture()
{
    if (id != 0)
    {
        glDeleteTextures(1, &id);
        id = 0;
    }
}
} // namespace gl
